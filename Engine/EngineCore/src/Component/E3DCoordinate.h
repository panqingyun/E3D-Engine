#pragma once

#include "E3DComponent.hpp"
#include "..\Source\ClassFactory.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Coordinate : public Component
	{
		DECLARE_CLASS(Coordinate)
	public:
		Coordinate();
		virtual void Awake() override;
	};
}