//
//  RenderSystem.cpp
//
//  Created by 潘庆云 on 2017/1/22.
//

#include "E3DRenderSystem.hpp"

E3DEngine::RenderSystem * g_pRenderSystem = nullptr;
void SetRenderSystem(E3DEngine::RenderSystem * rs)
{
	g_pRenderSystem = rs;
}


E3DEngine::RenderSystem * GetRenderSystem()
{
	return g_pRenderSystem;
}

namespace E3DEngine
{
	void RenderSystem::Initilize()
	{
	}

	void RenderSystem::BeginFrame()
	{
				
	}

	void RenderSystem::EndFrame()
	{
	}

	void RenderSystem::Cleanup()
	{

	}

	Vector2 RenderSystem::GetFrameSize()
	{
		return Vector2(m_frameWidth, m_frameHeight);
	}


	E3DEngine::RendererManager * RenderSystem::GetRenderManager()
	{
		return m_pRenderManager;
	}

	E3DEngine::MaterialManager * RenderSystem::GetMaterialManager()
	{
		return m_pMaterialManager;
	}


	E3DEngine::TextureDataManager * RenderSystem::GetTextureDataManager()
	{
		return m_pTextureDataManager;
	}


	E3DEngine::ShaderManager * RenderSystem::GetShaderManager()
	{
		return m_pShaderManager;
	}

	std::string RenderSystem::GetName()
	{
		return "RenderSystem";
	}

	RenderSystem::RenderSystem()
	{
	}

	void RenderSystem::setFrameHeight(float height)
	{
		this->m_frameHeight = height;
	}

	void RenderSystem::setFrameWidth(float width)
	{
		this->m_frameWidth = width;
	}

	float RenderSystem::getFrameHeight()
	{
		return this->m_frameHeight;
	}

	float RenderSystem::getFrameWidth()
	{
		return this->m_frameWidth;
	}

	void RenderSystem::Clear(Color4 color, int clearType)
	{
		
	}

	void RenderSystem::BindDefaultBackbuffer()
	{

	}


	E3DEngine::Render2Texture * RenderSystem::CreateRtt(float width, float height)
	{
		return nullptr;
	}

	void E3DEngine::RenderSystem::ChangeRenderSurface(NATIVE_WINDOW_TYPE windowHandle)
	{

	}
}
