//
//  E3DVertexBufferManager.cpp
//
//  Created by 潘庆云 on 2017/7/19.
//

#include "E3DGLESRenderManager.hpp"
#include "../E3DGLESRenderSystem.hpp"
#include "E3DGLESMeshRender.h"

namespace E3DEngine
{
	void GLES_RendererManager::AddRenderer(int materialID, BatchRenderer * rd)
	{
		if (m_mapVertexBuffers.find(materialID) == m_mapVertexBuffers.end())
		{
			m_mapVertexBuffers[materialID] = rd;
		}
	}

	E3DEngine::BatchRenderer * GLES_RendererManager::GenRender()
	{
		return new E3DEngine::GLES_Renderer();
	}


	void GLES_RendererManager::Cleanup()
	{
		for (auto & render : m_mapVertexBuffers)
		{
			SAFE_DELETE(render.second);
		}
		m_mapVertexBuffers.clear();
	}

	E3DEngine::BatchRenderer * GLES_RendererManager::newRenderer(RENDER_TYPE type,  int materialID)
	{
		BatchRenderer * buffer = nullptr;
		switch (type)
		{
		case E3DEngine::MESH:
			buffer = new GLES_MeshRender;
			break;
		default:
			buffer = new GLES_Renderer;
			break;
		}
		buffer->RenderIndex = eRI_Normal;
		m_mapVertexBuffers[buffer->ID] = buffer;
		buffer->SetMaterial(GLES_RenderSystem::GetRenderSystem()->GetMaterialManager()->GetMaterial(materialID));	
		return buffer;
	}

}
