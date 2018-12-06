//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
#include "E3DTerrain.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Camera/E3DCamera.h"
#include "../Object/E3DTransform.hpp"
#include "../RenderSystem/Texture/E3DTextureDataManager.hpp"
#include "../Source/E3DVertexManager.h"


E3DEngine::Terrain::Terrain()
{
	IsEditorGrid = false;
	CREATE_BEHAVIOUR(Terrain);
}

void E3DEngine::Terrain::Awake()
{
	if (IsEditorGrid)
	{
		createGrid();
	}
	else
	{
		createHeightMap();
	}
}

void E3DEngine::Terrain::createHeightMap()
{
	TextureData * td = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(HeightMapFile);
	mGameObject->VertexBufferName = "Terrain";
	if (td != nullptr)
	{
		if (VertexManager::GetVertex(mGameObject->VertexBufferName).empty())
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
					x = i - mapWidth / 2.0f;
					z = -(j - mapHeight / 2.0f);
					// [TODO] 
					char r = mapContent[i * mapWidth + j + 0];
					char g = mapContent[i * mapWidth + j + 1];
					char b = mapContent[i * mapWidth + j + 2];
					y = ((r + g + b) / 3.0) / 10;
					// 0 ---- 3
					// |\     |
					// |  \   |
					// |    \ |
					// 1----- 2
					vecVertex[vertexIndex].SetPosition(x, y, z);
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
			VertexManager::Add(vecVertex, vecIndex, mGameObject->VertexBufferName);
		}
	}
}


void E3DEngine::Terrain::createGrid()
{
	mGameObject->VertexBufferName = "_Terrain";
	if (VertexManager::GetVertex(mGameObject->VertexBufferName).empty())
	{
		std::vector<Vertex>  vecVertex;
		std::vector<UINT> vecIndex;
		vecVertex.resize(Size * Size);
		vecIndex.resize((Size - 1) * (Size - 1) * 6);
		int vertexIndex = 0, index = 0;
		float x, y = 0, z;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				x = (float)i - Size / 2.0f;
				z = -((float)j - Size / 2.0f);
				y = 0;
				vecVertex[vertexIndex].SetPosition(x , y, z );
				vecVertex[vertexIndex].SetNormal(0, 1, 0);
				vecVertex[vertexIndex].SetColor(1, 1,1, 1);
				vecVertex[vertexIndex].SettextureCoord1((float)i / (Size - 1), (float)j / (Size - 1));
				vertexIndex++;
				if (i < Size - 1 && j < Size - 1)
				{
					vecIndex[index++] = (i * Size + j); // 0
					vecIndex[index++] = ((i + 1) * Size + j);// 360
					vecIndex[index++] = ((i + 1) * Size + j + 1);

					vecIndex[index++] = ((i + 1) * Size + j + 1);
					vecIndex[index++] = (i * Size + j); // 1
					vecIndex[index++] = (i * Size + j + 1);
				}
			}
		}

		VertexManager::Add(vecVertex, vecIndex, mGameObject->VertexBufferName);
	}
	Transform->SetNeedUpdate(true);
}
