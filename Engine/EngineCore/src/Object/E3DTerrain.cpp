//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
#include "E3DTerrain.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Camera/E3DCamera.h"
#include "E3DTransform.hpp"
#include "../RenderSystem/Texture/E3DTextureDataManager.hpp"
#include "../Source/E3DVertexManager.h"


E3DEngine::Terrain::Terrain()
{
	mSceneObjectType = TP_Terrain;
	m_bIsEditorGrid = false;
	CREATE_BEHAVIOUR(Terrain);
}

void E3DEngine::Terrain::Create(const char * heightMapFileName)
{
	TextureData * td = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(heightMapFileName);
	VertexBufferName = "Terrain";
	if (td != nullptr)
	{
		if (VertexManager::GetVertex(VertexBufferName).empty())
		{
			int mapWidth = td->width;
			int mapHeight = td->height;
			unsigned char * mapContent = (unsigned char *)td->imgData;
			std::vector<Vertex>  vecVertex;
			std::vector<UINT> vecIndex;
			vecVertex.resize(mapWidth * mapHeight);
			vecIndex.resize((mapWidth - 1) * (mapHeight - 1) * 6);
			int vertexIndex = 0, index = 0;
			float x, y = 0, z;
			for (int i = 0; i < mapWidth; i++)
			{
				for (int j = 0; j < mapHeight; j++)
				{
					x = (float)i - mapWidth / 2.0f;
					z = -((float)j - mapHeight / 2.0f);
					// [TODO] 
					char r = mapContent[i * mapWidth + j + 0];
					char g = mapContent[i * mapWidth + j + 1];
					char b = mapContent[i * mapWidth + j + 2];
					y = ((r + g + b) / 3.0) / 10;
					vecVertex[vertexIndex].SetPosition(x * 5, y, z * 5);
					vecVertex[vertexIndex].SetNormal(0, 1, 0);
					vecVertex[vertexIndex].SetColor(1, 1, 1, 1);
					vecVertex[vertexIndex].SettextureCoord1((float)i / (mapWidth - 1), (float)j / (mapHeight - 1));
					vertexIndex++;
					if (i < mapWidth - 1 && j < mapWidth - 1)
					{
						vecIndex[index++] = (i * mapWidth + j); // 0
						vecIndex[index++] = ((i + 1) * mapWidth + j);// 360
						vecIndex[index++] = ((i + 1) * mapWidth + j + 1);

						vecIndex[index++] = ((i + 1) * mapWidth + j + 1);
						vecIndex[index++] = (i * mapWidth + j); // 1
						vecIndex[index++] = (i * mapWidth + j + 1);
					}
				}
			}
			VertexManager::Add(vecVertex, vecIndex, VertexBufferName);
		}
	}
}


void E3DEngine::Terrain::Create(int size, int perGridSize)
{
	VertexBufferName = "_Terrain";
	mSize = size;
	if (VertexManager::GetVertex(VertexBufferName).empty())
	{
		std::vector<Vertex>  vecVertex;
		std::vector<UINT> vecIndex;
		vecVertex.resize(size * size);
		vecIndex.resize((size - 1) * (size - 1) * 6);
		int vertexIndex = 0, index = 0;
		float x, y = 0, z;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				x = (float)i - size / 2.0f;
				z = -((float)j - size / 2.0f);
				y = 0;
				vecVertex[vertexIndex].SetPosition(x * perGridSize, y, z * perGridSize);
				vecVertex[vertexIndex].SetNormal(0, 1, 0);
				vecVertex[vertexIndex].SetColor(1, 1,1, 1);
				vecVertex[vertexIndex].SettextureCoord1((float)i / (size - 1), (float)j / (size - 1));
				vertexIndex++;
				if (i < size - 1 && j < size - 1)
				{
					vecIndex[index++] = (i * size + j); // 0
					vecIndex[index++] = ((i + 1) * size + j);// 360
					vecIndex[index++] = ((i + 1) * size + j + 1);

					vecIndex[index++] = ((i + 1) * size + j + 1);
					vecIndex[index++] = (i * size + j); // 1
					vecIndex[index++] = (i * size + j + 1);
				}
			}
		}

		VertexManager::Add(vecVertex, vecIndex, VertexBufferName);
	}
	Transform->SetNeedUpdate(true);
}

void E3DEngine::Terrain::SetIsEditorGrid(bool isEditor)
{
	m_bIsEditorGrid = isEditor;
}
