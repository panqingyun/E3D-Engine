//*********************************
// Create by PanQingyun
// 2017 - 11 -28
//********************************
#pragma once

#include "E3DGameObject.h"
#include "../Source/E3DVertex.h"

namespace E3DEngine
{
	class Renderer;
	class Box : public GameObject
	{
	public:
		Box()
		{
			CreateBehaviour();
		}
		void Create(float l, float w, float h);
		virtual void SetMaterial(Material * material);
		virtual void PrepareUpdate(float deltaTime) override;
		virtual void SetActive(bool isActive) override;
		virtual void AfterUpdate(float deltaTime) override;
		virtual void TransformChange() override;
	protected:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;
	};
}