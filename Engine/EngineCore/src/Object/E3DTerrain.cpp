#include "E3DTerrain.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Camera/E3DCamera.h"
#include "E3DTransform.hpp"

void E3DEngine::Terrain::Create(const char * heightMapFileName)
{
	//int mapWidth, mapHeight, bpp;
	//unsigned char *mapContent = stbi_load(heightMapFileName, &mapWidth, &mapHeight, &bpp, 0);

	//if (mapContent != nullptr)
	//{
	//	m_vecVertex.resize(mapWidth * mapHeight);
	//	m_vecIndex.resize((mapWidth - 1) * (mapHeight - 1) * 6);
	//	int vertexIndex = 0, index = 0;
	//	float x, y = 0, z;
	//	for (int i = 0; i < mapWidth; i ++)
	//	{
	//		for (int j = 0; j < mapHeight; j++)
	//		{
	//			x = (float)i - mapWidth / 2.0f;
	//			z = -((float)j - mapHeight / 2.0f);
	//			// [TODO] 
	//			char r = mapContent[i * mapWidth + j + 0];
	//			char g = mapContent[i * mapWidth + j + 1];
	//			char b = mapContent[i * mapWidth + j + 2];
	//			y =  ((r + g + b) / 3.0) / 10;
	//			m_vecVertex[vertexIndex].SetPosition(x * 5, y , z * 5);
	//			m_vecVertex[vertexIndex].SetNormal(0, 1, 0);
	//			m_vecVertex[vertexIndex].SetColor(1, 1, 1, 1);
	//			m_vecVertex[vertexIndex].SettextureCoord1((float)i / (mapWidth - 1), (float)j / (mapHeight - 1));
	//			vertexIndex++;
	//			if (i < mapWidth - 1 && j < mapWidth - 1)
	//			{
	//				m_vecIndex[index++] = (i * mapWidth + j); // 0
	//				m_vecIndex[index++] = ((i + 1) * mapWidth + j);// 360
	//				m_vecIndex[index++] = ((i + 1) * mapWidth + j + 1);

	//				m_vecIndex[index++] = ((i + 1) * mapWidth + j + 1);
	//				m_vecIndex[index++] = (i * mapWidth + j); // 1
	//				m_vecIndex[index++] = (i * mapWidth + j + 1);
	//			}
	//		}
	//	}
	//}
	//stbi_image_free(mapContent);
}


void E3DEngine::Terrain::Create(int size)
{
	m_vecVertex.resize(size * size);
	m_vecIndex.resize((size - 1) * (size - 1) * 6);
	int vertexIndex = 0, index = 0;
	float x, y = 0, z;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			x = (float)i - size / 2.0f;
			z = -((float)j - size / 2.0f);
			y = 0;
			m_vecVertex[vertexIndex].SetPosition(x * 5, y, z * 5);
			m_vecVertex[vertexIndex].SetNormal(0, 1, 0);
			m_vecVertex[vertexIndex].SetColor(0.5, 0.5, 0.5, 1);
			m_vecVertex[vertexIndex].SettextureCoord1((float)i / (size - 1), (float)j / (size - 1));
			vertexIndex++;
			if (i < size - 1 && j < size - 1)
			{
				m_vecIndex[index++] = (i * size + j); // 0
				m_vecIndex[index++] = ((i + 1) * size + j);// 360
				m_vecIndex[index++] = ((i + 1) * size + j + 1);

				m_vecIndex[index++] = ((i + 1) * size + j + 1);
				m_vecIndex[index++] = (i * size + j); // 1
				m_vecIndex[index++] = (i * size + j + 1);
			}
		}
	}
	Transform->SetNeedUpdate(true);
}

void E3DEngine::Terrain::SetMaterial(Material * material)
{
	m_pRenderer = GetRenderSystem()->GetRenderManager()->GetRenderer(material->ID);
	m_pRenderer->SetRenderIndex(eRI_Normal);
	//SceneManager::GetInstance().GetCurrentScene()->AddRenderObject(m_pRenderer, m_layerMask);

	GameObject::SetMaterial(material);
	m_pRenderer->IsStaticDraw = false;
	Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
	m_pRenderer->SetTransform(Transform);
	mRenderer->RemoveInRenderer(ID);

	mRenderer->RecordCurrentVextexStartIndex(ID);
	mRenderer->RecordCurrentIndexStartIndex(ID);
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		mRenderer->FillVertex(m_vecVertex[i]);
	}

	for (int i = 0; i < m_vecIndex.size(); i++)
	{
		mRenderer->FillIndex(m_vecIndex[i]);
	}
	mRenderer->FillEnd();
	mRenderer->VertexCountAdd(ID, m_vecVertex.size());
	mRenderer->IndexCountAdd(ID, m_vecIndex.size());

	m_pRenderer->TransformChange();
}


void E3DEngine::Terrain::PrepareUpdate(float deltaTime)
{
	GameObject::PrepareUpdate(deltaTime);
	if (m_bIsEditorGrid && m_pRenderer->pCamera != nullptr)
	{
		int size = m_pRenderer->pCamera->Transform->Position.y / 50;
		size = size == 0 ? 1 : size * 2;

		if (lastSize == size)
		{
			return;
		}
		Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
		int vertexStartIndex = mRenderer->GetRendererBuffer(ID)->VertextStartIndex;

		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			vec3f pos = vec3f(m_vecVertex[i].Position[0] * size, m_vecVertex[i].Position[1], m_vecVertex[i].Position[2] * size);
		//	m_vecVertex[i]
			mRenderer->Vertices[vertexStartIndex + i].SetPosition(pos.x, pos.y, pos.z);
		}

		m_pRenderer->TransformChange();
		lastSize = size;
	}
}

void E3DEngine::Terrain::CreateBehaviour()
{
	m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
	NEW_INSTANCE(Terrain);
	setBehaviourDefaultValue();
}

void E3DEngine::Terrain::setBehaviourDefaultValue()
{
	GameObject::setBehaviourDefaultValue();
}
