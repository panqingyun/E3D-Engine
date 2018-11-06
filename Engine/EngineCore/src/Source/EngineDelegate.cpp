//
//  EngineDelegate.cpp
//  Obj
//
//  Created by 潘庆云 on 2017/1/17.
//  Copyright © 2017年 潘庆云. All rights reserved.
//

#include "EngineDelegate.h"
#include "../Config/TableRegister.h"
#include <include/EngineAPI.h>

namespace E3DEngine
{
	EngineDelegate::EngineDelegate()
	{
		m_bIsInited = false;
		m_bPause = false;
		m_bRun = true;
	}


	E3DEngine::EngineDelegate & EngineDelegate::GetInstance()
	{
		static EngineDelegate _ins;
		return _ins;
	}

	EngineDelegate::~EngineDelegate() = default;
	
	void EngineDelegate::Initilize(bool isEditor)
	{
		if(m_bIsInited)
		{
			return;
		}
		m_bRun = !isEditor;
		m_bPauseRender = false;
		Application::Initialize();
		PhysicWorld::GetInstance().InitPhysics();
		Timer::Init();
		Debug::Init();
		m_bIsInited = true;
	}

	void EngineDelegate::UpdateRender()
	{
		if (m_bPause)
		{
			return;
		}
		if (m_bPauseRender)
		{
			m_bRenderPaused = true;
			return;
		}
		GetRenderSystem()->BeginFrame();
		ThreadTool::GetInstance().RunInvokeFun(RENDER_THREAD_ID);
		Scene * pCurScene = SceneManager::GetCurrentScene();
		if (pCurScene != nullptr)
		{
			SceneManager::GetCurrentScene()->RenderScene();
		}
		GetRenderSystem()->EndFrame();
	}


	void EngineDelegate::UpdateLogic(float deltaTime)
	{
		if (m_bPause)
		{
			return;
		}

		ThreadTool::GetInstance().RunInvokeFun(LOGIC_THREAD_ID);
		Timer::Update(deltaTime);

		Scene * pCurScene = SceneManager::GetCurrentScene();
		if (pCurScene != nullptr)
		{
			SceneManager::GetCurrentScene()->Update(deltaTime);
		}

		AutoreleasePool::GetInstance().Update();
		if (m_bRun)
		{
			Application::UpdateApp(deltaTime);
		}
	}

	void EngineDelegate::UpdatePhysics(float deltaTime)
	{
		if (m_bPause)
		{
			return;
		}

		ThreadTool::GetInstance().RunInvokeFun(PHYSIC_THREAD_ID);
		if (m_bRun)
		{
			PhysicWorld::GetInstance().Update(deltaTime);
		}
	}

	void EngineDelegate::SetEnginePause(bool bPause)
	{
		m_bPause = bPause;
	}

	bool EngineDelegate::GetEnginePause()
	{
		return m_bPause;
	}
	
	void EngineDelegate::Destory()
	{
		EffectFactory::GetInstance().Destory();
		Timer::Destory();
		TableRegister::Destory();
		PhysicWorld::GetInstance().Destory();
	}

	bool EngineDelegate::GetIsRun()
	{
		return m_bRun;
	}

	void EngineDelegate::SetIsRun(bool isRun)
	{
		m_bRun = isRun;
	}

	void EngineDelegate::SetPauseRender(bool isPause)
	{
		m_bPauseRender = isPause;
		if (isPause && GetRenderSystem()->getIsMutilThreadRender())
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

}
