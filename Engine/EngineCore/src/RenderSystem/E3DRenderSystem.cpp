//
//  RenderSystem.cpp
//
//  Created by 潘庆云 on 2017/1/22.
//

#include "E3DRenderSystem.hpp"
#include "..\Source\E3DThreadTool.h"
#include "..\Scene\E3DSceneManager.hpp"
#include "..\Source\E3DDebug.h"

E3DEngine::RenderSystem * g_pRenderSystem = nullptr;
void SetRenderSystem(E3DEngine::RenderSystem * rs)
{
	g_pRenderSystem = rs;
}


E3D_EXPORT_DLL E3DEngine::RenderSystem * GetRenderSystem()
{
	return g_pRenderSystem;
}

namespace E3DEngine
{

	void RenderSystem::SetPauseRender(bool isPause)
	{
		m_bPauseRender = isPause;
		if (isPause && m_bIsMutilThreadRender)
		{
			m_bRenderPaused = false;
			while (!m_bRenderPaused)
			{
#if (defined WIN32)
				::Sleep(1);
#else
				::sleep(1);
#endif
			}
		}
	}

	void RenderSystem::Render()
	{
		if (m_bPauseRender)
		{
			m_bRenderPaused = true;
			return;
		}
		BeginFrame();
		ThreadTool::GetInstance().RunInvokeFun(RENDER_THREAD_ID);
		Scene * pCurScene = SceneManager::GetCurrentScene();
		if (pCurScene != nullptr)
		{
			SceneManager::GetCurrentScene()->RenderScene();
		}
		EndFrame();
	}

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


	void RenderSystem::CreateShareContext()
	{
		m_bIsMutilThreadRender = true;
	}

	void RenderSystem::UseShareContext()
	{

	}


	void RenderSystem::UseRenderContext()
	{

	}


	void RenderSystem::SetCullFaceType(CULL_FACE type)
	{

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
		m_bRenderPaused = false;
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


	bool RenderSystem::getIsMutilThreadRender()
	{
		return m_bIsMutilThreadRender;
	}

	void RenderSystem::Clear(Color4 color, int clearType)
	{
		
	}

	void RenderSystem::BindDefaultBackbuffer()
	{

	}

	void E3DEngine::RenderSystem::ChangeRenderSurface(NATIVE_WINDOW_TYPE windowHandle)
	{

	}
}
