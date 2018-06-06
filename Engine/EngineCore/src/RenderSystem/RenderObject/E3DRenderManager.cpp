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
	Renderer * RendererManager::CreateVertexRender(int materialID)
	{
		return nullptr;
	}

	Renderer * RendererManager::GetRenderer(int materialID, RENDER_TYPE type)
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

	void RendererManager::Destory()
	{
		m_mapVertexBuffers.clear();
	}

}
