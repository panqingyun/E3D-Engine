//
//  E3DScene.cpp
//  demo
//
//  Created by 潘庆云 on 2017/7/11.
//

#include "E3DScene.hpp"
#include "../Source/E3DDebug.h"
#include "../Source/EngineDelegate.h"
#include "../RenderSystem/E3DRenderQueue.h"
#include "../Source/FilePath.h"
#include "../Config/TableRegister.h"
#include "../Object/E3DPrefab.h"
#include "E3DSceneLoader.h"

namespace E3DEngine
{		
	Scene::Scene()
	{
		m_nObjectID = 0;
		mObjectType = eT_Scene;
		rootObject = new GameObject;
		rootObject->SetActive(true);
		usedDirectionLight = nullptr;

		m_vecObjList[rootObject->ID] = rootObject;
		CreateBehaviour();

	}

	void Scene::Create(std::string filePath)
	{
		LoadSceneObjects(filePath);
		mName = GetFileName(filePath);
		m_scenePath = filePath;
	}

	int xc = 0;
	void Scene::Update(float deltaTime)
	{
		// 运行时执行，编辑器下不执行
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			for (auto &node : m_vecObjList)
			{
				node.second->Update(deltaTime);
			}
		}
		rootObject->Transform->Update();
		// 渲染场景
		GetRenderSystem()->BeginFrame();
		RenderScene(deltaTime);
		GetRenderSystem()->EndFrame();
		// 运行时执行，编辑器下不执行
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			for (auto &node : m_vecObjList)
			{
				if (node.second->mObjectType == eT_GameObject)
				{
					static_cast<GameObject*>(node.second)->AfterUpdate(deltaTime);
				}
			}
		}
	}

	GameObject* Scene::GetRootObject()
	{
		return rootObject;
	}
	
	void Scene::Destory()
	{
		PhysicWorld::GetInstance().Cleanup();
		SAFE_DELETE(rootObject);
		GetRenderSystem()->Cleanup();
		m_mapRenders.clear();
		m_vecObjList.clear();
		m_mapLights.clear();
		m_vecCamera.clear();
		TableRegister::Destory();
#ifdef __E3D_EDITOR__
		const std::vector<Camera*> &cameras = GetEditorCameras();
		for (auto &camera : cameras)
		{
			camera->GetRenderQueue()->Clear();
			camera->ClearRT();
		}
#endif
	}

	void Scene::DestoryAllOjectImmediately()
	{
		for(auto & it : m_vecObjList)
		{
			//for (Camera * camera : m_vecCamera)
			//{
			//	camera->GetRenderQueue()->Remove(static_cast<GameObject*>(it.second));
			//}
			SAFE_DELETE(it.second);
		}
		m_vecObjList.clear();
	}

	void Scene::RenderScene(float deltaTime)
	{
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			for (Camera * camera : m_vecCamera)
			{
				if (camera->IsActive)
				{
					camera->Render(deltaTime);
				}
			}
		}
#ifdef __E3D_EDITOR__
		else
		{
			const std::vector<Camera*> &cameras = GetEditorCameras();
			for (auto &camera : cameras)
			{
				camera->Render(deltaTime);
			}
		}
#endif
	}

	void Scene::ChangeRenderIndex(UINT id, eRenderIndex index)
	{
        for(Camera *camera : m_vecCamera)
		{
			camera->GetRenderQueue()->ChangeRenderQueue(id, index);
		}

#if __E3D_EDITOR__
		const std::vector<Camera*> &cameras = GetEditorCameras();
		for (auto &camera : cameras)
		{
			camera->GetRenderQueue()->ChangeRenderQueue(id, index);
		}
#endif
	}

	void Scene::AddCamera(Camera * pCamera)
	{
		bool isCanInsert = true;
        for(Camera * camera : m_vecCamera)
		{
			if (pCamera == camera)
			{
				isCanInsert = false;
			}
		}
		if (isCanInsert)
		{
			m_vecCamera.emplace_back(pCamera);
			ChangeCameraObject(pCamera);
		}
#if __E3D_EDITOR__
		const std::vector<Camera*> &cameras = GetEditorCameras();
		for (auto &camera : cameras)
		{
			ChangeCameraObject(camera);
		}
#endif
	}

	void Scene::SortCamera()
	{
		std::sort(m_vecCamera.begin(), m_vecCamera.end(),
		[](Camera * camera1, Camera * camera2)
		{
			return camera1->GetDepth() < camera2->GetDepth();
		});
	}

	void Scene::ChangeCameraObject(Camera * pCamera)
	{
		for (auto &obj : m_mapRenders)
		{
			if (obj.second->GetLayerMask() & pCamera->GetLayerMask())
			{
				pCamera->GetRenderQueue()->Add(obj.second);
			}
		}
	}

	void Scene::ChangeRenderObjectLayer(RenderObject * rb)
	{
		if (m_mapRenders.find(rb->ID) == m_mapRenders.end())
		{
			return;
		}

		for (Camera * camera : m_vecCamera)
		{
			if (camera->GetLayerMask() & rb->GetLayerMask())
			{
				camera->GetRenderQueue()->Add(rb);
			}
			else
			{
				camera->GetRenderQueue()->Remove(rb);
			}
		}

#if __E3D_EDITOR__
		const std::vector<Camera*> &cameras = GetEditorCameras();
		for (auto &camera : cameras)
		{
			if (camera->GetLayerMask() & rb->GetLayerMask())
			{
				camera->GetRenderQueue()->Add(rb);
			}
			else
			{
				camera->GetRenderQueue()->Remove(rb);
			}
		}
#endif
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


	Camera * Scene::GetMainCamera()
	{
		if (m_vecCamera.size() != 0)
		{
			return m_vecCamera[m_vecCamera.size() - 1];
		}
		return nullptr;
	}

	void Scene::ChangeViewportSize(float w, float h)
	{
        for (auto &camera : m_vecCamera) 
		{
            camera->ChangeViewport(w / h);
        }
#ifdef __E3D_EDITOR__
		const std::vector<Camera*> &cameras = GetEditorCameras();
		for (auto &camera : cameras)
		{
			camera->ChangeViewport(w / h);
		}
#endif
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
		
        for(Camera * camera : m_vecCamera)
		{
			if (camera->GetLayerMask() & layer)
			{
				camera->GetRenderQueue()->Add(rb);
			}
		}
#ifdef __E3D_EDITOR__
		const std::vector<Camera*> &cameras = GetEditorCameras();
		for (auto &camera : cameras)
		{
			if (camera->GetLayerMask() & layer)
			{
				camera->GetRenderQueue()->Add(rb);
			}
		}
#endif
	}

	void Scene::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		mBehaviour->Create(NAME_SPACE, "Scene");
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

	void Scene::AddObject(Object * obj)
	{
		if (obj == nullptr)
		{
			return;
		}
		if (obj->mObjectType == eT_GameObject || obj->mObjectType == eT_Camera)
		{
			GameObject *go = static_cast<GameObject*>(obj);
			if (rootObject->FindChild(go->ID))
			{
				return;
			}
			if (m_vecObjList.find(go->ID) != m_vecObjList.end())
			{
				m_vecObjList.erase(go->ID);
			}
			rootObject->AddChild(go);

		}
		m_vecObjList[obj->ID] = obj;
	}

	void Scene::RemoveObject(Object * node)
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

	void Scene::RemoveObject(UINT ID)
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

	UINT Scene::GenObjectID()
	{
		return  ++m_nObjectID;
	}

	std::string Scene::GetScenePath()
	{
		return m_scenePath;
	}


	void Scene::SetScenePath(std::string path)
	{
		m_scenePath = path;
	}

	void Scene::Save()
	{
		SaveCurrentScene();
	}

}
