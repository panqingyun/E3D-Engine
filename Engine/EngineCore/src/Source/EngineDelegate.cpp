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
		Application::Initialize();
		PhysicWorld::GetInstance().InitPhysics();
		Timer::Init();
		Debug::Init();
		m_bIsInited = true;
	}

	void EngineDelegate::Update(float deltaTime)
	{
		if (m_bPause)
		{
			return;
		}
		/*if (m_bRun)
		{
			PhysicWorld::GetInstance().Update(deltaTime);
		}*/
		Timer::Update(deltaTime);
		Scene * pCurScene = SceneManager::GetCurrentScene();
		if (pCurScene != nullptr )
		{
			SceneManager::GetCurrentScene()->Update(deltaTime);
		}

		AutoreleasePool::GetInstance().Update();
		Application::UpdateApp(deltaTime);
	}


	void EngineDelegate::UpdatePhysics(float deltaTime)
	{
		if (m_bPause)
		{
			return;
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
}
