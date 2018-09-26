#pragma once
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//
#include "E3DGameObject.h"
#include "../Source/E3DVertex.h"

namespace E3DEngine
{
	class Renderer;
	class E3D_EXPORT_DLL Sphere : public GameObject
	{
	public:
		Sphere();
		void Create(float r);
		virtual void SetActive(bool isActive) override;
		virtual void TransformChange() override;
	protected:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;
	};
}