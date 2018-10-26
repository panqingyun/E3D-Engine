#pragma once

#include "E3DGameObject.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Coordinate : public GameObject
	{
	public:
		Coordinate();
		virtual void TransferRender() override;
	};
}