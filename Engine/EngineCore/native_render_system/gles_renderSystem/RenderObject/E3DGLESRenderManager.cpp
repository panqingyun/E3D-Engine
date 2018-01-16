//
//  E3DVertexBufferManager.cpp
//
//  Created by 潘庆云 on 2017/7/19.
//

#include "E3DGLESRenderManager.hpp"
#include <src/RenderSystem/E3DRenderSystem.hpp>

namespace E3DEngine
{
	Renderer * GLES_RendererManager::CreateVertexRender(int materialID)
	{
		GLES_Renderer * buffer = (GLES_Renderer *)GetRenderer(materialID);	
		buffer->pMaterial = GetRenderSystem()->GetMaterialManager()->GetMaterial(materialID);
		return buffer;
	}

	Renderer * GLES_RendererManager::GetRenderer(int materialID)
	{
		if (m_mapVertexBuffers.find(materialID) == m_mapVertexBuffers.end())
		{
			GLES_Renderer * buffer = new GLES_Renderer;
			buffer->RenderIndex = eRI_Normal;
			m_mapVertexBuffers[materialID] = buffer;
			return buffer;
		}
		return m_mapVertexBuffers[materialID];
	}


	E3DEngine::Renderer * GLES_RendererManager::GenRender()
	{
		return new E3DEngine::GLES_Renderer();
	}

}
