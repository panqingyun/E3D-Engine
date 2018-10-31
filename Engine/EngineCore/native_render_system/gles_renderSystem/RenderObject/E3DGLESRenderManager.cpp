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
	Renderer * GLES_RendererManager::GetRenderer(int materialID, int vertexSize, RENDER_TYPE type, bool isStatic)
	{
		Renderer * buffer = nullptr;
		if (!isStatic)
		{
			buffer = newRenderer(type, materialID);
		}
		else
		{
			int rendererID = -1;
			if (m_mapMaterialID2RendererID.find(materialID) != m_mapMaterialID2RendererID.end())
			{
				rendererID = m_mapMaterialID2RendererID[materialID];
			}
			if (m_mapVertexBuffers.find(rendererID) == m_mapVertexBuffers.end())
			{
				buffer = newRenderer(type, materialID);
			}
			else
			{
				buffer = m_mapVertexBuffers[rendererID];
				if (buffer->GetVertextCount() + vertexSize > MAX_VERTEX_NUMBER || !buffer->IsStaticDraw)
				{
					buffer = newRenderer(type, materialID);
				}
			}
			m_mapMaterialID2RendererID[materialID] = buffer->ID;
		}
		buffer->IsStaticDraw = isStatic;;
		return buffer;
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


	void GLES_RendererManager::Cleanup()
	{
		for (auto & render : m_mapVertexBuffers)
		{
			SAFE_DELETE(render.second);
		}
		m_mapVertexBuffers.clear();
	}

	E3DEngine::Renderer * GLES_RendererManager::newRenderer(RENDER_TYPE type,  int materialID)
	{
		Renderer * buffer = nullptr;
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
