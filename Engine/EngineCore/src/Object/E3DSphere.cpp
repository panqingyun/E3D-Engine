#include "E3DSphere.h"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../RenderSystem/E3DRenderSystem.hpp"

void E3DEngine::Sphere::Create(float R)
{
	int rowNumber = 360;
	int colNumber = 360;
	m_vecVertex.resize(rowNumber * colNumber);
	int indexSize = (rowNumber - 1) * (colNumber - 1) * 6;
	m_vecIndex.resize(indexSize);
	int index = 0;
	int vIndex = 0;
	float dAlpha = 0, dBeta = 0;
	for (int alpha = 0; alpha < rowNumber; alpha ++)
	{
		dAlpha = DEG2RAD(alpha);
		float sinAplha = sin(dAlpha);
		float cosAlpha = cos(dAlpha);
		for (int beta = 0; beta < colNumber; beta++)
		{
			dBeta = DEG2RAD(beta);
			float x = R * cosAlpha * sin(dBeta);
			float y = R * sinAplha * sin(dBeta);
			float z = R * cos(dBeta);
			m_vecVertex[vIndex].SetPosition(x, y, z);
			m_vecVertex[vIndex].SetColor(1, 1, 1, 1);
			m_vecVertex[vIndex].SetNormal(x, y, z);
			vIndex++;
			if (alpha < rowNumber - 1 && beta < colNumber - 1)
			{
				m_vecIndex[index++] = (alpha * rowNumber + beta); // 0
				m_vecIndex[index++] = ((alpha + 1) * rowNumber + beta);// 360
				m_vecIndex[index++] = ((alpha + 1) * rowNumber + beta + 1);

				m_vecIndex[index++] = ((alpha + 1) * rowNumber + beta + 1);
				m_vecIndex[index++] = (alpha * rowNumber + beta); // 1
				m_vecIndex[index++] = (alpha * rowNumber + beta + 1);
			}
		}
	}
	size.x = R;
	size.y = R;
	size.z = R;
	IsActive = false;
}

void E3DEngine::Sphere::SetMaterial(Material *material)
{
	m_pRenderer = GetRenderSystem()->GetRenderManager()->GetRenderer(material->ID);
	m_pRenderer->EnableDepthTest = true;

	if (m_pRenderer->RenderIndex != eRI_None && m_pRenderer->RenderIndex != RenderIndex)
	{
		// TODO 同样的材质，不同渲染层级，需要重新创建一个Renderer
		//m_pRenderer = GetRenderSystem()->GetRenderManager()->CreateVertexRender(material->mMaterialID);
	}
	m_pRenderer->SetMaterial(material);
	m_pRenderer->SetTransform(Transform);
	m_pRenderer->IsStaticDraw = false;
	SetActive(true);
}

void E3DEngine::Sphere::SetActive(bool isActive)
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
			m_vecVertex[i].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);;
			m_vecVertex[i].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
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

void E3DEngine::Sphere::TransformChange()
{
	if (pCamera && !pCamera->boundingBoxFrustum(Transform->Position, 100))
	{
		return;
	}
	m_pRenderer->SetTransform(Transform);
	/*Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
	int vertexStartIndex = mRenderer->GetRendererBuffer(ID)->VertextStartIndex;
	std::vector<Vertex>::iterator it = m_vecVertex.begin();
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecVertex[i].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
		m_vecVertex[i].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);;
		m_vecVertex[i].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
		mRenderer->Vertices[vertexStartIndex + i] = m_vecVertex[i];
	}*/
	//m_pRenderer->TransformChange();
}

void E3DEngine::Sphere::CreateBehaviour()
{
	m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
	NEW_INSTANCE(Sphere);
	setBehaviourDefaultValue();
}

void E3DEngine::Sphere::setBehaviourDefaultValue()
{
	GameObject::setBehaviourDefaultValue();
}

