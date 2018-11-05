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
		mRenderThreadInvoke = nullptr;
		mPhysicThreadInvoke = nullptr;
		mLogicThreadInvoke = nullptr;
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
			return;
		}
		GetRenderSystem()->BeginFrame();
		if (mRenderThreadInvoke != nullptr)
		{
			if (mRenderThreadInvoke->Func != nullptr)
			{
				mRenderThreadInvoke->Func(mRenderThreadInvoke->Param1, mRenderThreadInvoke->Param2);
			}
			OperateThread(mRenderThreadInvoke->ID, RESUME_THREAD);
			SAFE_DELETE(mRenderThreadInvoke);
		}
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
		if (mLogicThreadInvoke != nullptr)
		{
			if (mLogicThreadInvoke->Func != nullptr)
			{
				mLogicThreadInvoke->Func(mLogicThreadInvoke->Param1, mLogicThreadInvoke->Param2);
			}
			OperateThread(mLogicThreadInvoke->ID, RESUME_THREAD);
			SAFE_DELETE(mLogicThreadInvoke);
		}
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
		if (mPhysicThreadInvoke != nullptr)
		{
			if (mPhysicThreadInvoke->Func != nullptr)
			{
				mPhysicThreadInvoke->Func(mPhysicThreadInvoke->Param1, mPhysicThreadInvoke->Param2);
			}
			OperateThread(mPhysicThreadInvoke->ID, RESUME_THREAD);
			SAFE_DELETE(mPhysicThreadInvoke);
		}
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
	}


	void EngineDelegate::AddInvoke(int cur_thread_id, int dist_thread_id, ThreadInvokeFun func, void * param1 /*= nullptr*/, void *param2 /*= nullptr*/)
	{
		if (dist_thread_id == LOGIC_THREAD_ID)
		{
			mLogicThreadInvoke = new ThreadInfo(cur_thread_id, func, param1, param2);
		}
		else if (dist_thread_id == RENDER_THREAD_ID)
		{
			mRenderThreadInvoke = new ThreadInfo(cur_thread_id, func, param1, param2);
		}
		else if (dist_thread_id == PHYSIC_THREAD_ID)
		{
			mPhysicThreadInvoke = new ThreadInfo(cur_thread_id, func, param1, param2);
		}
		OperateThread(cur_thread_id, SUSPEND_THREAD);
	}

}
