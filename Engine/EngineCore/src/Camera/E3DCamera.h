/* CameraEntity.h
 *
 * Copyright (C) 2012 Abdallah DIB.
 * All rights reserved. Email: Abdallah.dib@virtual-vison.net
 * Web: <http://www.virutal-vision.net/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef VVISION_CameraEntity_h
#define VVISION_CameraEntity_h

#include <float.h>
#include <complex>
#include <iostream>
#include <vector>
#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
	class RenderQueue;
	class Render2Texture;
	class Camera : public GameObject
	{
		friend class Render2Texture;
	public:

		static Camera * CreateCamera();
		/** create a perspective camera
		 @param position camera position
		 @param target camera target point
		 @param fov field of view
		 @param up the up vector
		 @param zNear near clipping plane of the camera
		 @param zFar far clipping plane of the camera
		 @param aspect ration of the camera ( width / height)
		 */
		Camera(const vec3f& position, const vec3f& target, float32 fov, const vec3f& up = vec3f(0.0, -1.0, 0.0), float32 zNear = 5.0f, float32 zFar = 10000.0f, float32 aspect = 9.0f/16.0f);
		
		Camera(const vec3f& position, const vec3f& target, vec3f up, float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar);
		
		/** destructor*/
		~Camera();
		
		void Render(float deltaTime);

		void Clear();

		void SetClearColor(Color4 color);

		void SetClearType(DWORD clearType);

		void FrameSizeChange(float aspect);

		RenderQueue * GetRenderQueue();

		virtual void SetLayerMask(DWORD layerMask) override;

		int GetDepth();

		void SetDepth(int depth);

		void SetRenderTexture(Render2Texture * rtt);

		vec3f GetWorldPointWithScreenPoint(float x, float y, float z);

		/** return the projection matrix of the camera*/
		const mat4f& GetProjectionMatrix() {return m_mProjection;}
		
		const mat4f& GetViewInverseMatrix() {return m_mViewInverse;}
		const mat4f& GetProjectInverseMatrix() {return m_mProjectInverse;}
		
		void TransformChange() override;

		/** return the view matrix  ( this is extracted from the quaternion*/
		const mat4f& GetViewMatrix();
		
		/** forward vector*/
		vec3f GetForwardVector();
		
		/** the up vector*/
		vec3f GetUpVector();
		
		vec4f GetWorldPoint(float x,float y,float z);
		
		/** get right vector*/
		vec3f GetRigthVector();
		
		/** set a new projection matrix for the camera ( ortho, frustum, todo: add helper for creating ortho frustum)*/
		void SetProjectionMatrix(const mat4f& projection);
	
		float GetPitch(){return m_pitch;}
		float GetYaw(){return m_yaw;}
		float GetRoll(){return m_roll;}
		float GetFaceArea(){return m_facearea;}
		
		bool boundingBoxFrustum(vec3f position, float size);
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;
	private:
		float DistanceBetweenPoints(vec3f p1,vec3f p2);
		vec3f GetThirdPoint(vec3f p1,vec3f p2,float z3);
		
		//剪裁
		bool boundingBoxFrustum(float x,float y,float z,float size);
		void calculateFrustumPlanes();
		float * normal(float *plans);
		void render(float deltaTime);
		//int GetFacePos(vec3f v1,vec3f v2,vec3f v3);
	private:
		/** view matrix*/
		mat4f m_mView;
		/** projection*/
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
