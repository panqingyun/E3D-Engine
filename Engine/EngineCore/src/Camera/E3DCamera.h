//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-10 PanQingyun. All rights reserved. *************************//
#ifndef __E3D_CAMERA_H__
#define __E3D_CAMERA_H__

#include <float.h>
#include <complex>
#include "../Object/E3DGameObject.h"
#include "../Source/vmath.h"

namespace E3DEngine
{
	class RenderQueue;
	class Render2Texture;
	class CubeMapTexture;
	struct Ray;
	class E3D_EXPORT_DLL Camera : public GameObject
	{
		friend class Render2Texture;
	public:
		static Camera * CreateCamera(bool isPerspective = true);

		Camera(const vec3f& position, const vec3f& target, float32 fov, const vec3f& up = vec3f(0.0, -1.0, 0.0), float32 zNear = 5.0f, float32 zFar = 10000.0f, float32 aspect = 9.0f/16.0f);
		
		Camera(const vec3f& position, const vec3f& target, vec3f up, float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar);
		
		~Camera();

	public:
		void Render();
		void ClearBackGround();
		void SetClearColor(Color4 color);
		void SetClearType(DWORD clearType);
		void ChangeViewport(float aspect);
		RenderQueue * GetRenderQueue();
		virtual void SetLayerMask(DWORD layerMask) override;
		int GetDepth();
		void SetDepth(int depth);
		void SetRenderTexture(Render2Texture * rtt);
		vec3f GetWorldPointWithScreenPoint(float x, float y, float z);
		vec3f GetScreenPointWithWorlPoint(const vec3f& worldPoint);
		vec3f GetClipPoint(const vec3f &worldPoint);
		const mat4f& GetProjectionMatrix();		
		const mat4f& GetViewInverseMatrix();
		const mat4f& GetProjectInverseMatrix();		
		void TransformChange() override;
		const mat4f& GetViewMatrix();		
		void SetViewMatrix(mat4f viewMat);
		vec3f GetForwardVector();		
		vec3f GetUpVector();		
		vec4f GetWorldPoint(float x,float y,float z);	
		vec3f GetRigthVector();		
		void SetProjectionMatrix(const mat4f& projection);
		Ray ScreenPointToRay(vec2f mousePos);	
		float GetPitch();
		float GetYaw();
		float GetRoll();
		float GetFaceArea();		
		bool boundingBoxFrustum(vec3f position, float size);
		vec4f GetClearColor();
		void ClearRT();
		bool Render2CubeMap(CubeMapTexture *cubeMap, int textureWidth = 512, int textureHeight = 512);
		Render2Texture *GetRenderTexture();
	private:
		float DistanceBetweenPoints(vec3f p1,vec3f p2);
		vec3f GetThirdPoint(vec3f p1,vec3f p2,float z3);		
		//剪裁
		bool boundingBoxFrustum(float x,float y,float z,float size);
		void calculateFrustumPlanes();
		float * normal(float *plans);
		void render();
		//int GetFacePos(vec3f v1,vec3f v2,vec3f v3);
	private:
		mat4f m_mView;
		mat4f m_mProjection;		
		mat4f m_mViewInverse;
		mat4f m_mProjectInverse;
		
		float m_pitch;
		float m_yaw;
		float m_roll;
		float m_facearea;
		float m_fov;
		float m_aspect;
		float m_near;
		float m_far;
		
		bool isPerspective;
		std::vector<float *> m_Plans;
		float *m_Temp;
		RenderQueue * m_RenderQueue;
		Color4 m_clearColor; 
		int m_nDepth;
		DWORD m_clearType;
		std::list<Render2Texture *> RTTs;

	};
}
#endif
