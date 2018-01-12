#pragma once

#include "E3DBox.h"

namespace E3DEngine
{
	class SkyBox : public Box
	{
	public:
		virtual void Create(float l, float w, float h) override;
		virtual void SetMaterial(Material * material) override;
		virtual void PrepareUpdate(float deltaTime) override;
	};
}