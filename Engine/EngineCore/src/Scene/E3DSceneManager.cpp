//
//  E3DSceneManager.cpp
//
//  Created by 潘庆云 on 2017/8/11.
//

#include "E3DSceneManager.hpp"
#include "../Source/EngineDelegate.h"
#include "../Object/E3DObject.h"

namespace E3DEngine
{
	const std::string NM_GameObject = "GameObject";
	const std::string TP_Camera = "Camera";
	const std::string TP_DLight = "DirectionLight";
	const std::string TP_SkyBox = "SkyBox";
	const std::string TP_Mesh = "Mesh";
	const std::string TP_Particle = "Particle";
	const std::string TP_Cube = "Cube";
	const std::string TP_Sphere = "Sphere";
	const std::string TP_Empty = "Empty";
	const string _typeName = "Type";

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

	const string _Camera_CullMask = "CulMask";
	const string _Camera_CullMask_Everything = "Everything";

	using createGameObjectFun = GameObject*(*)(GameObject *parent,TiXmlElement *objectElement);
	std::map<std::string, createGameObjectFun> createFun;
	std::map<std::string, UINT> renderIndexMap;
	void createObjects(GameObject * parent, TiXmlElement* rootElem);
	std::string sceneFolderPath = "";

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

	void descTransform(TiXmlElement *objectElement, CTransform * transform)
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
		rd = StringBuilder::Trim(rd);
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
				layer  |= (1 << selectLayerByName(layerName));
			}
			go->SetLayerMask(layer);
		}
	}

	GameObject* createCamera(GameObject *parent, TiXmlElement *objectElement)
	{
		Camera *pCamera = Camera::CreateCamera();

		pCamera->SetClearColor(createColor(*objectElement->Attribute(_ClearColor)));
		descTransform(objectElement->FirstChildElement(_Transform), pCamera->Transform);
		createObjects(pCamera, objectElement);
		return pCamera;
	}

	Material * createMaterial(TiXmlElement *objectElement)
	{
		std::string _path = *objectElement->Attribute(_FilePath);
		int _id = Convert::ToInt(*objectElement->Attribute(_SelectID));

		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(sceneFolderPath + "/" + _path, _id);
		return m;
	}

	GameObject* createSkyBox(GameObject *parent, TiXmlElement *objectElement)
	{		
		Material * m = createMaterial(objectElement->FirstChildElement(_Material));
		SkyBox *skb = GameObject::CreateSkyBox(m);
		createObjects(skb, objectElement);
		return skb;
	}

	GameObject* createMesh(GameObject *parent, TiXmlElement *objectElement)
	{
		std::string _path = *objectElement->Attribute(_FilePath);
		int _id = Convert::ToInt(*objectElement->Attribute(_SelectID));

		Mesh *mesh = Mesh::Create(sceneFolderPath + "/" + _path, _id);
		setRenderIndex(objectElement, mesh);
		createObjects(mesh, objectElement);
		return mesh;
	}

	GameObject* createDLight(GameObject *parent, TiXmlElement *objectElement)
	{
		Light *light = Light::Create(LightType::eDIRECTION_LIGHT);
		Color4 color = createColor(*objectElement->Attribute(_Color));
		light->Color = vec4f(color.r, color.g, color.b, color.a);
		createObjects(light, objectElement);
		return light;
	}

	GameObject *createEmpty(GameObject *parent, TiXmlElement *objectElement)
	{
		GameObject * go = new GameObject();

		return go;
	}

	GameObject * createParticle(GameObject *parent, TiXmlElement *objectElement)
	{
		std::string _path = *objectElement->Attribute(_FilePath);
		std::vector<ParticleGroup*> *particles = ParticleSystem::GetInstance().ActiveParticle(sceneFolderPath + "/" + _path);

		for (auto & particle: *particles)
		{
			descTransform(objectElement->FirstChildElement(_Transform), particle->Transform);
			if (parent != nullptr)
			{
				parent->AddChild(particle);
			}
			else
			{
				ADD_IN_SCENE(particle);
				setRenderIndex(objectElement, particle);
			}
		}
		
		return nullptr;
	}

	SceneManager::SceneManager()
	{
		m_currentUseSceneID = NULL_SCENE;
		m_lastSceneID = NULL_SCENE;
		createFun[TP_Camera] = createCamera;
		createFun[TP_DLight] = createDLight;
		createFun[TP_SkyBox] = createSkyBox;
		createFun[TP_Mesh] = createMesh;
		createFun[TP_Particle] = createParticle;
		createFun[TP_Empty] = createEmpty;

		renderIndexMap[_RenderIndex_LowMost] = eRenderIndex::eRI_LowMost;
		renderIndexMap[_RenderIndex_TopMost] = eRenderIndex::eRI_TopMost;
		renderIndexMap[_RenderIndex_Normal] = eRenderIndex::eRI_Normal;
		renderIndexMap[_RenderIndex_Transparent] = eRenderIndex::eRI_Transparent;
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

	void setLayerMask(TiXmlElement *objectElement,GameObject * go)
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
		descTransform(objectElement->FirstChildElement(_Transform), go->Transform);
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
			GameObject *go = createFun[_type](parent,item->ToElement());			
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

	E3DEngine::Scene * SceneManager::CreateScene(std::string filePath)
	{
		Scene * pScene = new Scene;
		m_mapScenes[pScene->ID] = pScene;

		ChangeScene(pScene->ID);
		TiXmlDocument * doc = new TiXmlDocument(filePath.c_str());
		bool loadOkay = doc->LoadFile();
		if (!loadOkay)
		{
			return nullptr;
		}
		TiXmlElement* rootElem = doc->RootElement();
		sceneFolderPath = vvision::GetFolder(filePath);
		createObjects(nullptr, rootElem);
		delete doc;
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
