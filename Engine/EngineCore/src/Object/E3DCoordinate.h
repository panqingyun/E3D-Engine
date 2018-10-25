#pragma once

#include "E3DGameObject.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Coordinate : public GameObject
	{
	public:
		Coordinate();
		virtual void SetRenderer(Renderer * renderer);
		virtual void SetActive(bool isActive) override;
	};
}