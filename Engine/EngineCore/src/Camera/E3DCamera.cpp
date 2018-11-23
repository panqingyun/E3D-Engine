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
#include "../Physics/E3DPhysics.h"
#include "../Source/E3DVertexManager.h"

namespace E3DEngine
{
	void Camera::createCamera(const vec3f& position, const vec3f& target, float32 fov, const vec3f& up, float32 zNear, float32 zFar, float32 aspect)
	{
		m_Plans.resize(6);
		for (int i = 0; i < m_Plans.size() ;i++)
		{
			m_Plans[i] = new float[4];
		}
		m_mProjection = mat4f::createPerspective(fov, aspect, zNear, zFar);
		m_mView = mat4f::createLookAt(position, target, up);
		m_aspect = aspect;
		m_mViewInverse = m_mView.inverse();
		m_mProjectInverse = m_mProjection.inverse();
		m_RenderQueue = new RenderQueue;
		m_RenderQueue->SetCamera(this);
		m_clearType = eCT_Color | eCT_Depth | eCT_Stencil;
		m_nDepth = 0;
		m_bIsShadowCamera = false;
		Transform->SetNeedUpdate(false);
	}
	
	void Camera::createCamera(const vec3f& position, const vec3f& target, vec3f up, float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar)
	{
		m_Plans.resize(6);
		for (int i = 0; i < m_Plans.size(); i++)
		{
			m_Plans[i] = new float[4];
		}
		m_mProjection = mat4f::createOrtho(left, right, bottom, top, zNear, zFar);
		m_mView = mat4f::createLookAt(position, target, up);
		m_mViewInverse = m_mView.inverse();
		m_mProjectInverse = m_mProjection.inverse();
		m_RenderQueue = new RenderQueue;
		m_RenderQueue->SetCamera(this);
		m_clearType = eCT_Color | eCT_Depth | eCT_Stencil;
		m_nDepth = 0;
		m_bIsShadowCamera = false;
		Transform->SetNeedUpdate(false);
	}


	Camera::~Camera()
	{
		delete m_RenderQueue;
	}


	void Camera::Awake()
	{
		vec3f up = vec3f(0.0f, 1.0f, 0.0);
		Vector2 frameSize = GetRenderSystem()->GetFrameSize();
		if (Perspective)
		{
			const float32 aspect = frameSize.x / frameSize.y;
			createCamera(Pos, Target, Fov, up, Near, Far, aspect);
			mGameObject->SetColor(Color4(0, 0, 0, 0));
		}
		else
		{
			float &&halfSize = Size / 2.0f;
			createCamera(Pos, Target, up, -halfSize, halfSize, -halfSize, halfSize, Near, Far);
			mGameObject->SetColor(Color4(0, 0, 0, 0));
		}
		m_RenderQueue->CullRenderObjectByLayer(mGameObject->GetLayerMask());
		SceneManager::GetCurrentScene()->ChangeCameraObject(this);
		Component::Awake();
	}


	void Camera::TransformChange()
	{
		Transform->WorldMatrix = Transform->Rotation.transform();
		Transform->WorldMatrix[12] = Transform->Position.x;
		Transform->WorldMatrix[13] = Transform->Position.y;
		Transform->WorldMatrix[14] = Transform->Position.z;
		m_mView = Transform->WorldMatrix.inverse();
	}

	void Camera::Render()
	{
		if (RTTs.size() == 0)
		{
			render();
		}
		else
		{
			for (auto & rtt : RTTs)
			{
				rtt->Bind();
				render();
			}
		}
	}

	void Camera::render()
	{
		ClearBackGround();
		if (m_bIsShadowCamera)
		{
			GetRenderSystem()->SetCullFaceType(eCF_FRONT);
		}
		m_RenderQueue->Render();
		if (m_bIsShadowCamera)
		{
			GetRenderSystem()->SetCullFaceType(eCF_BACK);
		}
		GetRenderSystem()->BindDefaultBackbuffer();
	}

	vec3f Camera::GetWorldPointWithScreenPoint(float x, float y, float z)
	{
		float clipX = x / GetRenderSystem()->getFrameWidth() * 2.0f - 1;
		float clipY = -(y / GetRenderSystem()->getFrameHeight() * 2.0f - 1);
		vec4f world = GetWorldPoint(clipX, clipY, z);

		return Convert::Vec4ToVec3(world);
	}

	vec3f Camera::GetScreenPointWithWorlPoint(const vec3f &worldPoint)
	{
		vec3f retPos;
		vec4f &&point = GetProjectionMatrix()  * GetViewMatrix() * Convert::Vec3ToVec4(worldPoint);
		retPos.x = ((point.x / point.w) + 1) / 2.0 * GetRenderSystem()->getFrameWidth();
		retPos.y = -((point.y / point.w) + 1) / 2.0 * GetRenderSystem()->getFrameHeight();
		retPos.z /= point.w;

		return retPos;
	}

	vec3f Camera::GetClipPoint(const vec3f &worldPoint)
	{
		vec3f retPos;
		vec4f &&point = GetProjectionMatrix()  * GetViewMatrix() * Convert::Vec3ToVec4(worldPoint);
		retPos.x = point.x / point.w;
		retPos.y = point.y / point.w;
		retPos.z /= point.w;

		return retPos;
	}


	const vvision::mat4f& Camera::GetProjectionMatrix()
	{
		return m_mProjection;
	}

	const vvision::mat4f& Camera::GetViewInverseMatrix()
	{
		m_mViewInverse = m_mView.inverse();
		return m_mViewInverse;
	}


	const vvision::mat4f& Camera::GetProjectInverseMatrix()
	{
		return m_mProjectInverse;
	}

	void Camera::ClearBackGround()
	{
		GetRenderSystem()->Clear(mGameObject->Color, m_clearType);
	}

	void Camera::SetClearType(DWORD clearType)
	{
		m_clearType = clearType;
	}


	void Camera::ChangeViewport(float aspect)
	{
		if (Perspective && RTTs.size() == 0)
		{
			m_mProjection = mat4f::createPerspective(Fov, aspect, Near, Far);
			m_mProjectInverse = m_mProjection.inverse();
		}
	}

	RenderQueue * Camera::GetRenderQueue()
	{
		return m_RenderQueue;
	}

	int Camera::GetDepth()
	{
		return m_nDepth;
	}

	void Camera::SetDepth(int depth)
	{
		m_nDepth = depth;
		SceneManager::GetCurrentScene()->SortCamera();
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
		if (Perspective)
		{
			m_mProjection = mat4f::createPerspective(Fov, rtt->GetWidth() / rtt->GetHeight(), Near, Far);
			m_mProjectInverse = m_mProjection.inverse();
		}
	}

	const mat4f& Camera::GetViewMatrix()
	{		
		return m_mView;
	}


	void Camera::SetViewMatrix(mat4f viewMat)
	{
		m_mView = viewMat;
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


	E3DEngine::Ray Camera::ScreenPointToRay(vec2f mousePos)
	{
		Ray ray;
		ray.From = Transform->GetPosition();

		vec3f to(0, 0, Far);
		to = to * GetForwardVector();

		ray.To = GetWorldPointWithScreenPoint(mousePos.x, mousePos.y, to.z);

		return ray;
	}


	float Camera::GetPitch()
	{
		return m_pitch;
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

	void Camera::ClearRT()
	{
		RTTs.clear();
	}


	bool Camera::Render2CubeMap(CubeMapTexture *cubeMap, int textureWidth /*= 512*/, int textureHeight /*= 512*/)
	{
		// TODO
		return false;
	}


	E3DEngine::Render2Texture * Camera::GetRenderTexture()
	{
		if (RTTs.empty())
		{
			return nullptr;
		}
		return *RTTs.begin();
	}


	void Camera::SetIsShadowCamera()
	{
		m_bIsShadowCamera = true;
	}

	float * Camera::normal(float *plans)
	{
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
		Debug::Log(ell_Warning, "first %f, %f, %f, %f", m_Plans[0][0], m_Plans[0][1], m_Plans[0][2], m_Plans[0][3]);
		m_Plans[0] = normal(m_Plans[0]);
		//第二个面
		m_Plans[1][0] = mMvpgMatrix[ 3] + mMvpgMatrix[ 0];
		m_Plans[1][1] = mMvpgMatrix[ 7] + mMvpgMatrix[ 4];
		m_Plans[1][2] = mMvpgMatrix[11] + mMvpgMatrix[ 8];
		m_Plans[1][3] = mMvpgMatrix[15] + mMvpgMatrix[12];
		Debug::Log(ell_Warning, "sceond %f, %f, %f, %f", m_Plans[1][0], m_Plans[1][1], m_Plans[1][2], m_Plans[1][3]);
		m_Plans[1] = normal(m_Plans[1]);
		//第三个面
		m_Plans[2][0] = mMvpgMatrix[ 3] + mMvpgMatrix[ 1];
		m_Plans[2][1] = mMvpgMatrix[ 7] + mMvpgMatrix[ 5];
		m_Plans[2][2] = mMvpgMatrix[11] + mMvpgMatrix[ 9];
		m_Plans[2][3] = mMvpgMatrix[15] + mMvpgMatrix[13];
		
		Debug::Log(ell_Warning, "third %f, %f, %f, %f", m_Plans[2][0], m_Plans[2][1], m_Plans[2][2], m_Plans[2][3]);
		m_Plans[2] = normal(m_Plans[2]);
		//第四个面
		m_Plans[3][0] = mMvpgMatrix[ 3] - mMvpgMatrix[ 1];
		m_Plans[3][1] = mMvpgMatrix[ 7] - mMvpgMatrix[ 5];
		m_Plans[3][2] = mMvpgMatrix[11] - mMvpgMatrix[ 9];
		m_Plans[3][3] = mMvpgMatrix[15] - mMvpgMatrix[13];
		
		Debug::Log(ell_Warning, "fourth %f, %f, %f, %f", m_Plans[3][0], m_Plans[3][1], m_Plans[3][2], m_Plans[3][3]);
		m_Plans[3] = normal(m_Plans[3]);
		//第五个面
		m_Plans[4][0] = mMvpgMatrix[ 3] - mMvpgMatrix[ 2];
		m_Plans[4][1] = mMvpgMatrix[ 7] - mMvpgMatrix[ 6];
		m_Plans[4][2] = mMvpgMatrix[11] - mMvpgMatrix[10];
		m_Plans[4][3] = mMvpgMatrix[15] - mMvpgMatrix[14];
		
		Debug::Log(ell_Warning, "fiveth %f, %f, %f, %f", m_Plans[4][0], m_Plans[4][1], m_Plans[4][2], m_Plans[4][3]);
		m_Plans[4] = normal(m_Plans[4]);
		//第六个面
		m_Plans[5][0] = mMvpgMatrix[ 3] + mMvpgMatrix[ 2];
		m_Plans[5][1] = mMvpgMatrix[ 7] + mMvpgMatrix[ 6];
		m_Plans[5][2] = mMvpgMatrix[11] + mMvpgMatrix[10];
		m_Plans[5][3] = mMvpgMatrix[15] + mMvpgMatrix[14];

		Debug::Log(ell_Warning, "sixth %f, %f, %f, %f", m_Plans[5][0], m_Plans[5][1], m_Plans[5][2], m_Plans[5][3]);
		m_Plans[5] = normal(m_Plans[5]);
	}

	float Camera::GetYaw()
	{
		return m_yaw;
	}


	float Camera::GetRoll()
	{
		return m_roll;
	}


	float Camera::GetFaceArea()
	{
		return m_facearea;
	}

}
