#include "E3DLine.h"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Source/E3DVertexManager.h"

namespace E3DEngine
{
	Line::Line(vec3f start, vec3f end)
	{
		IsActive = false;
		VertexBufferName = "Line";
		if (VertexManager::GetVertex(VertexBufferName).empty())
		{
			std::vector<Vertex> vecVertex;
			vecVertex.resize(3);

			vecVertex[0].SetPosition(start.x, start.y, start.z);
			vecVertex[0].SetColor(1, 1, 1, 1);
			vecVertex[1].SetPosition(end.x, end.y, end.z);
			vecVertex[1].SetColor(1, 1, 1, 1);
			vecVertex[2].SetPosition(start.x, start.y, start.z);
			vecVertex[2].SetColor(1, 1, 1, 1);

			std::vector<UINT> vecIndex;
			vecIndex.resize(3);
			UINT index[3] =
			{
				0 , 1, 2
			};

			memcpy(vecIndex.data(), index, sizeof(UINT) * 3);
			VertexManager::Add(vecVertex, vecIndex, VertexBufferName);
		}
		mSceneObjectType = TP_Line;
	}

	Line::~Line()
	{
	}

	void Line::TransferRender()
	{
		GameObject::TransferRender();
		m_pRenderer->SetDrawModule(eDM_LINES);
		IsActive = false;
		SetActive(true);
	}

	void Line::SetActive(bool isActive)
	{
		if (isActive == IsActive)
		{
			return;
		}
		GameObject::SetActive(isActive);
		fillRender(isActive);
	}

}