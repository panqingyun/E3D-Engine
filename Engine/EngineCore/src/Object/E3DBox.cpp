
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-11-28 PanQingyun. All rights reserved. ************************//

#include "E3DBox.h"
#include "../Scene/E3DSceneManager.hpp"
#include "../Object/E3DTransform.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"

void E3DEngine::Box::Create(float l, float w, float h)
{
	IsActive = false;
	m_vecVertex.resize(24);
	// 前
	m_vecVertex[0].SetPosition(-l / 2, h / 2, w / 2);
	m_vecVertex[0].SetColor(1, 0, 1, 1);
	m_vecVertex[0].SetNormal(0, 0, 1);
	m_vecVertex[0].SettextureCoord1(0, 1);
	m_vecVertex[1].SetPosition(-l / 2, -h / 2, w / 2);
	m_vecVertex[1].SetColor(1, 0, 1, 1);
	m_vecVertex[1].SetNormal(0, 0, 1);
	m_vecVertex[1].SettextureCoord1(0, 0);
	m_vecVertex[2].SetPosition(l / 2, -h / 2, w / 2);
	m_vecVertex[2].SetColor(1, 0, 1, 1);
	m_vecVertex[2].SetNormal(0, 0, 1);
	m_vecVertex[2].SettextureCoord1(1, 0);
	m_vecVertex[3].SetPosition(l / 2, h / 2, w / 2);
	m_vecVertex[3].SetColor(1, 0, 1, 1);
	m_vecVertex[3].SetNormal(0, 0, 1);
	m_vecVertex[2].SettextureCoord1(1, 1);
	// 上
	m_vecVertex[4].SetPosition(-l / 2, h / 2, w / 2);
	m_vecVertex[4].SetColor(1, 1, 1, 1);
	m_vecVertex[4].SetNormal(0, 1, 0);
	m_vecVertex[4].SettextureCoord1(0, 1);
	m_vecVertex[5].SetPosition(l / 2, h / 2, w / 2);
	m_vecVertex[5].SetColor(1, 1, 1, 1);
	m_vecVertex[5].SetNormal(0, 1, 0);
	m_vecVertex[5].SettextureCoord1(0, 0);
	m_vecVertex[6].SetPosition(l / 2, h / 2, -w / 2);
	m_vecVertex[6].SetColor(1, 1, 1, 1);
	m_vecVertex[6].SetNormal(0, 1, 0);
	m_vecVertex[6].SettextureCoord1(1, 0);
	m_vecVertex[7].SetPosition(-l / 2, h / 2, -w / 2);
	m_vecVertex[7].SetColor(1, 1, 1, 1);
	m_vecVertex[7].SetNormal(0, 1, 0);
	m_vecVertex[7].SettextureCoord1(1, 1);
	// 后
	m_vecVertex[8].SetPosition(-l / 2, h / 2, -w / 2);
	m_vecVertex[8].SetColor(0, 1, 1, 1);
	m_vecVertex[8].SetNormal(0, 0, -1);
	m_vecVertex[8].SettextureCoord1(0, 1);
	m_vecVertex[9].SetPosition(l / 2, h / 2, -w / 2);
	m_vecVertex[9].SetColor(0, 1, 1, 1);
	m_vecVertex[9].SetNormal(0, 0, -1);
	m_vecVertex[9].SettextureCoord1(0, 0);
	m_vecVertex[10].SetPosition(l / 2, -h / 2, -w / 2);
	m_vecVertex[10].SetColor(0, 1, 1, 1);
	m_vecVertex[10].SetNormal(0, 0, -1);
	m_vecVertex[10].SettextureCoord1(1, 0);
	m_vecVertex[11].SetPosition(-l / 2, -h / 2, -w / 2);
	m_vecVertex[11].SetColor(0, 1, 1, 1);
	m_vecVertex[11].SetNormal(0, 0, -1);
	m_vecVertex[11].SettextureCoord1(1, 1);
	// 下
	m_vecVertex[12].SetPosition(-l / 2, -h / 2, -w / 2);
	m_vecVertex[12].SetColor(1, 1, 0, 1);
	m_vecVertex[12].SetNormal(0, -1, 0);
	m_vecVertex[12].SettextureCoord1(0, 1);
	m_vecVertex[13].SetPosition(l / 2, -h / 2, -w / 2);
	m_vecVertex[13].SetColor(1, 1, 0, 1);
	m_vecVertex[13].SetNormal(0, -1, 0);
	m_vecVertex[13].SettextureCoord1(0, 0);
	m_vecVertex[14].SetPosition(l / 2, -h / 2, w / 2);
	m_vecVertex[14].SetColor(1, 1, 0, 1);
	m_vecVertex[14].SetNormal(0, -1, 0);
	m_vecVertex[14].SettextureCoord1(1, 0);
	m_vecVertex[15].SetPosition(-l / 2, -h / 2, w / 2);
	m_vecVertex[15].SetColor(1, 1, 0, 1);
	m_vecVertex[15].SetNormal(0, -1, 0);
	m_vecVertex[15].SettextureCoord1(1, 1);
	// 左
	m_vecVertex[16].SetPosition(-l / 2, h / 2, w / 2);
	m_vecVertex[16].SetColor(1, 0, 0, 1);
	m_vecVertex[16].SetNormal(-1, 0, 0);
	m_vecVertex[16].SettextureCoord1(0, 1);
	m_vecVertex[17].SetPosition(-l / 2, h / 2, -w / 2);
	m_vecVertex[17].SetColor(1, 0, 0, 1);
	m_vecVertex[17].SetNormal(-1, 0, 0);
	m_vecVertex[17].SettextureCoord1(0, 0);
	m_vecVertex[18].SetPosition(-l / 2, -h / 2, -w / 2);
	m_vecVertex[18].SetColor(1, 0, 0, 1);
	m_vecVertex[18].SetNormal(-1, 0, 0);
	m_vecVertex[18].SettextureCoord1(1, 0);
	m_vecVertex[19].SetPosition(-l / 2, -h / 2, w / 2);
	m_vecVertex[19].SetColor(1, 0, 0, 1);
	m_vecVertex[19].SetNormal(-1, 0, 0);
	m_vecVertex[19].SettextureCoord1(1, 1);
	// 右
	m_vecVertex[20].SetPosition(l / 2, h / 2, w / 2);
	m_vecVertex[20].SetColor(0, 1, 0, 1);
	m_vecVertex[20].SetNormal(1, 0, 0);
	m_vecVertex[20].SettextureCoord1(0, 1);
	m_vecVertex[21].SetPosition(l / 2, -h / 2, w / 2);
	m_vecVertex[21].SetColor(0, 1, 0, 1);
	m_vecVertex[21].SetNormal(1, 0, 0);
	m_vecVertex[21].SettextureCoord1(0, 0);
	m_vecVertex[22].SetPosition(l / 2, -h / 2, -w / 2);
	m_vecVertex[22].SetColor(0, 1, 0, 1);
	m_vecVertex[22].SetNormal(1, 0, 0);
	m_vecVertex[22].SettextureCoord1(1, 0);
	m_vecVertex[23].SetPosition(l / 2, h / 2, -w / 2);
	m_vecVertex[23].SetColor(0, 1, 0, 1);
	m_vecVertex[23].SetNormal(1, 0, 0);
	m_vecVertex[23].SettextureCoord1(1, 1);

	size.x = l;
	size.y = w;
	size.z = h;

	m_vecIndex.resize(36);
	UINT index[36] = 
	{
		0	, 1	, 2,	2,	3,	0,
		4	, 5	, 6,	6,	7,	4,
		8	, 9	,10,	10,	11, 8,
		12	,13	,14,	14,	15,	12,
		16	,17	,18,	18,	19,	16,
		20	,21	,22,	22, 23, 20
	};

	memcpy(m_vecIndex.data(), index, sizeof(UINT) * 36);
}


void E3DEngine::Box::TransferRender()
{
	GameObject::TransferRender();
	IsActive = false;
	SetActive(true);
}


void E3DEngine::Box::PrepareUpdate(float deltaTime)
{

}

void E3DEngine::Box::SetActive(bool isActive)
{
	if (isActive == IsActive)
	{
		return;
	}
	GameObject::SetActive(isActive);
	Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
	mRenderer->RemoveInRenderer(ID);
	if (isActive)
	{
		mRenderer->FillBegin(ID);
		for (int i = 0; i < m_vecVertex.size(); i ++)
		{
			mRenderer->FillVertex(m_vecVertex[i]);
		}

		for (int i = 0; i < m_vecIndex.size(); i ++)
		{
			mRenderer->FillIndex(m_vecIndex[i]);
		}

		mRenderer->FillEnd(ID, m_vecVertex.size());
	}
	m_pRenderer->TransformChange();
}


void E3DEngine::Box::AfterUpdate(float deltaTime)
{

}

void E3DEngine::Box::TransformChange()
{
	if (!m_bIsStatic)
	{
		return;
	}
	if (pCamera && !pCamera->boundingBoxFrustum(Transform->Position, 100))
	{
		return;
	}
	m_pRenderer->SetTransform(Transform);
}

void E3DEngine::Box::CreateBehaviour()
{
	m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
	NEW_INSTANCE(Box);
	setBehaviourDefaultValue();
}

void E3DEngine::Box::setBehaviourDefaultValue()
{
	GameObject::setBehaviourDefaultValue();
}

