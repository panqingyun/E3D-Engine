#include "E3DSkyBox.h"
#include "E3DRenderObject.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../Source/EngineDelegate.h"

void E3DEngine::SkyBox::Create(float l, float w, float h)
{
	Box::Create(l, w, h);	
}

void E3DEngine::SkyBox::SetMaterial(Material * material)
{
	SkyBoxConfig * skyBox = material->MaterialTableManager->Select<SkyBoxConfig>(1);
	textures.emplace_back(material->MaterialTableManager->Select<TextureAtlas>(skyBox->Front)); //0
	textures.emplace_back(material->MaterialTableManager->Select<TextureAtlas>(skyBox->Top));	// 1
	textures.emplace_back(material->MaterialTableManager->Select<TextureAtlas>(skyBox->Back));	// 2
	textures.emplace_back(material->MaterialTableManager->Select<TextureAtlas>(skyBox->Down));	// 3
	textures.emplace_back(material->MaterialTableManager->Select<TextureAtlas>(skyBox->Left));	// 4
	textures.emplace_back(material->MaterialTableManager->Select<TextureAtlas>(skyBox->Right));	// 5

	setTextureCoord();
	Box::SetMaterial(material);
	m_pRenderer->SetRenderIndex(eRI_LowMost);
	m_pRenderer->EnableDepthTest = false;

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

	// front
	m_vecVertex[0].SettextureCoord(rightTop.x, rightTop.y);
	m_vecVertex[1].SettextureCoord(rightDown.x, rightDown.y);
	m_vecVertex[2].SettextureCoord(leftDown.x, leftDown.y);
	m_vecVertex[3].SettextureCoord(leftTop.x, leftTop.y);


	getCoord(1, leftTop, rightTop, leftDown, rightDown);
	// up
	m_vecVertex[4].SettextureCoord(leftTop.x, leftTop.y);
	m_vecVertex[5].SettextureCoord(rightTop.x, rightTop.y);
	m_vecVertex[6].SettextureCoord(rightDown.x, rightDown.y);
	m_vecVertex[7].SettextureCoord(leftDown.x, leftDown.y);


	getCoord(2, leftTop, rightTop, leftDown, rightDown);
	// back
	m_vecVertex[8].SettextureCoord(leftTop.x, leftTop.y);
	m_vecVertex[9].SettextureCoord(rightTop.x, rightTop.y);
	m_vecVertex[10].SettextureCoord(rightDown.x, rightDown.y);
	m_vecVertex[11].SettextureCoord(leftDown.x, leftDown.y);


	getCoord(3, leftTop, rightTop, leftDown, rightDown);
	// down
	m_vecVertex[12].SettextureCoord(leftTop.x, leftTop.y);
	m_vecVertex[13].SettextureCoord(rightTop.x, rightTop.y);
	m_vecVertex[14].SettextureCoord(rightDown.x, rightDown.y);
	m_vecVertex[15].SettextureCoord(leftDown.x, leftDown.y);


	getCoord(4, leftTop, rightTop, leftDown, rightDown);
	// left
	m_vecVertex[16].SettextureCoord(leftTop.x, leftTop.y);
	m_vecVertex[17].SettextureCoord(rightTop.x, rightTop.y);
	m_vecVertex[18].SettextureCoord(rightDown.x, rightDown.y);
	m_vecVertex[19].SettextureCoord(leftDown.x, leftDown.y);


	getCoord(5, leftTop, rightTop, leftDown, rightDown);
	// right
	m_vecVertex[20].SettextureCoord(rightTop.x, rightTop.y);
	m_vecVertex[21].SettextureCoord(rightDown.x, rightDown.y);
	m_vecVertex[22].SettextureCoord(leftDown.x, leftDown.y);
	m_vecVertex[23].SettextureCoord(leftTop.x, leftTop.y);

}

void E3DEngine::SkyBox::getCoord(int index, vec2f &leftTop, vec2f &rightTop, vec2f &leftDown, vec2f &rightDown)
{
	TextureAtlas* texture = textures[index];

	leftTop.x = texture->x / texture->width;
	leftTop.y = texture->y / texture->height;
	leftDown.x = texture->x / texture->width;
	leftDown.y = texture->y / texture->height + texture->h / texture->height;
	rightDown.x = texture->x / texture->width + texture->w / texture->width;
	rightDown.y = texture->y / texture->height + texture->h / texture->height;
	rightTop.x = texture->x / texture->width + texture->w / texture->width;
	rightTop.y = texture->y / texture->height;
}

void E3DEngine::SkyDome::Create(float R)
{
	int rowNumber = 91;
	int colNumber = 361;
	m_vecVertex.resize(rowNumber  * colNumber );
	int indexSize = (rowNumber - 1) * (colNumber - 1) * 6;
	m_vecIndex.resize(indexSize);
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
			dBeta = DEG2RAD(( beta));
			float z = R * cos(dBeta) * cos(dAlpha);
			float x = R * sin(dBeta) * cos(dAlpha);
			float y = R * sin(dAlpha);
			m_vecVertex[vIndex].SetPosition(x, y, z);
			m_vecVertex[vIndex].SetColor(1, 1, 1, 1);
			m_vecVertex[vIndex].SetNormal(x, y, z);
			m_vecVertex[vIndex].SettextureCoord((float)beta / (colNumber - 1), (float)alpha / (rowNumber - 1));
			vIndex++;
			if (alpha < rowNumber - 1 && beta < colNumber - 1)
			{
				m_vecIndex[index++] = (alpha * colNumber + beta); // 0
				m_vecIndex[index++] = ((alpha + 1) * colNumber + beta);// 360
				m_vecIndex[index++] = ((alpha + 1) * colNumber + beta + 1);

				m_vecIndex[index++] = ((alpha + 1) * colNumber + beta + 1);
				m_vecIndex[index++] = (alpha * colNumber + beta); // 1
				m_vecIndex[index++] = (alpha * colNumber + beta + 1);
			}
		}
	}
	size.x = R;
	size.y = R;
	size.z = R;
	IsActive = false;
}

void E3DEngine::SkyDome::SetMaterial(Material * material)
{
	m_pRenderer = GetRenderSystem()->GetRenderManager()->GetRenderer(material->ID);
	SceneManager::GetInstance().GetCurrentScene()->AddRenderObject(m_pRenderer, m_layerMask);
	
	GameObject::SetMaterial(material);
	m_pRenderer->SetTransform(Transform);
	m_pRenderer->IsStaticDraw = true;
	m_pRenderer->EnableDepthTest = false;
	m_pRenderer->SetRenderIndex(eRI_LowMost);
	//m_pRenderer->SetDrawModule(eDM_LINES);
	IsActive = false;
	SetActive(true);
}

void E3DEngine::SkyDome::PrepareUpdate(float deltaTime)
{
	if (m_pRenderer != nullptr && m_pRenderer->pCamera != nullptr)
	{
		Transform->SetPosition(m_pRenderer->pCamera->Transform->Position);
	}
}

void E3DEngine::SkyDome::SetActive(bool isActive)
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
	Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
	mRenderer->RemoveInRenderer(ID);
	if (isActive)
	{
		mRenderer->RecordCurrentVextexStartIndex(ID);
		mRenderer->RecordCurrentIndexStartIndex(ID);
		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			m_vecVertex[i].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
			mRenderer->FillVertex(m_vecVertex[i]);
		}

		for (int i = 0; i < m_vecIndex.size(); i++)
		{
			mRenderer->FillIndex(m_vecIndex[i]);
		}
		mRenderer->FillEnd();
		mRenderer->VertexCountAdd(ID, m_vecVertex.size());
		mRenderer->IndexCountAdd(ID, m_vecIndex.size());
	}
	mRenderer->TransformChange();
}

