#include "E3DCoordinate.h"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "E3DTransform.hpp"
#include "E3DGameObject.h"
#include "../Camera/E3DCamera.h"

namespace E3DEngine
{
	Coordinate::Coordinate()
	{
		IsActive = false;
		m_vecVertex.resize(6);
		// x r
		m_vecVertex[0].SetPosition(0, 0, 0);
		m_vecVertex[0].SetColor(1, 0, 0, 1);
		m_vecVertex[1].SetPosition(5, 0, 0);
		m_vecVertex[1].SetColor(1, 0, 0, 1);
		// y g
		m_vecVertex[2].SetPosition(0, 0, 0);
		m_vecVertex[2].SetColor(0, 1, 0, 1);
		m_vecVertex[3].SetPosition(0, 5, 0);
		m_vecVertex[3].SetColor(0, 1, 0, 1);
		// z b
		m_vecVertex[4].SetPosition(0, 0, 0);
		m_vecVertex[4].SetColor(0, 0, 1, 1);
		m_vecVertex[5].SetPosition(0, 0, 5);
		m_vecVertex[5].SetColor(0, 0, 1, 1);


		m_vecIndex.resize(9);
		UINT index[9] =
		{
			0, 1, 0,
			2, 2, 3,
			4, 5, 4
		};

		memcpy(m_vecIndex.data(), index, sizeof(UINT) * 9);
		mSceneObjectType = TP_Line;
		Transform->SetNeedUpdate(false);
		CreateBehaviour();
	}

	void Coordinate::SetRenderer(Renderer * renderer)
	{
		GameObject::SetRenderer(renderer);
		m_pRenderer->SetDrawModule(eDM_LINES);
	}

	void Coordinate::TransferRender()
	{
		
	}

	void Coordinate::SetActive(bool isActive)
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

	void Coordinate::PrepareUpdate(float deltaTime)
	{
		if (m_PobjTransform == nullptr)
		{
			return;
		}
		Transform->WorldMatrix = m_PobjTransform->WorldMatrix;
		mat4f scale = mat4f::createScaleMatrix(1.0 / m_PobjTransform->Scale.x, 1.0 / m_PobjTransform->Scale.y, 1.0 / m_PobjTransform->Scale.z);
		Transform->WorldMatrix = Transform->WorldMatrix * scale;
	}

	void Coordinate::SetTransform(CTransform * objTransform)
	{
		if (objTransform != nullptr)
		{
			m_PobjTransform = objTransform;
			Transform->WorldMatrix = objTransform->WorldMatrix;	
			mat4f scale = mat4f::createScaleMatrix(1.0 / objTransform->Scale.x, 1.0 / objTransform->Scale.y, 1.0 / objTransform->Scale.z);
			Transform->WorldMatrix = Transform->WorldMatrix * scale;
			m_pRenderer->SetTransform(Transform);
		}
	}

}