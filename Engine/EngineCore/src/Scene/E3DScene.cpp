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

namespace E3DEngine
{	
	const std::string NM_GameObject = "GameObject";
	const std::string TP_Camera		= "Camera";
	const std::string TP_DLight		= "DirectionLight";
	const std::string TP_PLight		= "PointLight";
	const std::string TP_SkyBox		= "SkyBox";
	const std::string TP_Mesh		= "Mesh";
	const std::string TP_Particle	= "Particle";
	const std::string TP_Cube		= "Cube";
	const std::string TP_Sphere		= "Sphere";
	const std::string TP_Empty		= "Empty";
	const std::string _typeName		= "Type";
	const std::string TP_Terrain	= "Terrain";

	const std::string _Name			= "Name";
	const std::string _FilePath		= "FilePath";
	const std::string _SelectID		= "SelectID";
	const std::string _LayerMask	= "LayerMask";
	const std::string _Active		= "Active";
	const std::string _Position		= "Posistion";
	const std::string _Rotation		= "Rotation";
	const std::string _Scale		= "Scale";
	const std::string _Transform	= "Transform";
	const std::string _Material		= "Material";
	const std::string _Particle		= "Particle";
	const std::string _ClearColor	= "ClearColor";
	const std::string _Color		= "Color";
	const std::string _RenderIndex	= "RenderIndex";
	const std::string _Component	= "Component";
	const std::string _Range		= "Range";

	const std::string _Layer_AllLayer				= "AllLayer";
	const std::string _RenderIndex_Transparent		= "Transparent";
	const std::string _RenderIndex_Normal			= "Normal";
	const std::string _RenderIndex_LowMost			= "LowMost";
	const std::string _RenderIndex_TopMost			= "TopMost";
	const std::string _Component_ClassName			= "ClassName";
	const std::string _Component_Property			= "Property";
	const std::string _Camera_CullMask				= "CullingMask";
	const std::string _Camera_CullMask_Everything	= "Everything";

	using createGameObjectFun	= GameObject*(*)(TiXmlElement *objectElement);
	std::string sceneFolderPath = "";

	std::map<std::string, createGameObjectFun>	createFun;
	std::map<std::string, UINT>					renderIndexMap;

	void createObjects(GameObject * parent, TiXmlElement* rootElem);

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

	void setComponentPropertyValue(TiXmlElement *objectElement, Component *component)
	{
		const std::string *_property = objectElement->Attribute(_Component_Property);
		if (_property == nullptr)
		{
			return;
		}
		MonoString *arg = mono_string_new(MonoScriptManager::GetInstance().GetEngineDomain(), _property->c_str());
		component->SetPropertyValue((void*)arg);
	}

	void createComponent(TiXmlElement *objectElement, GameObject *go)
	{
		if (objectElement == nullptr)
		{
			return;
		}

		std::string comName = *objectElement->Attribute(_Component_ClassName);
		Component * component = go->AddComponent(comName.c_str());
		setComponentPropertyValue(objectElement, component);
		component->OnCreate();
		component->OnCreateComplete();
		createComponent(objectElement->NextSiblingElement(_Component), go);
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
		TableManager *tbMgr = TableRegister::GetTableManager((LAYER_CONFIAG_NAME).c_str());
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
		go->mName = *objectElement->Attribute(_Name);
		go->mTypeName = _type;
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
		createFun[TP_Camera]	= createCamera;
		createFun[TP_DLight]	= createDLight;
		createFun[TP_SkyBox]	= createSkyBox;
		createFun[TP_Mesh]		= createMesh;
		createFun[TP_Particle]	= createParticle;
		createFun[TP_Empty]		= createEmpty;
		createFun[TP_Cube]		= createCube;
		createFun[TP_Sphere]	= createSphere;
		createFun[TP_PLight]	= createPointLight;

		renderIndexMap[_RenderIndex_LowMost]		= eRenderIndex::eRI_LowMost;
		renderIndexMap[_RenderIndex_TopMost]		= eRenderIndex::eRI_TopMost;
		renderIndexMap[_RenderIndex_Normal]			= eRenderIndex::eRI_Normal;
		renderIndexMap[_RenderIndex_Transparent]	= eRenderIndex::eRI_Transparent;
	}

	Scene::Scene()
	{
		m_nObjectID			= 0;
		mType				= eT_Scene;
		rootObject			= new GameObject;
		usedDirectionLight	= nullptr;

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
		mName = GetFileName(filePath);
		TiXmlElement* rootElem = doc->RootElement();
		createObjects(nullptr, rootElem);
		delete doc;
	}

	void Scene::Update(float deltaTime)
	{
		// 运行时执行，编辑器下不执行
		if (!EngineDelegate::GetInstance().GetIsEditor())
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
		if (!EngineDelegate::GetInstance().GetIsEditor())
		{
			for (auto &node : m_vecObjList)
			{
				if (node.second->mType == eT_GameObject)
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
		SAFE_DELETE(rootObject);
		GetRenderSystem()->Cleanup();
		m_mapRenders.clear();
		m_vecObjList.clear();
		m_mapLights.clear();
		m_vecCamera.clear();
		TableRegister::Destory();
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
#ifdef __E3D_EDITOR__
		GetEditorCamera()->Render(deltaTime);
#else
        for(Camera * camera : m_vecCamera)
		{
			if (camera->IsActive)
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

	void Scene::ChangeViewportSize(float w, float h)
	{
        for (auto &camera : m_vecCamera) 
		{
            camera->ChangeViewport(w / h);
        }
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
		if (obj->mType == eT_GameObject || obj->mType == eT_Camera)
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
}
