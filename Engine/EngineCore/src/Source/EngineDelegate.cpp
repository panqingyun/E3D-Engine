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
	}

	EngineDelegate::~EngineDelegate() = default;
	
	void EngineDelegate::Initilize()
	{
		if(m_bIsInited)
		{
			return;
		}
		Application::Initialize();
		Physics::GetInstance().InitPhysics();
		Timer::Init();
		Debug::Init();
		m_bIsInited = true;
	}

	void EngineDelegate::Update(float deltaTime)
	{
		Timer::Update(deltaTime);
		Physics::GetInstance().Update(deltaTime);
		Scene * pCurScene = SceneManager::GetCurrentScene();
		if (pCurScene != nullptr )
		{
			SceneManager::GetCurrentScene()->Update(deltaTime);
		}

		AutoreleasePool::GetInstance().Update();
		Application::UpdateApp(deltaTime);
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
		Physics::GetInstance().Destory();
	}
}
