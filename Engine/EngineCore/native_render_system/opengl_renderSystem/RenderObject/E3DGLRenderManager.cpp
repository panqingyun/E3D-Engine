//
//  E3DVertexBufferManager.cpp
//
//  Created by 潘庆云 on 2017/7/19.
//

#include "E3DGLRenderManager.hpp"
#include "../E3DGL_RenderSystem.h"
#include "E3DGLMeshRender.h"

namespace E3DEngine
{
	void GL_RendererManager::AddRenderer(int materialID, BatchRenderer * rd)
	{
		if (m_mapVertexBuffers.find(materialID) == m_mapVertexBuffers.end())
		{
			m_mapVertexBuffers[materialID] = rd;
		}
	}

	E3DEngine::BatchRenderer * GL_RendererManager::GenRender()
	{
		return new E3DEngine::GL_Renderer();
	}


	void GL_RendererManager::Cleanup()
	{
		for (auto & render : m_mapVertexBuffers)
		{
			SAFE_DELETE(render.second);
		}
		m_mapVertexBuffers.clear();
	}

	E3DEngine::BatchRenderer * GL_RendererManager::newRenderer(RENDER_TYPE type,  int materialID)
	{
		BatchRenderer * buffer = nullptr;
		switch (type)
		{
		case E3DEngine::MESH:
			buffer = new GL_MeshRender;
			break;
		default:
			buffer = new GL_Renderer;
			break;
		}
		buffer->RenderIndex = eRI_Normal;
		m_mapVertexBuffers[buffer->ID] = buffer;
		buffer->SetMaterial(GL_RenderSystem::GetRenderSystem()->GetMaterialManager()->GetMaterial(materialID));
		return buffer;
	}

}
