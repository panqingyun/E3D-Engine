//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//
#include "E3DSphere.h"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"

E3DEngine::Sphere::Sphere()
{
	CreateBehaviour();
}

void E3DEngine::Sphere::Create(float R)
{
	int rowNumber = 181;
	int colNumber = 181;
	m_vecVertex.resize(rowNumber * colNumber);
	int indexSize = (rowNumber - 1) * (colNumber - 1) * 6;
	m_vecIndex.resize(indexSize);
	int index = 0;
	int vIndex = 0;
	float dAlpha = 0, dBeta = 0;
	for (int alpha = 0; alpha < rowNumber; alpha ++)
	{
		dAlpha = DEG2RAD((90 - alpha));
		for (int beta = 0; beta < colNumber; beta++)
		{
			dBeta = DEG2RAD(beta * 2);
			float z = R * cos(dBeta) * cos(dAlpha);
			float x = R * sin(dBeta) * cos(dAlpha);
			float y = R * sin(dAlpha);
			m_vecVertex[vIndex].SetPosition(x, y, z);
			m_vecVertex[vIndex].SetColor(1, 1, 1, 1);
			m_vecVertex[vIndex].SetNormal(x, y, z);
			m_vecVertex[vIndex].SettextureCoord1((float)beta / (colNumber - 1), (float)alpha/ (rowNumber - 1));
			vIndex++;
			if (alpha < rowNumber - 1 && beta < colNumber - 1)
			{
				m_vecIndex[index++] = (alpha * rowNumber + beta); // 0
				m_vecIndex[index++] = ((alpha + 1) * rowNumber + beta);// 360
				m_vecIndex[index++] = ((alpha + 1) * rowNumber + beta + 1);

				m_vecIndex[index++] = ((alpha + 1) * rowNumber + beta + 1);
				m_vecIndex[index++] = (alpha * rowNumber + beta + 1);
				m_vecIndex[index++] = (alpha * rowNumber + beta); // 1
			}
		}
	}
	size.x = R;
	size.y = R;
	size.z = R;
	IsActive = false;
}

void E3DEngine::Sphere::SetActive(bool isActive)
{
	if (isActive == IsActive)
	{
		return;
	}
	GameObject::SetActive(isActive);
	if (m_pRenderer == nullptr)
	{
		return;
	}
	m_pRenderer->RemoveInRenderer(ID);
	if (isActive)
	{
		m_pRenderer->FillBegin(ID);
		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			m_pRenderer->FillVertex(m_vecVertex[i]);
		}

		for (int i = 0; i < m_vecIndex.size(); i++)
		{
			m_pRenderer->FillIndex(m_vecIndex[i]);
		}
		m_pRenderer->FillEnd(ID, m_vecVertex.size());
	}
	m_pRenderer->TransformChange();
}

void E3DEngine::Sphere::TransformChange()
{
	if (pCamera && !pCamera->boundingBoxFrustum(Transform->Position, 100))
	{
		return;
	}
	m_pRenderer->SetTransform(Transform);
	/*Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
	int vertexStartIndex = mRenderer->GetRendererBuffer(ID)->VertextStartIndex;
	std::vector<Vertex>::iterator it = m_vecVertex.begin();
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecVertex[i].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
		m_vecVertex[i].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);;
		m_vecVertex[i].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
		mRenderer->Vertices[vertexStartIndex + i] = m_vecVertex[i];
	}*/
	//m_pRenderer->TransformChange();
}

void E3DEngine::Sphere::CreateBehaviour()
{
	mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
	NEW_INSTANCE(Sphere);
	setBehaviourDefaultValue();
}

void E3DEngine::Sphere::setBehaviourDefaultValue()
{
	GameObject::setBehaviourDefaultValue();
}

