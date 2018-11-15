#pragma once
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//
#include "E3DComponent.hpp"
#include "../Source/E3DVertex.h"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Sphere : public Component
	{
		DECLARE_CLASS(Sphere)
	public:
		Sphere();
		virtual void Awake() override;

	private:
		void create(float r);
	};
}