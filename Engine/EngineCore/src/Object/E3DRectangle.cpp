
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//

#include "E3DRectangle.hpp"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"

namespace E3DEngine
{
	void Rectangle::CreateShape(float width, float height)
	{
		m_vecVertex.resize(4);
		m_vecVertex[0].SetPosition(-width/2, height/2, 0);
		m_vecVertex[0].SetNormal(0, 0, 1);
		m_vecVertex[0].SetColor(1, 1, 1, 1);
		m_vecVertex[0].SettextureCoord1(0, 0);
		m_vecVertex[1].SetPosition(-width/2, -height/2, 0);
		m_vecVertex[1].SetNormal(0, 0, 1);
		m_vecVertex[1].SetColor(1, 1, 1, 1);
		m_vecVertex[1].SettextureCoord1(0, 1);
		m_vecVertex[2].SetPosition(width/2, -height/2, 0);
		m_vecVertex[2].SetNormal(0, 0, 1);
		m_vecVertex[2].SetColor(1, 1, 1, 1);
		m_vecVertex[2].SettextureCoord1(1, 1);
		m_vecVertex[3].SetPosition(width/2, height/2, 0);
		m_vecVertex[3].SetNormal(0, 0, 1);
		m_vecVertex[3].SetColor(1, 1, 1, 1);
		m_vecVertex[3].SettextureCoord1(1, 0);
		m_vecIndex.resize(6);
		m_vecIndex[0] = 0;
		m_vecIndex[1] = 1;
		m_vecIndex[2] = 2;
		m_vecIndex[3] = 2;
		m_vecIndex[4] = 3;
		m_vecIndex[5] = 0;
		IsActive = false;
		CreateBehaviour();
	}
	
	void Rectangle::SetActive(bool isActive)
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
