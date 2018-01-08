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
		m_nObjectID = 0;
		m_bIsInited = false;
		m_bPause = false;
		RootTransform = nullptr;
	}
	
	void EngineDelegate::InitConfig(const char *path)
	{
		if (m_mapTableManager.find(path) != m_mapTableManager.end())
		{
			return;
		}
		std::vector<std::string> excList;
		TableManager* tblManager = TableRegister::RegisterAllTable(path);
		m_mapTableManager[path] = tblManager;
	}
	
    void EngineDelegate::SetResourcePath(const char *path)
    {
        Application::ResourcePath = path;
    }
	
	void EngineDelegate::DestoryTableManager(std::string id)
	{
		if (m_mapTableManager.find(id) == m_mapTableManager.end())
		{
			return;
		}
		SAFE_DELETE(m_mapTableManager[id]);
		m_mapTableManager.erase(id);
	}
	
	void EngineDelegate::AddDonotDestory(GameObject* obj)
	{
		if (m_mapDoNotDestoryObject.find(obj->ID) != m_mapDoNotDestoryObject.end())
		{
			return;
		}
		obj->SetDontDestory(true);
		m_mapDoNotDestoryObject[obj->ID] = obj;
	}
	
	TableManager * EngineDelegate::GetTableManager(std::string id)
	{
		if (m_mapTableManager.find(id) == m_mapTableManager.end())
		{
			return  nullptr;
		}
		return m_mapTableManager[id];
	}	
	
	void EngineDelegate::SetCommonResourcePath(const char * path)
	{
		Application::ResourcePath = path;
	}

	QWORD EngineDelegate::GenObjectID()
	{
		return  ++m_nObjectID;
	}

	void EngineDelegate::DestoryObject(GameObject * obj)
	{
		if (m_mapDoNotDestoryObject.find(obj->ID) != m_mapDoNotDestoryObject.end())
		{
			m_mapDoNotDestoryObject.erase(obj->ID);
		}
		SAFE_DELETE(obj);
	}
	
	EngineDelegate::~EngineDelegate() = default;
	
	void EngineDelegate::Initilize()
	{
		if(m_bIsInited)
		{
			return;
		}
		Application::Initialize();
		MeshFactory::GetInstance().Initilize();
		Physics::GetInstance().InitPhysics();
		Timer::Init();
		Debug::Init();
		m_pParticleSystem = new ParticleSystem;
		m_pParticleSystem->Initilize();
		m_bIsInited = true;
	}

	void EngineDelegate::Update(float deltaTime, bool selfClear)
	{
		Timer::Update(deltaTime);
		Physics::GetInstance().Update(deltaTime);
		Scene * pCurScene = SceneManager::GetInstance().GetCurrentScene();
		if (pCurScene != nullptr && RootTransform != nullptr)
		{	
			SceneManager::GetInstance().GetCurrentScene()->Update(deltaTime);
			RootTransform->Update();
		}

		m_pParticleSystem->Update(deltaTime);
		AutoreleasePool::GetInstance().Update();
		Application::UpdateApp(deltaTime);
	}
    
    void EngineDelegate::SetSceneType(int type)
    {
        Scene * pScene = SceneManager::GetInstance().GetCurrentScene();
        if(pScene != nullptr)
        {
            pScene->SetSceneType((E3DEngine::eSceneType)type);
        }
    }

	void EngineDelegate::ChangeScene(uint sceneID)
	{
		if (sceneID == NULL_SCENE)
		{
			RootTransform = nullptr;
			return;
		}
		if (!SceneClearEvent.empty())
		{
			SceneClearEvent(nullptr, nullptr);
		}
		if (!SceneManager::GetInstance().ChangeScene(sceneID))
		{
			return;
		}

		Scene * pScene = SceneManager::GetInstance().GetCurrentScene();
		RootTransform = pScene->Transform;

		if (pScene->dontDestoryScene)
		{
			return;
		}
		for (auto & it : m_mapDoNotDestoryObject)
		{
			pScene->AddChild(it.second);
			if (it.second->NodeType != eT_Bone)
			{
				RootTransform->AddChild(it.first, it.second->Transform);
			}
		}
	}

	void EngineDelegate::ChangeScene(E3DEngine::Scene *scene)
	{
		int sceneId = 0;
		if (scene != nullptr)
		{
			sceneId = scene->ID;
		}
		ChangeScene(sceneId);
	}

	void EngineDelegate::SetEnginePause(bool bPause)
	{
		m_bPause = bPause;
	}


	bool EngineDelegate::GetEnginePause()
	{
		return m_bPause;
	}

	void EngineDelegate::DestoryScene(E3DEngine::Scene *scene)
	{
		if (scene == nullptr)
		{
			return;
		}
		SceneManager::GetInstance().DestoryScene(scene);
	}

	void EngineDelegate::Destory()
	{
		EffectFactory::GetInstance().Destory();
		MeshFactory::GetInstance().Destory();
		Timer::Destory();
		if (RootTransform != nullptr)
		{
			RootTransform->Destory();
		}
		
		m_pParticleSystem->Destory();
		
		for(std::map<std::string, TableManager*>::iterator it = m_mapTableManager.begin();
			it != m_mapTableManager.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		m_mapTableManager.clear();
		TableRegister::Destory();
		Physics::GetInstance().Destory();
	}
}
