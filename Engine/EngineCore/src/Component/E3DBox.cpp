
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-11-28 PanQingyun. All rights reserved. ************************//

#include "E3DBox.h"
#include "../Scene/E3DSceneManager.hpp"
#include "../Object/E3DTransform.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Camera/E3DCamera.h"
#include "../Source/E3DVertexManager.h"


E3DEngine::Box::Box()
{
	CREATE_BEHAVIOUR(Box);
}

void E3DEngine::Box::Awake()
{
	mGameObject->VertexBufferName = "Box";
	fillVertex();
}

void E3DEngine::Box::fillVertex()
{
	if (VertexManager::GetVertex(mGameObject->VertexBufferName).empty())
	{
		std::vector<Vertex> vecVertex;
		vecVertex.resize(24);
		// 前
		vecVertex[0].SetPosition(-1.0 / 2, 1.0 / 2, 1.0 / 2);
		vecVertex[0].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[0].SetNormal(0, 0, 1.0);
		vecVertex[0].SettextureCoord1(0, 1.0);
		vecVertex[1.0].SetPosition(-1.0 / 2, -1.0 / 2, 1.0 / 2);
		vecVertex[1.0].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[1.0].SetNormal(0, 0, 1.0);
		vecVertex[1.0].SettextureCoord1(0, 0);
		vecVertex[2].SetPosition(1.0 / 2, -1.0 / 2, 1.0 / 2);
		vecVertex[2].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[2].SetNormal(0, 0, 1.0);
		vecVertex[2].SettextureCoord1(1.0, 0);
		vecVertex[3].SetPosition(1.0 / 2, 1.0 / 2, 1.0 / 2);
		vecVertex[3].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[3].SetNormal(0, 0, 1.0);
		vecVertex[3].SettextureCoord1(1.0, 1.0);
		// 上
		vecVertex[4].SetPosition(-1.0 / 2, 1.0 / 2, 1.0 / 2);
		vecVertex[4].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[4].SetNormal(0, 1.0, 0);
		vecVertex[4].SettextureCoord1(0, 1.0);
		vecVertex[5].SetPosition(1.0 / 2, 1.0 / 2, 1.0 / 2);
		vecVertex[5].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[5].SetNormal(0, 1.0, 0);
		vecVertex[5].SettextureCoord1(0, 0);
		vecVertex[6].SetPosition(1.0 / 2, 1.0 / 2, -1.0 / 2);
		vecVertex[6].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[6].SetNormal(0, 1.0, 0);
		vecVertex[6].SettextureCoord1(1.0, 0);
		vecVertex[7].SetPosition(-1.0 / 2, 1.0 / 2, -1.0 / 2);
		vecVertex[7].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[7].SetNormal(0, 1.0, 0);
		vecVertex[7].SettextureCoord1(1.0, 1.0);
		// 后
		vecVertex[8].SetPosition(-1.0 / 2, 1.0 / 2, -1.0 / 2);
		vecVertex[8].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[8].SetNormal(0, 0, -1.0);
		vecVertex[8].SettextureCoord1(0, 1.0);
		vecVertex[9].SetPosition(1.0 / 2, 1.0 / 2, -1.0 / 2);
		vecVertex[9].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[9].SetNormal(0, 0, -1.0);
		vecVertex[9].SettextureCoord1(0, 0);
		vecVertex[10].SetPosition(1.0 / 2, -1.0 / 2, -1.0 / 2);
		vecVertex[10].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[10].SetNormal(0, 0, -1.0);
		vecVertex[10].SettextureCoord1(1.0, 0);
		vecVertex[11].SetPosition(-1.0 / 2, -1.0 / 2, -1.0 / 2);
		vecVertex[11].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[11].SetNormal(0, 0, -1.0);
		vecVertex[11].SettextureCoord1(1.0, 1.0);
		// 下
		vecVertex[12].SetPosition(-1.0 / 2, -1.0 / 2, -1.0 / 2);
		vecVertex[12].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[12].SetNormal(0, -1.0, 0);
		vecVertex[12].SettextureCoord1(0, 1.0);
		vecVertex[13].SetPosition(1.0 / 2, -1.0 / 2, -1.0 / 2);
		vecVertex[13].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[13].SetNormal(0, -1.0, 0);
		vecVertex[13].SettextureCoord1(0, 0);
		vecVertex[14].SetPosition(1.0 / 2, -1.0 / 2, 1.0 / 2);
		vecVertex[14].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[14].SetNormal(0, -1.0, 0);
		vecVertex[14].SettextureCoord1(1.0, 0);
		vecVertex[15].SetPosition(-1.0 / 2, -1.0 / 2, 1.0 / 2);
		vecVertex[15].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[15].SetNormal(0, -1.0, 0);
		vecVertex[15].SettextureCoord1(1.0, 1.0);
		// 左
		vecVertex[16].SetPosition(-1.0 / 2, 1.0 / 2, 1.0 / 2);
		vecVertex[16].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[16].SetNormal(-1.0, 0, 0);
		vecVertex[16].SettextureCoord1(0, 1.0);
		vecVertex[17].SetPosition(-1.0 / 2, 1.0 / 2, -1.0 / 2);
		vecVertex[17].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[17].SetNormal(-1.0, 0, 0);
		vecVertex[17].SettextureCoord1(0, 0);
		vecVertex[18].SetPosition(-1.0 / 2, -1.0 / 2, -1.0 / 2);
		vecVertex[18].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[18].SetNormal(-1.0, 0, 0);
		vecVertex[18].SettextureCoord1(1.0, 0);
		vecVertex[19].SetPosition(-1.0 / 2, -1.0 / 2, 1.0 / 2);
		vecVertex[19].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[19].SetNormal(-1.0, 0, 0);
		vecVertex[19].SettextureCoord1(1.0, 1.0);
		// 右
		vecVertex[20].SetPosition(1.0 / 2, 1.0 / 2, 1.0 / 2);
		vecVertex[20].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[20].SetNormal(1.0, 0, 0);
		vecVertex[20].SettextureCoord1(0, 1.0);
		vecVertex[21].SetPosition(1.0 / 2, -1.0 / 2, 1.0 / 2);
		vecVertex[21].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[21].SetNormal(1.0, 0, 0);
		vecVertex[21].SettextureCoord1(0, 0);
		vecVertex[22].SetPosition(1.0 / 2, -1.0 / 2, -1.0 / 2);
		vecVertex[22].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[22].SetNormal(1.0, 0, 0);
		vecVertex[22].SettextureCoord1(1.0, 0);
		vecVertex[23].SetPosition(1.0 / 2, 1.0 / 2, -1.0 / 2);
		vecVertex[23].SetColor(1.0, 1.0, 1.0, 1.0);
		vecVertex[23].SetNormal(1.0, 0, 0);
		vecVertex[23].SettextureCoord1(1.0, 1.0);
		std::vector<UINT> vecIndex;
		vecIndex.resize(36);
		UINT index[36] =
		{
			0	, 1	, 2,	2,	3,	0,
			4	, 5	, 6,	6,	7,	4,
			8	, 9	,10,	10,	11, 8,
			12	,13	,14,	14,	15,	12,
			16	,17	,18,	18,	19,	16,
			20	,21	,22,	22, 23, 20
		};

		memcpy(vecIndex.data(), index, sizeof(UINT) * 36);

		VertexManager::Add(vecVertex, vecIndex, mGameObject->VertexBufferName);
	}

	mGameObject->SetSize(1, 1, 1);
}

