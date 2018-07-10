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

namespace E3DEngine
{	
	const std::string NM_GameObject = "GameObject";
	const std::string TP_Camera = "Camera";
	const std::string TP_DLight = "DirectionLight";
	const std::string TP_PLight = "PointLight";
	const std::string TP_SkyBox = "SkyBox";
	const std::string TP_Mesh = "Mesh";
	const std::string TP_Particle = "Particle";
	const std::string TP_Cube = "Cube";
	const std::string TP_Sphere = "Sphere";
	const std::string TP_Empty = "Empty";
	const string _typeName = "Type";
	const string TP_Terrain = "Terrain";

	const string _Name = "Name";
	const string material_TypeName = "Material";
	const string _FilePath = "FilePath";
	const string _SelectID = "SelectID";
	const string _LayerMask = "LayerMask";
	const string _Layer_AllLayer = "AllLayer";
	const string _Active = "Active";

	const string transform_TypeName = "Transform";
	const string _Position = "Posistion";
	const string _Rotation = "Rotation";
	const string _Scale = "Scale";

	const string _Transform = "Transform";
	const string _Material = "Material";
	const string _Particle = "Particle";

	const string _ClearColor = "ClearColor";
	const string _Color = "Color";

	const string _RenderIndex = "RenderIndex";

	const string _RenderIndex_Transparent = "Transparent";
	const string _RenderIndex_Normal = "Normal";
	const string _RenderIndex_LowMost = "LowMost";
	const string _RenderIndex_TopMost = "TopMost";

	const string _Component = "Component";
	const string _Component_ClassName = "ClassName";

	const string _Camera_CullMask = "CullingMask";
	const string _Camera_CullMask_Everything = "Everything";
	const string _Range = "Range";

	using createGameObjectFun = GameObject*(*)(TiXmlElement *objectElement);
	std::map<std::string, createGameObjectFun> createFun;
	std::map<std::string, UINT> renderIndexMap;
	void createObjects(GameObject * parent, TiXmlElement* rootElem);
	std::string sceneFolderPath = "";

	Color4 createColor(std::string colorStr)
	{
		std::vector<std::string> colorS = StringBuilder::Split(colorStr, ",");
		float r = Convert::ToFloat(colorS[0]);
		float g = Convert::ToFloat(colorS[1]);
		float b = Convert::ToFloat(colorS[2]);
		float a = Convert::ToFloat(colorS[3]);

		return Color4(r, g, b, a);
	}

	vec3f getVector3(std::string vecStr)
	{
		std::vector<std::string> colorS = StringBuilder::Split(vecStr, ",");
		float x = Convert::ToFloat(colorS[0]);
		float y = Convert::ToFloat(colorS[1]);
		float z = Convert::ToFloat(colorS[2]);

		return vec3f(x, y, z);
	}

	void createComponent(TiXmlElement *objectElement, GameObject *go)
	{
		if (objectElement == nullptr)
		{
			return;
		}

		std::string comName = *objectElement->Attribute(_Component_ClassName);
		go->AddComponent(comName.c_str());
	}

	void parseTransform(TiXmlElement *objectElement, CTransform * transform)
	{
		if (transform == nullptr)
		{
			return;
		}
		if (objectElement == nullptr)
		{
			return;
		}

		transform->SetPosition(getVector3(*objectElement->Attribute(_Position)));
		transform->SetRotation(getVector3(*objectElement->Attribute(_Rotation)));
		transform->SetScale(getVector3(*objectElement->Attribute(_Scale)));
	}

	void setRenderIndex(TiXmlElement *objectElement, GameObject * go)
	{
		if (objectElement->Attribute(_RenderIndex) == nullptr)
		{
			return;
		}
		std::string  rd = *objectElement->Attribute(_RenderIndex);
		StringBuilder::Trim(rd);
		if (renderIndexMap.find(rd) == renderIndexMap.end())
		{
			return;
		}
		go->SetRenderIndex(renderIndexMap[rd]);
	}

	int selectLayerByName(std::string name);
	void setCameraCullMask(TiXmlElement *objectElement, GameObject *go)
	{
		if (objectElement == nullptr)
		{
			return;
		}
		if (objectElement->Attribute(_Camera_CullMask) == nullptr)
		{
			return;
		}
		std::string cullMask = *objectElement->Attribute(_Camera_CullMask);

		unsigned int layer = 0;
		if (cullMask == _Camera_CullMask_Everything)
		{
			go->SetLayerMask(-1);
		}
		else
		{
			std::vector<std::string> layers = StringBuilder::Split(cullMask, "|");
			for (auto &layerName : layers)
			{
				StringBuilder::Trim(layerName);
				if (layerName == "")
				{
					continue;
				}
				layer |= (1 << selectLayerByName(layerName));
			}
			go->SetLayerMask(layer);
		}
	}

	GameObject* createCamera(TiXmlElement *objectElement)
	{
		Camera *pCamera = Camera::CreateCamera();

		pCamera->SetClearColor(createColor(*objectElement->Attribute(_ClearColor)));
		setCameraCullMask(objectElement, pCamera);
		parseTransform(objectElement->FirstChildElement(_Transform), pCamera->Transform);
		createObjects(pCamera, objectElement);
		return pCamera;
	}

	Renderer * createRenderer(TiXmlElement *objectElement)
	{
		std::string _path = *objectElement->Attribute(_FilePath);
		int _id = Convert::ToInt(*objectElement->Attribute(_SelectID));

		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(sceneFolderPath + "/" + _path, _id);
		Renderer * renderer = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID);
		renderer->SetMaterial(m);
		return renderer;
	}

	GameObject* createSkyBox(TiXmlElement *objectElement)
	{
		Renderer * rd = createRenderer(objectElement->FirstChildElement(_Material));
		SkyBox *skb = new SkyBox();
		skb->Create(50, 50, 50);
		skb->SetRenderer(rd);
		createObjects(skb, objectElement);
		return skb;
	}

	GameObject* createMesh(TiXmlElement *objectElement)
	{
		std::string _path = *objectElement->Attribute(_FilePath);
		int _id = Convert::ToInt(*objectElement->Attribute(_SelectID));

		Mesh *mesh = Mesh::Create(sceneFolderPath + "/" + _path, _id);
		setRenderIndex(objectElement, mesh);
		createObjects(mesh, objectElement);
		return mesh;
	}

	GameObject* createDLight(TiXmlElement *objectElement)
	{
		Light *light = Light::Create(LightType::eDIRECTION_LIGHT);
		Color4 color = createColor(*objectElement->Attribute(_Color));
		light->Color = vec4f(color.r, color.g, color.b, color.a);
		createObjects(light, objectElement);
		return light;
	}

	GameObject *createEmpty(TiXmlElement *objectElement)
	{
		GameObject * go = new GameObject();

		return go;
	}

	GameObject *createCube(TiXmlElement *objectElement)
	{
		Box * box = new Box();
		box->Create(1, 1, 1);
		Renderer * rd = createRenderer(objectElement->FirstChildElement(_Material));

		box->SetRenderer(rd);
		createObjects(box, objectElement);

		return box;
	}

	GameObject *createSphere(TiXmlElement *objectElement)
	{
		Sphere * sphere = new Sphere();
		sphere->Create(1);
		Renderer * rd = createRenderer(objectElement->FirstChildElement(_Material));
		sphere->SetRenderer(rd);
		createObjects(sphere, objectElement);

		return sphere;
	}

	GameObject *createPointLight(TiXmlElement *objectElement)
	{
		Light *light = Light::Create(LightType::ePOINT_LIGHT);
		Color4 color = createColor(*objectElement->Attribute(_Color));
		light->Color = vec4f(color.r, color.g, color.b, color.a);
		if (objectElement->Attribute(_Range) != nullptr)
		{
			static_cast<PointLight*>(light)->Range = Convert::ToFloat(*objectElement->Attribute(_Range));
		}
		createObjects(light, objectElement);

		return light;
	}

	GameObject * createParticle(TiXmlElement *objectElement)
	{
		GameObject * go = new GameObject();
		go->CreateBehaviour();
		std::string _path = *objectElement->Attribute(_FilePath);
		std::vector<ParticleGroup*> *particles = ParticleSystem::GetInstance().ActiveParticle(sceneFolderPath + "/" + _path);
		for (auto & particle : *particles)
		{
			go->AddChild(particle);
		}

		return go;
	}

	int selectLayerByName(std::string name)
	{
		if (name == _Layer_AllLayer)
		{
			return -1;
		}
		TableManager *tbMgr = EngineDelegate::GetInstance().GetTableManager(LAYER_CONFIAG_NAME);
		if (tbMgr == nullptr)
		{
			return 0;
		}
		std::vector< LayerConfig*> *layers = tbMgr->GetTable<LayerConfig>();
		for (auto &layer : *layers)
		{
			if (layer->Name == name)
			{
				return layer->ID;
			}
		}

		SAFE_DELETE(layers);
		return 0;
	}

	void setLayerMask(TiXmlElement *objectElement, GameObject * go)
	{
		if (objectElement == nullptr)
		{
			return;
		}
		if (objectElement->Attribute(_LayerMask) == nullptr)
		{
			return;
		}
		int layer = selectLayerByName(*objectElement->Attribute(_LayerMask));
		go->SetLayerMask(1 << layer);
	}

	void setGameObjectActive(TiXmlElement *objectElement, GameObject * go)
	{
		if (objectElement == nullptr)
		{
			return;
		}
		if (objectElement->Attribute(_Active) == nullptr)
		{
			return;
		}
		string activeStr = *objectElement->Attribute(_Active);
		bool active = Convert::ToBoolean(StringBuilder::Trim(activeStr));
		go->SetActive(active);
	}

	void setObjectCommonValue(GameObject * go, TiXmlElement *objectElement, std::string _type)
	{
		go->Name = *objectElement->Attribute(_Name);
		go->TypeName = _type;
		parseTransform(objectElement->FirstChildElement(_Transform), go->Transform);
		if (_type == TP_Particle)
		{
			go->Transform->SetIsBillBoard(true);
		}
		createComponent(objectElement->FirstChildElement(_Component), go);
		setLayerMask(objectElement, go);
		setGameObjectActive(objectElement, go);
	}

	void createObjects(GameObject * parent, TiXmlElement* rootElem)
	{
		for (TiXmlNode * item = rootElem->FirstChild(); item != nullptr; item = item->NextSibling())
		{
			if (item->Value() != NM_GameObject)
			{
				continue;
			}
			std::string _type = *item->ToElement()->Attribute(_typeName);
			if (createFun.find(_type) == createFun.end())
			{
				continue;
			}
			GameObject *go = createFun[_type](item->ToElement());
			if (go != nullptr)
			{
				setObjectCommonValue(go, item->ToElement(), _type);
				if (parent == nullptr)
				{
					ADD_IN_SCENE(go);
				}
				else
				{
					parent->AddChild(go);
				}
			}
		}
	}

	void RegistScnObjCreateFunc()
	{
		createFun[TP_Camera] = createCamera;
		createFun[TP_DLight] = createDLight;
		createFun[TP_SkyBox] = createSkyBox;
		createFun[TP_Mesh] = createMesh;
		createFun[TP_Particle] = createParticle;
		createFun[TP_Empty] = createEmpty;
		createFun[TP_Cube] = createCube;
		createFun[TP_Sphere] = createSphere;
		createFun[TP_PLight] = createPointLight;

		renderIndexMap[_RenderIndex_LowMost] = eRenderIndex::eRI_LowMost;
		renderIndexMap[_RenderIndex_TopMost] = eRenderIndex::eRI_TopMost;
		renderIndexMap[_RenderIndex_Normal] = eRenderIndex::eRI_Normal;
		renderIndexMap[_RenderIndex_Transparent] = eRenderIndex::eRI_Transparent;
	}

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

	void Scene::Create(std::string filePath)
	{
		TiXmlDocument * doc = new TiXmlDocument(filePath.c_str());
		bool loadOkay = doc->LoadFile();
		if (!loadOkay)
		{
			return;
		}

		sceneFolderPath = GetFolder(filePath);
		TiXmlElement* rootElem = doc->RootElement();
		createObjects(nullptr, rootElem);
		delete doc;
	}

	void Scene::Update(float deltaTime)
	{
        for(auto &node : m_vecObjList)
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
			//for (Camera * camera : m_vecCamera)
			//{
			//	camera->GetRenderQueue()->Remove(static_cast<GameObject*>(it.second));
			//}
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
        for(Camera * camera : m_vecCamera)
		{
			camera->Render(deltaTime);
		}
	}

	void Scene::ChangeRenderIndex(UINT id, eRenderIndex index)
	{
        for(Camera *camera : m_vecCamera)
		{
			camera->GetRenderQueue()->ChangeRenderQueue(id, index);
		}
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

	void Scene::ChangeFrameSize(float w, float h)
	{
        for (auto &camera : m_vecCamera) {
            camera->FrameSizeChange(w / h);
        }
//        for(Camera * camera : m_vecCamera)
//        {
//            camera->FrameSizeChange(w / h);
//        }
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
			}
			rootObject->AddChild(go);
			
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

        for(Camera * camera : m_vecCamera)
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
