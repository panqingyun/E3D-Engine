//
//  E3DScene.cpp
//  demo
//
//  Created by 潘庆云 on 2017/7/11.
//

#include "E3DScene.hpp"
#include "../Source/E3DDebug.h"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{	
	Scene::Scene()
	{
		dontDestoryScene	= false;
		m_SceneType		= eSceneType_defult;
		NodeType		= eT_Scene;
		Transform		= new CTransform;
		CreateBehaviour();
	}

	void Scene::Update(float deltaTime)
	{
		for (auto &node : m_vecObjList)
		{
			node.second->Update(deltaTime);
		}

		// 渲染场景
		GetRenderSystem()->BeginFrame();
		RenderScene(deltaTime);
		GetRenderSystem()->EndFrame();

	}
	
	void Scene::Destory()
	{
		if (dontDestoryScene)
		{
			return;
		}
		int childSize = m_vecObjList.size();
		for (int i = 0; i < childSize; i++)
		{
			auto node = m_vecObjList.begin()->second;
			if (node->NodeType == eT_Camera)
			{
				continue;
			}
			m_vecObjList.erase(node->ID);
			for (Camera * camera : m_vecCamera)
			{
				camera->GetRenderQueue()->Remove(static_cast<GameObject*>(node));
			}
			SAFE_DELETE(node);
		}
		for (Camera * camera : m_vecCamera)
		{
			SAFE_DELETE(camera);
		}
		GetRenderSystem()->Cleanup();
		m_vecObjList.clear();
	}
	
	void Scene::SceneReload()
	{
		if (!SceneReloadEvent.empty())
		{
			SceneReloadEvent(nullptr, nullptr);
		}
	}

	void Scene::DestoryAllOjectImmediately()
	{
		for(auto & it : m_vecObjList)
		{
			for (Camera * camera : m_vecCamera)
			{
				camera->GetRenderQueue()->Remove(static_cast<GameObject*>(it.second));
			}
			SAFE_DELETE(it.second);
		}
		m_vecObjList.clear();
	}

	void Scene::SetDontDestory(bool dontDestory)
	{
		dontDestoryScene = dontDestory;
	}

	void Scene::SetSceneType(eSceneType type)
	{
		m_SceneType = type;
	}

	void Scene::RenderScene(float deltaTime)
	{
		for (Camera * camera : m_vecCamera)
		{
			camera->Render(deltaTime);
		}
	}

	void Scene::ChangeRenderIndex(QWORD id, eRenderIndex index)
	{
		for (Camera *camera : m_vecCamera)
		{
			camera->GetRenderQueue()->ChangeRenderQueue(id, index);
		}
	}

	void Scene::AddCamera(Camera * pCamera)
	{
		bool isCanInsert = true;
		for (Camera * camera : m_vecCamera)
		{
			if (pCamera == camera)
			{
				isCanInsert = false;
			}
		}
		if (isCanInsert)
		{
			m_vecCamera.emplace_back(pCamera);
			for (auto &obj : m_vecObjList)
			{
				if (obj.second->NodeType != eT_GameObject)
				{
					continue;
				}
				if (!pCamera->GetRenderQueue()->FindInRenderQueue(static_cast<GameObject*>(obj.second)))
				{
					pCamera->GetRenderQueue()->Add(static_cast<GameObject*>(obj.second));
				}
			}
		}
	}

	void Scene::SortCamera()
	{
		std::sort(m_vecCamera.begin(), m_vecCamera.end(),
		[](Camera * camera1, Camera * camera2)
		{
			return camera1->GetDepth() < camera2->GetDepth();
		});
	}


	Camera* Scene::GetCamera(QWORD cameraID)
	{
		for (Camera * camera : m_vecCamera)
		{
			if (camera->ID == cameraID)
			{
				return camera;
			}
		}
		return nullptr;
	}


	void Scene::ChangeFrameSize(float w, float h)
	{
		for (Camera * camera : m_vecCamera)
		{
			camera->FrameSizeChange(w / h);
		}
	}

	E3DEngine::eSceneType Scene::GetSceneType()
	{
		return m_SceneType;
	}

	void Scene::AddChild(Object * node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (m_vecObjList.find(node->ID) != m_vecObjList.end())
		{
			if (node->NodeType == eT_GameObject)
			{
				for (Camera * camera : m_vecCamera)
				{
					if (camera->GetLayerMask() &static_cast<GameObject*>(node)->GetLayerMask())
					{
						camera->GetRenderQueue()->Add(static_cast<GameObject*>(node));
					}
				}
			}
			return;
		}

		m_vecObjList[node->ID] = node;
		
	}

	void Scene::RemoveChild(Object * node)
	{
		if (node == nullptr)
		{
			return;
		}
		DWORD id = node->ID;
		if (m_vecObjList.find(id) == m_vecObjList.end())
		{
			return;
		}
		
		if (m_vecObjList[id]->NodeType == eT_GameObject)
		{
			GameObject * go = static_cast<GameObject*>(m_vecObjList[id]);
			for (Camera * camera : m_vecCamera)
			{
				if (camera->GetLayerMask() & go->GetLayerMask())
				{
					camera->GetRenderQueue()->Remove(go);
				}
			}
		}
		m_vecObjList.erase(node->ID);
		SAFE_DELETE(node);
	}

	void Scene::RemoveChild(QWORD ID)
	{
		if (m_vecObjList.find(ID) == m_vecObjList.end())
		{
			return;
		}

		if (m_vecObjList[ID]->NodeType == eT_GameObject)
		{
			GameObject * go = static_cast<GameObject*>(m_vecObjList[ID]);
			for (Camera * camera : m_vecCamera)
			{
				if (camera->GetLayerMask() & go->GetLayerMask())
				{
					camera->GetRenderQueue()->Remove(go);
				}
			}
		}
		m_vecObjList.erase(ID);
		SAFE_DELETE(m_vecObjList[ID]);
	}


	void Scene::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		m_pBehaviour->Create(NAME_SPACE, "Scene");
		setBehaviourDefaultValue();
	}

	Scene::~Scene()
	{

	}

}
