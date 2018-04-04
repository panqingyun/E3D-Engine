/*
 *  CameraEntity.cpp
 *  Virtual Vision
 *
 *  Created by Abdallah Dib Abdallah.dib@virtual-vison.net
 *  Copyright 2011 Virtual Vision. All rights reserved.
 *
 */
#include "E3DCamera.h"
#include <cmath>
#include "../Object/E3DTransform.hpp"
#include "../RenderSystem/E3DRenderQueue.h"
#include "../RenderSystem/Texture/E3DRender2Texture.h"
#include "../Source/EngineDelegate.h"
#include "../RenderSystem/E3DRenderSystem.hpp"

namespace E3DEngine
{
	Camera::Camera(const vec3f& position, const vec3f& target, float32 fov, const vec3f& up, float32 zNear, float32 zFar, float32 aspect)
	{
		m_Plans.resize(6);
		for (int i = 0; i < m_Plans.size() ;i++)
		{
			m_Plans[i] = new float[4];
		}
		isPerspective = true;
		m_mProjection = mat4f::createPerspective(fov, aspect, zNear, zFar);
		m_mView = mat4f::createLookAt(Transform->Position, target, up);
		Transform->Rotation = Quatf::frommat(m_mView);
		Transform->Position = position;
		m_near = zNear;
		m_far = zFar;
		m_aspect = aspect;
		m_fov = fov;
		m_mViewInverse = m_mView.inverse();
		m_mProjectInverse = m_mProjection.inverse();
		m_RenderQueue = new RenderQueue;
		m_RenderQueue->SetCamera(this);
		m_clearType = eCT_Color | eCT_Depth | eCT_Stencil;
		m_layerMask = ~0;
		m_nDepth = 0;
		NodeType = eT_Camera;
		SceneManager::GetInstance().GetCurrentScene()->AddCamera(this);
		CreateBehaviour();
		Transform->SetNeedUpdate(false);
	}
	
	Camera::Camera(const vec3f& position, const vec3f& target, vec3f up, float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar)
	{
		m_Plans.resize(6);
		for (int i = 0; i < m_Plans.size(); i++)
		{
			m_Plans[i] = new float[4];
		}
		isPerspective = false;
		m_mProjection = mat4f::createOrtho(left, right, bottom, top, zNear, zFar);
		m_mView = mat4f::createLookAt(Transform->Position, target, up);
		Transform->Rotation = Quatf::frommat(m_mView);
		Transform->Position = position;
		m_mViewInverse = m_mView.inverse();
		m_mProjectInverse = m_mProjection.inverse();
		m_RenderQueue = new RenderQueue;
		m_RenderQueue->SetCamera(this);
		m_clearType = eCT_Color | eCT_Depth | eCT_Stencil;
		m_layerMask = ~0;
		m_nDepth = 0;
		NodeType = eT_Camera;
		SceneManager::GetInstance().GetCurrentScene()->AddCamera(this);
		CreateBehaviour();
		Transform->SetNeedUpdate(false);
	}


	Camera::~Camera()
	{
		if (ParentNode != nullptr && ParentNode->NodeType == eT_Camera)
		{
			static_cast<GameObject*>(ParentNode)->Transform->RemoveChild(ID);
		}
	}


	void Camera::Render(float deltaTime)
	{
		if (RTTs.size() == 0)
		{
			render(deltaTime);
		}
		else
		{
			for (auto & rtt : RTTs)
			{
				rtt->Bind();
				render(deltaTime);
			}
		}
	}


	void Camera::render(float deltaTime)
	{
		Clear();
		m_RenderQueue->Render(deltaTime);
		GetRenderSystem()->BindDefaultBackbuffer();
	}

	vec3f Camera::GetWorldPointWithScreenPoint(float x, float y, float z)
	{
		vec4f zViewVec = GetViewMatrix() * vec4f(0.0, 0.0, z, 1.0);
		float zView = zViewVec.z;
		float zProj = zView * GetProjectionMatrix()[10] + GetProjectionMatrix()[14];
		float wView = -zView;

		vec4f projNormal = vec4f();
		vec4f proj;
		projNormal.x = x;
		projNormal.y = y;
		projNormal.z = zProj / wView;
		projNormal.w = 1.0;
		proj = vec4f(projNormal.x*wView, projNormal.y*wView, zProj, projNormal.w*wView);
		vec4f view = GetProjectInverseMatrix() * proj;
		vec4f world = GetViewInverseMatrix() * view;

		return Convert::Vec4ToVec3(world);
	}

	void Camera::Clear()
	{
		GetRenderSystem()->Clear(m_clearColor, m_clearType);
	}

	void Camera::SetClearColor(Color4 color)
	{
		m_clearColor = color;
	}

	void Camera::SetClearType(DWORD clearType)
	{
		m_clearType = clearType;
	}


	void Camera::FrameSizeChange(float aspect)
	{
		if (isPerspective)
		{
			m_mProjection = mat4f::createPerspective(m_fov, aspect, m_near, m_far);
			m_mProjectInverse = m_mProjection.inverse();
		}
	}

	RenderQueue * Camera::GetRenderQueue()
	{
		return m_RenderQueue;
	}

	void Camera::SetLayerMask(DWORD layerMask)
	{
		GameObject::SetLayerMask(layerMask);
		m_RenderQueue->CullRenderObjectByLayer(layerMask);
		SceneManager::GetInstance().GetCurrentScene()->ChangeCameraObject(this);
	}

	int Camera::GetDepth()
	{
		return m_nDepth;
	}

	void Camera::SetDepth(int depth)
	{
		m_nDepth = depth;
		SceneManager::GetInstance().GetCurrentScene()->SortCamera();
	}

	void Camera::SetRenderTexture(Render2Texture * rtt)
	{
		for (auto & _rtt : RTTs)
		{
			if (rtt == _rtt)
			{
				return;
			}
		}
		RTTs.push_back(rtt);
	}

	void Camera::TransformChange()
	{
		//extract view matrix from quaternion
		Transform->WorldMatrix = Transform->Rotation.transform();
		Transform->WorldMatrix[12] = Transform->Position.x;
		Transform->WorldMatrix[13] = Transform->Position.y;
		Transform->WorldMatrix[14] = Transform->Position.z;
		m_mView = Transform->WorldMatrix.inverse();

		m_mViewInverse = m_mView.inverse();
	}


	const mat4f& Camera::GetViewMatrix()
	{
		//get the view matrix of the camera
		Transform->WorldMatrix = Transform->Rotation.transform();
		Transform->WorldMatrix[12] = Transform->Position.x;
		Transform->WorldMatrix[13] = Transform->Position.y;
		Transform->WorldMatrix[14] = Transform->Position.z;
		m_mView = Transform->WorldMatrix.inverse();
		
		m_mViewInverse = m_mView.inverse();
		
		return m_mView;
	}

	// 根据投影归一化后的x,y，以及世界坐标中的z，得到视空间下的(x',y',z')
	vec4f Camera::GetWorldPoint(float x,float y,float z)
	{
		vec4f zViewVec = GetViewMatrix() * vec4f(0.0, 0.0, z, 1.0);
		float zView = zViewVec.z;
		float zProj = zView * GetProjectionMatrix()[10] + GetProjectionMatrix()[14];
		float wView = -zView;

		vec4f projNormal = vec4f();
		vec4f proj;
		projNormal.x = x;
		projNormal.y = y;
		projNormal.z = zProj/wView;
		projNormal.w = 1.0;
		proj = vec4f(projNormal.x*wView, projNormal.y*wView, zProj, projNormal.w*wView);
		vec4f view = GetProjectInverseMatrix() * proj;
		vec4f world = GetViewInverseMatrix() * view;
		
		return world;
	}

	void Camera::SetProjectionMatrix(const mat4f& projection)
	{
		m_mProjection = projection;
		
		m_mProjectInverse = m_mProjection.inverse();
	}

	vec3f Camera::GetForwardVector()
	{
		Transform->WorldMatrix = m_mView.inverse();
		return vec3f(-Transform->WorldMatrix[8], -Transform->WorldMatrix[9], -Transform->WorldMatrix[10]);
	}

	vec3f Camera::GetUpVector()
	{
		Transform->WorldMatrix = m_mView.inverse();
		return vec3f(Transform->WorldMatrix[4], Transform->WorldMatrix[5], Transform->WorldMatrix[6]);
	}

	vec3f Camera::GetRigthVector()
	{
		Transform->WorldMatrix = m_mView.inverse();
		return vec3f(Transform->WorldMatrix[0], Transform->WorldMatrix[1], Transform->WorldMatrix[2]);
	}

	vec3f Camera::GetThirdPoint(vec3f p1,vec3f p2,float z3)
	{
		vec3f ret;
		ret.x = ((z3-p2.z)*(z3-p2.z)-(z3-p1.z)*(z3-p1.z))/20;
		ret.y = p1.y - sqrt(((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z))-(ret.x-p1.x)*(ret.x-p1.x)-(z3-p1.z)*(z3-p1.z));
		ret.z = z3;
		
		return ret;
	}

	float Camera::DistanceBetweenPoints(vec3f p1,vec3f p2)
	{
		float dis = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z);
		return sqrt(dis);
	}

	bool Camera::boundingBoxFrustum(vec3f position, float size)
	{
		calculateFrustumPlanes();
		return boundingBoxFrustum(position.x, position.y, position.x, size);
	}

	bool Camera::boundingBoxFrustum(float x, float y, float z, float size)
	{
		for(int i = 0;i < 6;i++)
		{
			if (m_Plans[i][0] * (x - size) + m_Plans[i][1] * (y - size) + m_Plans[i][2] * (z - size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x + size) + m_Plans[i][1] * (y - size) + m_Plans[i][2] * (z - size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x - size) + m_Plans[i][1] * (y + size) + m_Plans[i][2] * (z - size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x + size) + m_Plans[i][1] * (y + size) + m_Plans[i][2] * (z - size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x - size) + m_Plans[i][1] * (y - size) + m_Plans[i][2] * (z + size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x + size) + m_Plans[i][1] * (y - size) + m_Plans[i][2] * (z + size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x - size) + m_Plans[i][1] * (y + size) + m_Plans[i][2] * (z + size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			if (m_Plans[i][0] * (x + size) + m_Plans[i][1] * (y + size) + m_Plans[i][2] * (z + size) + m_Plans[i][3] > 0)
			{
				continue;
			}
			return false;
		}
		return true;
	}


	void Camera::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Camera);
		setBehaviourDefaultValue();
	}


	void Camera::setBehaviourDefaultValue()
	{
		GameObject::setBehaviourDefaultValue();
	}

	float * Camera::normal(float *plans) {
		m_Temp = plans;
		float size = sqrt(m_Temp[0] * m_Temp[0] + m_Temp[1] * m_Temp[1] + m_Temp[2] * m_Temp[2]);
		m_Temp[0] /= size;
		m_Temp[1] /= size;
		m_Temp[2] /= size;
		m_Temp[3] /= size;
		return m_Temp;
	}

	void Camera::calculateFrustumPlanes()
	{
		mat4f mMvpgMatrix = m_mProjection * m_mView;
	//    float *plan = new float[4];
	//    plan[0] = mMvpgMatrix[ 3] - mMvpgMatrix[ 0];
	//    plan[1]
	//    plan[2]
	//    plan[3]
		//第一个面
		m_Plans[0][0] = mMvpgMatrix[ 3] - mMvpgMatrix[ 0];
		m_Plans[0][1] = mMvpgMatrix[ 7] - mMvpgMatrix[ 4];
		m_Plans[0][2] = mMvpgMatrix[11] - mMvpgMatrix[ 8];
		m_Plans[0][3] = mMvpgMatrix[15] - mMvpgMatrix[12];
		m_Plans[0] = normal(m_Plans[0]);
		//第二个面
		m_Plans[1][0] = mMvpgMatrix[ 3] + mMvpgMatrix[ 0];
		m_Plans[1][1] = mMvpgMatrix[ 7] + mMvpgMatrix[ 4];
		m_Plans[1][2] = mMvpgMatrix[11] + mMvpgMatrix[ 8];
		m_Plans[1][3] = mMvpgMatrix[15] + mMvpgMatrix[12];
		
		m_Plans[1] = normal(m_Plans[1]);
		//第三个面
		m_Plans[2][0] = mMvpgMatrix[ 3] + mMvpgMatrix[ 1];
		m_Plans[2][1] = mMvpgMatrix[ 7] + mMvpgMatrix[ 5];
		m_Plans[2][2] = mMvpgMatrix[11] + mMvpgMatrix[ 9];
		m_Plans[2][3] = mMvpgMatrix[15] + mMvpgMatrix[13];
		
		m_Plans[2] = normal(m_Plans[2]);
		//第四个面
		m_Plans[3][0] = mMvpgMatrix[ 3] - mMvpgMatrix[ 1];
		m_Plans[3][1] = mMvpgMatrix[ 7] - mMvpgMatrix[ 5];
		m_Plans[3][2] = mMvpgMatrix[11] - mMvpgMatrix[ 9];
		m_Plans[3][3] = mMvpgMatrix[15] - mMvpgMatrix[13];
		
		m_Plans[3] = normal(m_Plans[3]);
		//第五个面
		m_Plans[4][0] = mMvpgMatrix[ 3] - mMvpgMatrix[ 2];
		m_Plans[4][1] = mMvpgMatrix[ 7] - mMvpgMatrix[ 6];
		m_Plans[4][2] = mMvpgMatrix[11] - mMvpgMatrix[10];
		m_Plans[4][3] = mMvpgMatrix[15] - mMvpgMatrix[14];
		
		m_Plans[4] = normal(m_Plans[4]);
		//第六个面
		m_Plans[5][0] = mMvpgMatrix[ 3] + mMvpgMatrix[ 2];
		m_Plans[5][1] = mMvpgMatrix[ 7] + mMvpgMatrix[ 6];
		m_Plans[5][2] = mMvpgMatrix[11] + mMvpgMatrix[10];
		m_Plans[5][3] = mMvpgMatrix[15] + mMvpgMatrix[14];
		
		m_Plans[5] = normal(m_Plans[5]);
	}

	Camera * Camera::CreateCamera()
	{
		const float32 fov = 60.0f;
		const vec3f up = vec3f(0.0f, 1.0f, 0.0);
		const float32 zNear = 1.0f;
		const float32 zFar = 30000.0f;
		Vector2 frameSize = GetRenderSystem()->GetFrameSize();
		const float32 aspect = frameSize.x / frameSize.y;
		const vec3f position = vec3f(0, 0, 200);
		const vec3f target = vec3f(0, 0, -1);
		E3DEngine::Camera *camera = new E3DEngine::Camera(position, target, fov, up, zNear, zFar, aspect);
		return camera;
	}

}
