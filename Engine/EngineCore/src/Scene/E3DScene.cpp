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
		rootObject		= new GameObject;

		usedDirectionLight = nullptr;
		m_vecObjList[rootObject->ID] = rootObject;
		CreateBehaviour();
	}

	void Scene::Update(float deltaTime)
	{
		for (auto &node : m_vecObjList)
		{
			node.second->Update(deltaTime);
		}
		rootObject->Transform->Update();
		// 渲染场景
		GetRenderSystem()->BeginFrame();
		RenderScene(deltaTime);
		GetRenderSystem()->EndFrame();
		for (auto &node : m_vecObjList)
		{
			if (node.second->NodeType == eT_GameObject)
			{
				static_cast<GameObject*>(node.second)->AfterUpdate(deltaTime);
			}
		}

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
			SAFE_DELETE(node);
		}
		for (Camera * camera : m_vecCamera)
		{
			SAFE_DELETE(camera);
		}
		GetRenderSystem()->Cleanup();
		m_mapRenders.clear();
		m_vecObjList.clear();
		m_mapLights.clear();
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
				//camera->GetRenderQueue()->Remove(static_cast<GameObject*>(it.second));
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

	void Scene::ChangeRenderIndex(UINT id, eRenderIndex index)
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
			for (auto &obj : m_mapRenders)
			{
				if (!pCamera->GetRenderQueue()->FindInRenderQueue(obj.second))
				{
					pCamera->GetRenderQueue()->Add(obj.second);
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


	Camera* Scene::GetCamera(UINT cameraID)
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
		if (node->NodeType == eT_GameObject)
		{			
			GameObject *go = static_cast<GameObject*>(node);
			if (rootObject->FindChild(go->ID))
			{
				return;
			}
			if (m_vecObjList.find(go->ID) != m_vecObjList.end())
			{
				m_vecObjList.erase(go->ID);
				rootObject->AddChild(go);
			}
			
		}
		m_vecObjList[node->ID] = node;
		
	}

	void Scene::AddRenderObject(RenderObject* rb, UINT layer)
	{
		if (rb == nullptr)
		{
			return;
		}

		if (m_mapRenders.find(rb->ID) != m_mapRenders.end())
		{
			return;
		}

		m_mapRenders[rb->ID] = rb;

		for (Camera * camera : m_vecCamera)
		{
			if (camera->GetLayerMask() & layer)
			{
				camera->GetRenderQueue()->Add(rb);
			}
		}
	}

	void Scene::RemoveChild(Object * node)
	{
		if (node == nullptr)
		{
			return;
		}
		DWORD id = node->ID;

		if (rootObject->FindChild(id))
		{
			GameObject * go = static_cast<GameObject*>(node);
			
			rootObject->RemoveChild(go);
		}
		else
		{
			if (m_vecObjList.find(id) == m_vecObjList.end())
			{
				return;
			}
			m_vecObjList.erase(node->ID);
		}
	}

	void Scene::RemoveChild(UINT ID)
	{
		if (rootObject->FindChild(ID))
		{
			rootObject->RemoveChild(ID);
		}
		else
		{
			if (m_vecObjList.find(ID) == m_vecObjList.end())
			{
				return;
			}
			m_vecObjList.erase(ID);
		}
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

	void Scene::AddLight(Light * light)
	{
		if (m_mapLights.find(light->ID) != m_mapLights.end())
		{
			return;
		}

		if (light->Type == eDIRECTION_LIGHT)
		{
			usedDirectionLight = (DirectionLight*)light;
		}
		else
		{
			m_mapLights[light->ID] = light;
		}
	}


	void Scene::DeleteLight(Light *light)
	{
		if (light == nullptr)
		{
			return;
		}

		if (light->Type == eDIRECTION_LIGHT)
		{
			SAFE_DELETE(usedDirectionLight);
		}
		else if (light->Type == ePOINT_LIGHT)
		{
			if (m_mapLights.find(light->ID) != m_mapLights.end())
			{
				m_mapLights.erase(light->ID);
				SAFE_DELETE(light);
			}
		}
	}

	Light * Scene::GetDirectionalLight()
	{ 
		return usedDirectionLight; 
	}

	std::map<UINT, Light*>& Scene::GetPointLights()
	{
		return m_mapLights;
	}

}
