//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//

#include "E3DSkyBox.h"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "../Object/E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../Source/EngineDelegate.h"
#include "../Source/E3DVertexManager.h"
#include "../Scene/E3DSceneManager.hpp"

E3DEngine::SkyBox::SkyBox()
{
	CREATE_BEHAVIOUR(SkyBox);
}

void E3DEngine::SkyBox::Awake()
{
	mGameObject->VertexBufferName = "SkyBox";
	fillVertex();
}

void E3DEngine::SkyBox::Update(float deltaTime)
{
	Transform->SetPosition(SceneManager::GetCurrentScene()->GetMainCamera()->Transform->Position);
}

 
E3DEngine::SkyDome::SkyDome()
{
	CREATE_BEHAVIOUR(SkyDome);
}

void E3DEngine::SkyDome::Awake()
{
	mGameObject->VertexBufferName = "SkyDome";
	if (VertexManager::GetVertex(mGameObject->VertexBufferName).empty())
	{
		fillVertex(1);
	}
	mGameObject->SetSize(1, 1, 1);
}

void E3DEngine::SkyDome::fillVertex(float R)
{
	int rowNumber = 91;
	int colNumber = 361;
	std::vector<Vertex> vecVertex;
	vecVertex.resize(rowNumber  * colNumber);
	int indexSize = (rowNumber - 1) * (colNumber - 1) * 6;
	std::vector<unsigned int> vecIndex;
	vecIndex.resize(indexSize);
	int index = 0;
	int vIndex = 0;
	float dAlpha = 0, dBeta = 0;
	for (int alpha = rowNumber - 1; alpha >= 0; alpha--)
	{
		dAlpha = DEG2RAD((alpha));
		float sinAplha = sin(dAlpha);
		float cosAlpha = cos(dAlpha);
		for (int beta = 0; beta < colNumber; beta++)
		{
			dBeta = DEG2RAD((beta));
			float z = R * cos(dBeta) * cos(dAlpha);
			float x = R * sin(dBeta) * cos(dAlpha);
			float y = R * sin(dAlpha);
			vecVertex[vIndex].SetPosition(x, y, z);
			vecVertex[vIndex].SetColor(1, 1, 1, 1);
			vecVertex[vIndex].SetNormal(x, y, z);
			vecVertex[vIndex].SettextureCoord1((float)beta / (colNumber - 1), (float)alpha / (rowNumber - 1));
			vIndex++;
			if (alpha < rowNumber - 1 && beta < colNumber - 1)
			{
				vecIndex[index++] = (alpha * colNumber + beta); // 0
				vecIndex[index++] = ((alpha + 1) * colNumber + beta);// 360
				vecIndex[index++] = ((alpha + 1) * colNumber + beta + 1);

				vecIndex[index++] = ((alpha + 1) * colNumber + beta + 1);
				vecIndex[index++] = (alpha * colNumber + beta); // 1
				vecIndex[index++] = (alpha * colNumber + beta + 1);
			}
		}
	}

	VertexManager::Add(vecVertex, vecIndex, mGameObject->VertexBufferName);
}

void E3DEngine::SkyDome::Update(float deltaTime)
{
	Transform->SetPosition(SceneManager::GetCurrentScene()->GetMainCamera()->Transform->Position);
}


