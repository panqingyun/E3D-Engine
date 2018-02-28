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

	Renderer * GLES_RendererManager::GetRenderer(int materialID, bool isCreate)
	{
		if (m_mapVertexBuffers.find(materialID) == m_mapVertexBuffers.end())
		{
			if (isCreate)
			{
				GLES_Renderer * buffer = new GLES_Renderer;
				buffer->RenderIndex = eRI_Normal;
				m_mapVertexBuffers[materialID] = buffer;
				return buffer;
			}
			else
			{
				return nullptr;
			}
		}
		return m_mapVertexBuffers[materialID];
	}


	void GLES_RendererManager::AddRenderer(int materialID, Renderer * rd)
	{
		if (m_mapVertexBuffers.find(materialID) == m_mapVertexBuffers.end())
		{
			m_mapVertexBuffers[materialID] = rd;
		}
	}

	E3DEngine::Renderer * GLES_RendererManager::GenRender()
	{
		return new E3DEngine::GLES_Renderer();
	}


}
