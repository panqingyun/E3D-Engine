#pragma once

#include "E3DGameObject.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Coordinate : public GameObject
	{
	public:
		Coordinate();
		virtual void SetRenderer(Renderer * renderer);
		virtual void TransferRender() override;
		virtual void SetActive(bool isActive) override;
		virtual void PrepareUpdate(float deltaTime) override;
		void SetTransform(CTransform * objTransform);
	private:
		CTransform * m_PobjTransform;
		mat4f		 m_OrthoMatrix;
	};
}