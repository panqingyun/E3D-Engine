//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//
#include "E3DSphere.h"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "../Object/E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Source/E3DVertexManager.h"

E3DEngine::Sphere::Sphere()
{
	CREATE_BEHAVIOUR(Sphere);
}

void E3DEngine::Sphere::Awake()
{
	create(1);
}

void E3DEngine::Sphere::create(float R)
{
	mGameObject->VertexBufferName = "Sphere";
	if (VertexManager::GetVertex(mGameObject->VertexBufferName).empty())
	{
		std::vector<Vertex> vecVertex;
		int rowNumber = 181;
		int colNumber = 181;
		vecVertex.resize(rowNumber * colNumber);
		int indexSize = (rowNumber - 1) * (colNumber - 1) * 6;
		std::vector<unsigned int> vecIndex;
		vecIndex.resize(indexSize);
		int index = 0;
		int vIndex = 0;
		float dAlpha = 0, dBeta = 0;
		for (int alpha = 0; alpha < rowNumber; alpha++)
		{
			dAlpha = DEG2RAD((90 - alpha));
			for (int beta = 0; beta < colNumber; beta++)
			{
				dBeta = DEG2RAD(beta * 2);
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
					vecIndex[index++] = (alpha * rowNumber + beta); // 0
					vecIndex[index++] = ((alpha + 1) * rowNumber + beta);// 360
					vecIndex[index++] = ((alpha + 1) * rowNumber + beta + 1);

					vecIndex[index++] = ((alpha + 1) * rowNumber + beta + 1);
					vecIndex[index++] = (alpha * rowNumber + beta + 1);
					vecIndex[index++] = (alpha * rowNumber + beta); // 1
				}
			}
		}
		VertexManager::Add(vecVertex, vecIndex, mGameObject->VertexBufferName);
	}
	mGameObject->SetSize(R, R, R);
}