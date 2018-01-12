#include "E3DSkyBox.h"
#include "E3DRenderObject.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "E3DTransform.hpp"
#include "../Camera/E3DCamera.h"

void E3DEngine::SkyBox::Create(float l, float w, float h)
{
	Box::Create(l, w, h);
	
	// front
	m_vecVertex[0].SettextureCoord(1, 0);		
	m_vecVertex[1].SettextureCoord(1.0, 1.0 / 2.0);				
	m_vecVertex[2].SettextureCoord(2.0 / 3.0, 1.0 / 2.0);
	m_vecVertex[3].SettextureCoord(2.0 / 3.0, 0.0);				

	// up
	m_vecVertex[4].SettextureCoord(1.0 / 3.0, 1.0 / 2.0);
	m_vecVertex[5].SettextureCoord(2.0 / 3, 1.0 / 2.0);
	m_vecVertex[6].SettextureCoord(2.0 /3.0, 1.0);
	m_vecVertex[7].SettextureCoord(1.0 / 3.0, 1.0 );

	// back
	m_vecVertex[8].SettextureCoord(0, 0);
	m_vecVertex[9].SettextureCoord(1.0 / 3, 0.0);
	m_vecVertex[10].SettextureCoord(1.0 / 3, 1.0 / 2.0);
	m_vecVertex[11].SettextureCoord(0.0, 1.0 / 2.0);

	// down
	m_vecVertex[12].SettextureCoord(2.0 / 3, 1.0 / 2);
	m_vecVertex[13].SettextureCoord(1, 1.0 / 2);
	m_vecVertex[14].SettextureCoord(1, 1);
	m_vecVertex[15].SettextureCoord(2.0 / 3.0 , 1.0);

	// left
	m_vecVertex[16].SettextureCoord(0.0, 1.0 / 2.0);
	m_vecVertex[17].SettextureCoord(1.0 / 3.0, 1.0 / 2.0);
	m_vecVertex[18].SettextureCoord(1.0 / 3.0, 1.0);
	m_vecVertex[19].SettextureCoord(0.0, 1.0);

	// right
	m_vecVertex[20].SettextureCoord(2.0 / 3.0, 0.0);
	m_vecVertex[21].SettextureCoord(2.0 / 3.0, 1.0 / 2.0);
	m_vecVertex[22].SettextureCoord(1.0 / 3.0, 1.0 / 2.0);
	m_vecVertex[23].SettextureCoord(1.0 / 3.0, 0.0);

}

void E3DEngine::SkyBox::SetMaterial(Material * material)
{
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

