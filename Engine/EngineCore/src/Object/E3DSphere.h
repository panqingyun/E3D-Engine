#pragma once

#include "E3DGameObject.h"
#include "../Source/E3DVertex.h"

namespace E3DEngine
{
	class Renderer;
	class Sphere extends GameObject
	{
	public:
		void Create(float r);
		virtual void TrampolinePage();
		virtual void SetActive(bool isActive) override;
		virtual void TransformChange() override;
	protected:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;
	private:
		Renderer * m_pRenderer;
		std::vector<Vertex> m_vecVertex;
		std::vector<uint> m_vecIndex;
		vec3f size;
	};
}