//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//

#include "E3DSkyBox.h"
#include "E3DRenderObject.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../Source/EngineDelegate.h"
#include "../Source/E3DVertexManager.h"

void E3DEngine::SkyBox::Create(float l, float w, float h)
{
	mSceneObjectType = TP_SkyBox;
	VertexBufferName = "SkyBox";
	fillVertex(l, w, h);	
}

void E3DEngine::SkyBox::TransferRender()
{
	m_pRenderer->SetRenderIndex(eRI_LowMost);
	SkyBoxConfig * skyBox = m_pRenderer->GetMaterial()->mMaterialTableManager->Select<SkyBoxConfig>(1);
	SetLayerMask(LD_SKYBOX);
	if (skyBox == nullptr)
	{
		return;
	}
	textures.emplace_back(m_pRenderer->GetMaterial()->mMaterialTableManager->Select<TextureAtlasConfig>(skyBox->Front)); //0
	textures.emplace_back(m_pRenderer->GetMaterial()->mMaterialTableManager->Select<TextureAtlasConfig>(skyBox->Top));	// 1
	textures.emplace_back(m_pRenderer->GetMaterial()->mMaterialTableManager->Select<TextureAtlasConfig>(skyBox->Back));	// 2
	textures.emplace_back(m_pRenderer->GetMaterial()->mMaterialTableManager->Select<TextureAtlasConfig>(skyBox->Down));	// 3
	textures.emplace_back(m_pRenderer->GetMaterial()->mMaterialTableManager->Select<TextureAtlasConfig>(skyBox->Left));	// 4
	textures.emplace_back(m_pRenderer->GetMaterial()->mMaterialTableManager->Select<TextureAtlasConfig>(skyBox->Right));	// 5

	setTextureCoord();
}

void E3DEngine::SkyBox::PrepareUpdate(float deltaTime)
{
	if (m_pRenderer==nullptr || m_pRenderer->pCamera == nullptr)
	{
		return;
	}
	Transform->SetPosition(m_pRenderer->pCamera->Transform->Position);
}

void E3DEngine::SkyBox::setTextureCoord()
{
	vec2f leftTop, rightTop , leftDown, rightDown;

	getCoord(0, leftTop, rightTop, leftDown, rightDown);

	std::vector<Vertex> &vecVertex = VertexManager::GetVertex(VertexBufferName);

	// front
	vecVertex[0].SettextureCoord1(rightTop.x, rightTop.y);
	vecVertex[1].SettextureCoord1(rightDown.x, rightDown.y);
	vecVertex[2].SettextureCoord1(leftDown.x, leftDown.y);
	vecVertex[3].SettextureCoord1(leftTop.x, leftTop.y);


	getCoord(1, leftTop, rightTop, leftDown, rightDown);
	// up
	vecVertex[4].SettextureCoord1(leftTop.x, leftTop.y);
	vecVertex[5].SettextureCoord1(rightTop.x, rightTop.y);
	vecVertex[6].SettextureCoord1(rightDown.x, rightDown.y);
	vecVertex[7].SettextureCoord1(leftDown.x, leftDown.y);


	getCoord(2, leftTop, rightTop, leftDown, rightDown);
	// back
	vecVertex[8].SettextureCoord1(leftTop.x, leftTop.y);
	vecVertex[9].SettextureCoord1(rightTop.x, rightTop.y);
	vecVertex[10].SettextureCoord1(rightDown.x, rightDown.y);
	vecVertex[11].SettextureCoord1(leftDown.x, leftDown.y);


	getCoord(3, leftTop, rightTop, leftDown, rightDown);
	// down
	vecVertex[12].SettextureCoord1(leftTop.x, leftTop.y);
	vecVertex[13].SettextureCoord1(rightTop.x, rightTop.y);
	vecVertex[14].SettextureCoord1(rightDown.x, rightDown.y);
	vecVertex[15].SettextureCoord1(leftDown.x, leftDown.y);


	getCoord(4, leftTop, rightTop, leftDown, rightDown);
	// left
	vecVertex[16].SettextureCoord1(leftTop.x, leftTop.y);
	vecVertex[17].SettextureCoord1(rightTop.x, rightTop.y);
	vecVertex[18].SettextureCoord1(rightDown.x, rightDown.y);
	vecVertex[19].SettextureCoord1(leftDown.x, leftDown.y);


	getCoord(5, leftTop, rightTop, leftDown, rightDown);
	// right
	vecVertex[20].SettextureCoord1(rightTop.x, rightTop.y);
	vecVertex[21].SettextureCoord1(rightDown.x, rightDown.y);
	vecVertex[22].SettextureCoord1(leftDown.x, leftDown.y);
	vecVertex[23].SettextureCoord1(leftTop.x, leftTop.y);

}

void E3DEngine::SkyBox::getCoord(int index, vec2f &leftTop, vec2f &rightTop, vec2f &leftDown, vec2f &rightDown)
{
	TextureAtlasConfig* texture = textures[index];

	leftTop.x = texture->x / texture->width;
	leftTop.y = texture->y / texture->height;
	leftDown.x = texture->x / texture->width;
	leftDown.y = texture->y / texture->height + texture->h / texture->height;
	rightDown.x = texture->x / texture->width + texture->w / texture->width;
	rightDown.y = texture->y / texture->height + texture->h / texture->height;
	rightTop.x = texture->x / texture->width + texture->w / texture->width;
	rightTop.y = texture->y / texture->height;
}

E3DEngine::SkyDome::SkyDome()
{
	mSceneObjectType = TP_SkyDome;
	CREATE_BEHAVIOUR(SkyDome);
}

void E3DEngine::SkyDome::Create(float R)
{
	VertexBufferName = "SkyDome";
	if (VertexManager::GetVertex(VertexBufferName).empty())
	{
		fillVertex(R);
	}
	size.x = R;
	size.y = R;
	size.z = R;
	IsActive = false;
}

void E3DEngine::SkyDome::fillVertex(float R)
{
	int rowNumber = 91;
	int colNumber = 361;
	std::vector<Vertex> vecVertex;
	vecVertex.resize(rowNumber  * colNumber);
	m_vecBatchVertex.resize(rowNumber  * colNumber);
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

	VertexManager::Add(vecVertex, vecIndex, VertexBufferName);
}

void E3DEngine::SkyDome::PrepareUpdate(float deltaTime)
{
	if (m_pRenderer != nullptr && m_pRenderer->pCamera != nullptr)
	{
		Transform->SetPosition(m_pRenderer->pCamera->Transform->Position);
	}
}


