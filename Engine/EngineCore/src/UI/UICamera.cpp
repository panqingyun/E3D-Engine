#include "UICamera.h"
#include "../Source/EngineDelegate.h"

E3DEngine::UI::UICamera::UICamera(const vec3f& position, const vec3f& target, vec3f up, float32 zNear, float32 zFar)
{
	float screenWidth = GetRenderSystem()->getFrameWidth();
	float screenHeight = GetRenderSystem()->getFrameHeight();

	float left = -screenWidth / 2.0f;
	float top = screenHeight / 2.0f;
	float right = screenWidth / 2.0f;
	float bottom = -screenHeight / 2.0f;
	m_pCamera = new Camera(position, target, up, left, right, bottom, top, zNear, zFar);
}

const mat4f& E3DEngine::UI::UICamera::GetProjectionMatrix()
{
	return m_pCamera->GetProjectionMatrix();
}

const mat4f& E3DEngine::UI::UICamera::GetViewInverseMatrix()
{

	return m_pCamera->GetViewInverseMatrix();
}

const mat4f& E3DEngine::UI::UICamera::GetProjectInverseMatrix()
{

	return m_pCamera->GetProjectInverseMatrix();
}

const mat4f& E3DEngine::UI::UICamera::GetViewMatrix()
{
	return m_pCamera->GetViewMatrix();
}

const Quatf& E3DEngine::UI::UICamera::GetQuaternionRepresentation()
{
	return m_pCamera->GetQuaternionRepresentation();
}

vec3f E3DEngine::UI::UICamera::GetPosition()
{
	return GetPosition();
}

vec3f E3DEngine::UI::UICamera::GetForwardVector()
{
	return GetForwardVector();
}

vec3f E3DEngine::UI::UICamera::GetUpVector()
{
	return GetUpVector();
}

vec4f E3DEngine::UI::UICamera::GetWorldPointWithX(float x, float y, float z)
{
	return GetWorldPointWithX(x, y, z);
}

vec3f E3DEngine::UI::UICamera::GetRigthVector()
{
	return GetRigthVector();
}

void E3DEngine::UI::UICamera::SetProjectionMatrix(const mat4f& projection)
{
	m_pCamera->SetProjectionMatrix(projection);
}

void E3DEngine::UI::UICamera::SetPosition(const vec3f& position)
{
	m_pCamera->SetPosition(position);
}

void E3DEngine::UI::UICamera::SetQuaternion(Quatf new_quat)
{
	m_pCamera->SetQuaternion(new_quat);
}

void E3DEngine::UI::UICamera::SetRotateByMat(mat4f new_mat, bool isCameraFront)
{
	m_pCamera->SetRotateByMat(new_mat, isCameraFront);
}

void E3DEngine::UI::UICamera::SetRotate(float x, float y, float z)
{
	m_pCamera->SetRotate(x, y, z);
}

float E3DEngine::UI::UICamera::GetFaceArea()
{
	return m_pCamera->GetFaceArea();
}

bool E3DEngine::UI::UICamera::boundingBoxFrustum(vec3f position, float size)
{
	return m_pCamera->boundingBoxFrustum(position, size);
}
