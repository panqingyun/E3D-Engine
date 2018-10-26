//
//  E3DVertexBufferManager.cpp
//
//  Created by 潘庆云 on 2017/7/19.
//

#include "E3DRenderManager.hpp"
#include "src/Source/EngineDelegate.h"
#include "../E3DRenderSystem.hpp"

namespace E3DEngine
{
	Renderer * RendererManager::CreateRender(Material* material)
	{
		return nullptr;
	}

	Renderer * RendererManager::GetRenderer(int materialID, int vertexSize, RENDER_TYPE type, bool isStatic)
	{
		return nullptr;
	}


	E3DEngine::Renderer * RendererManager::GenRender()
	{
		return nullptr;
	}


	void RendererManager::AddRenderer(int materialID, Renderer * rd)
	{

	}

	void RendererManager::Cleanup()
	{
		m_mapVertexBuffers.clear();
	}

}
