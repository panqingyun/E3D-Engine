#ifndef __UI_CAMERA_H__
#define __UI_CAMERA_H__

#include "../Source/Interface.h"
#include "../Camera/E3DCamera.h"

namespace E3DEngine
{
	namespace UI
	{
		/************************************************************************/
		/* 																		*/
		/* 																		*/
		/************************************************************************/
		class UICamera extends Ref
		{
		public:
			UICamera(const vec3f& position, const vec3f& target, vec3f up, float32 zNear, float32 zFar);

			const mat4f& GetProjectionMatrix();
			const mat4f& GetViewInverseMatrix();
			const mat4f& GetProjectInverseMatrix();
			const mat4f& GetViewMatrix();
		
		public:
			vec3f GetForwardVector();			
			vec3f GetUpVector();
			vec4f GetWorldPointWithX(float x, float y, float z);
			vec3f GetRigthVector();
			float GetFaceArea();

		public:
			void SetProjectionMatrix(const mat4f& projection);
			void SetPosition(const vec3f& position);
			void SetQuaternion(Quatf new_quat);
			void SetRotate(float x, float y, float z);
		
		public:
			bool boundingBoxFrustum(vec3f position, float size);

		private:
			Camera * m_pCamera;
		};
	}
}

#endif
