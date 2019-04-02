//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-10 PanQingyun. All rights reserved. *************************//
// E3DCamera.h
// 摄像机
// 创建： 2017-1-10
// 
// 修改：2019-4-2
//		修改函数名 将RenderTexture改为TargetTexture 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __E3D_CAMERA_H__
#define __E3D_CAMERA_H__

#include <float.h>
#include <complex>
#include "../Object/E3DGameObject.h"
#include "../Source/vmath.h"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	class RenderQueue;
	class Render2Texture;
	class CubeMapTexture;
	struct Ray;
	class E3D_EXPORT_DLL Camera : public Component
	{
		DECLARE_CLASS(Camera)
		friend class Render2Texture;
	public:
		Camera();
		~Camera();

	private:
		void createCamera(const vec3f& position, const vec3f& target, float32 fov, const vec3f& up = vec3f(0.0, -1.0, 0.0), float32 zNear = 5.0f, float32 zFar = 10000.0f, float32 aspect = 9.0f/16.0f);
		void createCamera(const vec3f& position, const vec3f& target, vec3f up, float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar);
		
	public: 
		virtual void Awake() override;
		virtual void TransformChange() override;
		virtual void Start() override;

	public:
		void Render();
		void ClearBackGround();
		void SetClearType(DWORD clearType);
		void ChangeViewport(float aspect);
		RenderQueue * GetRenderQueue();
		vec3f GetWorldPointWithScreenPoint(float x, float y, float z);
		vec3f GetScreenPointWithWorlPoint(const vec3f& worldPoint);
		vec3f GetClipPoint(const vec3f &worldPoint);
		const mat4f& GetProjectionMatrix();		
		const mat4f& GetViewInverseMatrix();
		const mat4f& GetProjectInverseMatrix();		
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

		void ClearTargetTexture();
		bool Render2CubeMap(CubeMapTexture *cubeMap, int textureWidth = 512, int textureHeight = 512);
		void SetTargetTexture(Render2Texture * rtt);
		Render2Texture *GetTargetTexture();
		void SetIsShadowCamera();
		bool GetIsShadowCamera() { return m_bIsShadowCamera; }

	public:
		DECLARE_PROPERTY(Camera, bool, Perspective);
		DECLARE_PROPERTY(Camera, float, Near);
		DECLARE_PROPERTY(Camera, float, Far);
		DECLARE_PROPERTY(Camera, float, Size);
		DECLARE_PROPERTY(Camera, vec3f, Pos);
		DECLARE_PROPERTY(Camera, vec3f, Target);
		DECLARE_PROPERTY(Camera, float, Fov);
		DECLARE_PROPERTY(Camera, std::string, RenderTextureFile);
		DECLARE_PROPERTY(Camera, int, RenderTextureID);
		DECLARE_PROPERTY(Camera, int, Depth);
		virtual void registProperty() override
		{
			SAVE_PROPERTY(Perspective, FT_BOOLEAN);
			SAVE_PROPERTY(Near, FT_FLOAT);
			SAVE_PROPERTY(Far, FT_FLOAT);
			SAVE_PROPERTY(Size, FT_FLOAT);
			SAVE_PROPERTY(Pos, FT_VECTOR3);
			SAVE_PROPERTY(Target, FT_VECTOR3);
			SAVE_PROPERTY(Fov, FT_FLOAT);
			SAVE_PROPERTY(RenderTextureFile, FT_STRING);
			SAVE_PROPERTY(RenderTextureID, FT_INT);
			SAVE_PROPERTY(Depth, FT_INT);
		}

	private:
		bool boundingBoxFrustum(vec3f position, float size);
		float DistanceBetweenPoints(vec3f p1,vec3f p2);
		vec3f GetThirdPoint(vec3f p1,vec3f p2,float z3);		
		//剪裁
		bool boundingBoxFrustum(float x,float y,float z,float size);
		void calculateFrustumPlanes();
		float * normal(float *plans);
		void render();

	private:
		mat4f m_mView;
		mat4f m_mProjection;		
		mat4f m_mViewInverse;
		mat4f m_mProjectInverse;
		
		float m_pitch;
		float m_yaw;
		float m_roll;
		float m_aspect;
		bool  m_bIsShadowCamera;
		bool  m_bUseDefaultRtt;
		std::vector<float *> m_Plans;
		float *m_Temp;
		RenderQueue * m_RenderQueue;
		DWORD m_clearType;
		Render2Texture * m_pRTT;

	};
}
#endif
