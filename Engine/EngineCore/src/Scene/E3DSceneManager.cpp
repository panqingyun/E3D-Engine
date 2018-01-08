//
//  E3DSceneManager.cpp
//
//  Created by 潘庆云 on 2017/8/11.
//

#include "E3DSceneManager.hpp"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{
	void SceneManager::DestoryScene(E3DEngine::Scene *scene)
	{
		if (scene == nullptr)
		{
			return;
		}
		if (m_mapScenes.find(scene->ID) == m_mapScenes.end())
		{
			return;
		}
		bool isDestoryCurrentScene = false;
		if (scene == m_mapScenes[m_currentUseSceneID])
		{
			isDestoryCurrentScene = true;
		}
		scene->Destory();
		m_mapScenes.erase(scene->ID);
		SAFE_DELETE(scene);
		if (isDestoryCurrentScene)
		{
			m_currentUseSceneID = NULL_SCENE;
			m_lastSceneID = NULL_SCENE;
			EngineDelegate::GetInstance().ChangeScene(nullptr);
		}
	}

	SceneManager::SceneManager()
	{
		m_currentUseSceneID = NULL_SCENE;
		m_lastSceneID = NULL_SCENE;
	}

	void SceneManager::Initilize()
	{

	}

	void SceneManager::Destory()
	{
		for (auto & scene : m_mapScenes)
		{
			scene.second->Destory();
			SAFE_DELETE(scene.second);
		}
		EngineDelegate::GetInstance().ChangeScene(nullptr);
		GetRenderSystem()->Cleanup();
		m_mapScenes.clear();
	}

	E3DEngine::Scene * SceneManager::CreateScene()
	{
		Scene * pScene = new Scene;
		m_mapScenes[pScene->ID] = pScene;

		return pScene;
	}

	bool SceneManager::ChangeScene(uint sceneID)
	{
		if (m_mapScenes.find(sceneID) == m_mapScenes.end())
		{
			return false;
		}
		if (sceneID == m_currentUseSceneID)
		{
			return false;
		}
		m_lastSceneID = m_currentUseSceneID;
		if (m_mapScenes.find(m_currentUseSceneID) != m_mapScenes.end())
		{
			if (m_mapScenes[m_currentUseSceneID] == nullptr)
			{
				m_mapScenes.erase(m_currentUseSceneID);
			}
			else
			{
				m_mapScenes[m_currentUseSceneID]->Destory();
			}
		}
		m_currentUseSceneID = sceneID;
		
		return true;
	}

	bool SceneManager::ChangeScene(Scene * scene)
	{
		if (scene == nullptr)
		{
			return false;
		}
		uint sceneID = scene->ID;
		return ChangeScene(sceneID);

	}

	E3DEngine::Scene * SceneManager::GetCurrentScene()
	{
		if (m_mapScenes.find(m_currentUseSceneID) == m_mapScenes.end())
		{
			return nullptr;
		}
		return m_mapScenes[m_currentUseSceneID];
	}

	E3DEngine::Scene * SceneManager::GetScene(uint sceneID)
	{
		if (m_mapScenes.find(sceneID) == m_mapScenes.end())
		{
			return nullptr;
		}
		return m_mapScenes[sceneID];
	}

}
