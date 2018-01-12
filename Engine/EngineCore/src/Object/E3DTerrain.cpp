#include "E3DTerrain.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"

void E3DEngine::Terrain::Create(const char * heightMapFileName)
{
	int mapWidth, mapHeight;
	unsigned char * mapContent = vvision::readBmp(heightMapFileName, mapWidth, mapHeight);

	if (mapContent != nullptr)
	{
		m_vecVertex.resize(mapWidth * mapHeight);
		m_vecIndex.resize((mapWidth - 1) * (mapHeight - 1) * 6);
		int vertexIndex = 0, index = 0;
		float x, y = 0, z;
		for (int i = 0; i < mapWidth; i ++)
		{
			for (int j = 0; j < mapHeight; j++)
			{
				x = (float)i - mapWidth / 2.0f;
				z = -((float)j - mapHeight / 2.0f);
				// [TODO] 
				//y = ((float)(*(mapContent + vertexIndex) )) / 10.0;
				m_vecVertex[vertexIndex].SetPosition(x * 20, y , z * 20);
				m_vecVertex[vertexIndex].SetNormal(0, 1, 0);
				m_vecVertex[vertexIndex].SetColor(0.8, 0.8, 0.8, 0.8);
				m_vecVertex[vertexIndex].SettextureCoord((float)i / (mapWidth - 1), (float)j / (mapHeight - 1));
				vertexIndex++;
				if (i < mapWidth - 1 && j < mapWidth - 1)
				{
					m_vecIndex[index++] = (i * mapWidth + j); // 0
					m_vecIndex[index++] = ((i + 1) * mapWidth + j);// 360
					m_vecIndex[index++] = ((i + 1) * mapWidth + j + 1);

					m_vecIndex[index++] = ((i + 1) * mapWidth + j + 1);
					m_vecIndex[index++] = (i * mapWidth + j); // 1
					m_vecIndex[index++] = (i * mapWidth + j + 1);
				}
			}
		}
	}
}

void E3DEngine::Terrain::SetMaterial(Material * material)
{
	m_pRenderer = GetRenderSystem()->GetRenderManager()->GetRenderer(material->ID);
	SceneManager::GetInstance().GetCurrentScene()->AddRenderObject(m_pRenderer, m_layerMask);
	m_pRenderer->EnableDepthTest = true;

	GameObject::SetMaterial(material);
	m_pRenderer->IsStaticDraw = true;
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
