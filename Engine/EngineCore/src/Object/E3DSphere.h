#pragma once

#include "E3DGameObject.h"
#include "../Source/E3DVertex.h"

namespace E3DEngine
{
	class Renderer;
	class Sphere : public GameObject
	{
	public:
		Sphere()
		{
			CreateBehaviour();
		}
		void Create(float r);
		virtual void SetActive(bool isActive) override;
		virtual void TransformChange() override;
		virtual void SetMaterial(Material *material) override;
	protected:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;
	};
}