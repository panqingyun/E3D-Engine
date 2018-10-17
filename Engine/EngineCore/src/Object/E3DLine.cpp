#include "E3DLine.h"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"

namespace E3DEngine
{
	Line::Line(vec3f start, vec3f end)
	{
		IsActive = false;
		m_vecVertex.resize(3);

		m_vecVertex[0].SetPosition(start.x, start.y, start.z);
		m_vecVertex[0].SetColor(1, 1, 1, 1);
		m_vecVertex[1].SetPosition(end.x, end.y, end.z);
		m_vecVertex[1].SetColor(1, 1, 1, 1);
		m_vecVertex[2].SetPosition(start.x, start.y, start.z);
		m_vecVertex[2].SetColor(1, 1, 1, 1);

		m_vecIndex.resize(3);
		UINT index[3] =
		{
			0 , 1, 2
		};

		memcpy(m_vecIndex.data(), index, sizeof(UINT) * 3);
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
		Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
		if (isActive)
		{
			mRenderer->FillBegin(ID);
			for (int i = 0; i < m_vecVertex.size(); i++)
			{
				mRenderer->FillVertex(m_vecVertex[i]);
			}

			for (int i = 0; i < m_vecIndex.size(); i++)
			{
				mRenderer->FillIndex(m_vecIndex[i]);
			}

			mRenderer->FillEnd(ID, m_vecVertex.size(), m_vecIndex.size());
		}
		else
		{
			mRenderer->RemoveInRenderer(ID);
		}
		m_pRenderer->TransformChange();
	}

}