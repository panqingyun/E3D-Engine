//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2018-9-29  PanQingyun. All rights reserved. ************************//
#include "E3DSceneLoader.h"
#include "../Source/ClassFactory.h"
#include "../Source/EngineDelegate.h"
#include "../Source/FilePath.h"
#include <mono/metadata/tabledefs.h>
#include "../Config/TableRegister.h"
#include "../Source/E3DVertexManager.h"

namespace E3DEngine
{
	const std::string _Name = "Name";
	const std::string _FilePath = "FilePath";
	const std::string _SelectID = "SelectID";
	const std::string _LayerMask = "LayerMask";
	const std::string _Active = "Active";
	const std::string _Position = "Posistion";
	const std::string _Rotation = "Rotation";
	const std::string _Scale = "Scale";
	const std::string _Transform = "Transform";
	const std::string _Material = "Material";
	const std::string _Particle = "Particle";
	const std::string _ClearColor = "ClearColor";
	const std::string _Color = "Color";
	const std::string _RenderIndex = "RenderIndex";
	const std::string _Component = "Component";
	const std::string _Range = "Range";
	const std::string _InnerID = "ID";
	const std::string _Static = "IsStatic";
	const std::string _Size = "Size";

	const std::string _Layer_AllLayer = "AllLayer";
	const std::string _Component_ClassName = "ClassName";
	const std::string _Component_Field = "Field";
	const std::string _Camera_CullMask = "CullingMask";
	const std::string _Camera_CullMask_Everything = "Everything";

	using createGameObjectFun = GameObject*(*)(TiXmlElement *objectElement);
	using createTiXmlElementFun = void(*)(TiXmlElement *objectElement, GameObject *gameObject);

	std::string sceneFolderPath = "";

	std::map<UINT, createGameObjectFun>	createObjectFun;

	void CreateObjects(GameObject * parent, TiXmlElement* rootElem);

	std::string GetFileFullPath(string path)
	{
		if (path.empty())
		{
			return "";
		}
		if (path[0] == path[1] && path[1] == '.')
		{
			return sceneFolderPath + "/" + path;
		}
		else
		{
			return Application::AppDataPath + path;
		}
	}

	vec3f getVector3(std::string vecStr)
	{
		std::vector<std::string> colorS = StringBuilder::Split(vecStr, ",");
		float &&x = Convert::ToFloat(colorS[0]);
		float &&y = Convert::ToFloat(colorS[1]);
		float &&z = Convert::ToFloat(colorS[2]);

		return vec3f(x, y, z);
	}

	void setComponentFieldValue(TiXmlElement *fieldElement, Component *component)
	{
		if (fieldElement == nullptr)
		{
			return;
		}
		MonoClass *klass = component->GetMonoBehaviour()->GetClass();
		for (TiXmlAttribute * attribute = fieldElement->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
		{
			const char* fieldName = attribute->Name();
			const char* valueStr = attribute->Value();
			component->SetFieldValue(fieldName, valueStr);
		}

		setComponentFieldValue(fieldElement->NextSiblingElement(), component);
	}

	void createComponent(TiXmlElement *objectElement, GameObject *go)
	{
		if (objectElement == nullptr)
		{
			return;
		}

		std::string comName = *objectElement->Attribute(_Component_ClassName);
		bool &&active = Convert::ToBoolean(*objectElement->Attribute(_Active));
		Component * component = go->AddComponent(comName.c_str());
		component->IsActive = active;
		setComponentFieldValue(objectElement->FirstChildElement(_Component_Field), component);
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			component->OnCreate();
		}
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
		transform->Update();
	}

	void setRenderIndex(TiXmlElement *objectElement, GameObject * go)
	{
		if (objectElement->Attribute(_RenderIndex) == nullptr)
		{
			return;
		}
		std::string rd = *objectElement->Attribute(_RenderIndex);
		StringBuilder::Trim(rd);
		go->SetRenderIndex(Convert::ToInt(rd));
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
		std::string layerStr = *objectElement->Attribute(_LayerMask);
		if (layerStr == _Layer_AllLayer)
		{
			go->SetLayerMask(-1);
		}
		else
		{
			std::vector<std::string> layers = StringBuilder::Split(layerStr, "|");
			int layer = 0;
			for (int i = 0; i < layers.size(); i++)
			{
				if (StringBuilder::Trim(layers[i]) == "")
					return;
				layer |= (1 << Convert::ToInt(layers[i]));
			}
			go->SetLayerMask(layer);
		}
	}

	GameObject* createCamera(TiXmlElement *objectElement)
	{
		Camera *pCamera = Camera::CreateCamera();

		SceneManager::GetCurrentScene()->AddCamera(pCamera);
		pCamera->SetClearColor(Convert::ToColor4(*objectElement->Attribute(_ClearColor)));
		setLayerMask(objectElement, pCamera);
		parseTransform(objectElement->FirstChildElement(_Transform), pCamera->Transform);

		return pCamera;
	}

	Renderer * createRenderer(TiXmlElement *objectElement, int vertxSize, bool isStaticObject, DWORD renderType = NORMAL)
	{
		std::string _path = *objectElement->Attribute(_FilePath);
		int _id = Convert::ToInt(*objectElement->Attribute(_SelectID));

		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(GetFileFullPath(_path), _id);
		m->mConfigPath = _path;
		m->mConfigID = _id;
		Renderer * renderer = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID, vertxSize,(RENDER_TYPE)renderType, isStaticObject);
		return renderer;
	}

	GameObject* createSkyBox(TiXmlElement *objectElement)
	{
		SkyBox *skb = new SkyBox();
		skb->Create(50, 50, 50);

		return skb;
	}

	GameObject* createMesh(TiXmlElement *objectElement)
	{
		std::string _path = *objectElement->Attribute(_FilePath);

		Mesh *mesh = new Mesh(_path);	
		mesh->mConfigPath = _path;

		return mesh;
	}

	GameObject* createDLight(TiXmlElement *objectElement)
	{
		Light *light = Light::Create(LightType::eDIRECTION_LIGHT);
		
		light->Color = Convert::ToColor4(*objectElement->Attribute(_Color));

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

		return box;
	}

	GameObject *createSphere(TiXmlElement *objectElement)
	{
		Sphere * sphere = new Sphere();
		sphere->Create(1);
		return sphere;
	}

	GameObject *createTerrain(TiXmlElement *objectElement)
	{
		Terrain * terrain = new Terrain;
		int size = Convert::ToInt(*objectElement->Attribute(_Size));
		terrain->Create(size);
		return terrain;
	}

	GameObject *createPointLight(TiXmlElement *objectElement)
	{
		Light *light = Light::Create(LightType::ePOINT_LIGHT);
		light->Color = Convert::ToColor4(*objectElement->Attribute(_Color));
		if (objectElement->Attribute(_Range) != nullptr)
		{
			static_cast<PointLight*>(light)->Range = Convert::ToFloat(*objectElement->Attribute(_Range));
		}

		return light;
	}

	GameObject *createPrefab(TiXmlElement *objectElement)
	{
		std::string filePath = (*objectElement->Attribute(_FilePath));
		filePath = GetFileFullPath(filePath);
		return LoadPrefab(filePath);
	}

	E3D_EXPORT_DLL GameObject * LoadPrefab(std::string filePath)
	{
		Prefab *prefab = new Prefab();
		prefab->SetActive(true);
		prefab->SetFilePath(filePath);
		TiXmlDocument * doc = new TiXmlDocument(filePath.c_str());
		bool loadOkay = doc->LoadFile();
		if (!loadOkay)
		{
			return prefab;
		}
		std::string folderPath = sceneFolderPath;
		sceneFolderPath = GetFolder(filePath);

		TiXmlElement* rootElem = doc->RootElement();
		CreateObjects(prefab, rootElem);
		sceneFolderPath = folderPath;
		return prefab;
	}

	GameObject * createParticle(TiXmlElement *objectElement)
	{
		GameObject * go = new GameObject();
		go->CreateBehaviour();
		std::string _path = *objectElement->Attribute(_FilePath);
		go->mConfigPath = _path;
		std::vector<ParticleGroup*> *particles = ParticleSystem::GetInstance().ActiveParticle(GetFileFullPath( _path));
		for (auto & particle : *particles)
		{
			particle->mName = _ParticleGroupName;
			go->AddChild(particle);
		}

		return go;
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

	void setObjectCommonValue(GameObject * go, TiXmlElement *objectElement,unsigned int _type)
	{
		go->mName = *objectElement->Attribute(_Name);
		go->mSceneObjectType = _type;
		go->IsActive = true;
		parseTransform(objectElement->FirstChildElement(_Transform), go->Transform);
		go->IsActive = false;
		if (_type == TP_Particle)
		{
			go->Transform->SetIsBillBoard(true);
		}
		createComponent(objectElement->FirstChildElement(_Component), go);
		setLayerMask(objectElement, go);
		if (objectElement->Attribute(_Color) != nullptr)
		{
			go->SetColor(Convert::ToColor4(*objectElement->Attribute(_Color)));
		}
		if (objectElement->Attribute(_InnerID) != nullptr)
		{
			go->SceneInnerID = Convert::ToInt(*objectElement->Attribute(_InnerID));
		}
		for (auto & component : go->GetAllComponents())
		{
			if (!EngineDelegate::GetInstance().GetIsRun())
			{
				continue;
			}
			component.second->OnCreateComplete();
		}
		setGameObjectActive(objectElement, go);
		if (objectElement->FirstChildElement(_Material) != nullptr)
		{
			DWORD type = go->mSceneObjectType == TP_Mesh ? MESH : NORMAL;
			Renderer * rd = createRenderer(objectElement->FirstChildElement(_Material), VertexManager::GetVertex(go->VertexBufferName).size(), go->GetIsStatic(), type);
			go->SetRenderer(rd);
		}
	}

	E3D_EXPORT_DLL void LoadSceneObjects(string sceneFilePath)
	{
		TiXmlDocument * doc = new TiXmlDocument(sceneFilePath.c_str());
		bool loadOkay = doc->LoadFile();
		if (!loadOkay)
		{
			return;
		}
		sceneFolderPath = GetFolder(sceneFilePath);

		TiXmlElement* rootElem = doc->RootElement();
		CreateObjects(nullptr, rootElem);
		delete doc;

	}

	void CreateObjects(GameObject * parent, TiXmlElement* rootElem)
	{
		for (TiXmlNode * item = rootElem->FirstChild(); item != nullptr; item = item->NextSibling())
		{
			if (item->Value() != NM_GameObject)
			{
				continue;
			}
			unsigned int &&_type = Convert::ToInt(*item->ToElement()->Attribute(_TypeName));
			 
			if (createObjectFun.find(_type) == createObjectFun.end())
			{
				continue;
			}
			bool isStatic = false;
			if (item->ToElement()->Attribute(_Static) != nullptr)
			{
				isStatic = Convert::ToBoolean(*item->ToElement()->Attribute(_Static));
			}
			GameObject *go = createObjectFun[_type](item->ToElement());
			if (go != nullptr)
			{
				go->SetIsStatic(isStatic);
				if (parent == nullptr)
				{
					ADD_IN_SCENE(go);
				}
				else
				{
					parent->AddChild(go);
				}
				setObjectCommonValue(go, item->ToElement(), _type);
				CreateObjects(go, item->ToElement());
				go->CreateComplete();
			}
		}
	}

	std::string getLayerMaskElement(int layerMask)
	{
		if (layerMask == -1)
		{
			return _Layer_AllLayer;
		}
		std::string retLayeStr = "";
		TableManager *tbMgr = TableRegister::GetTableManager((LAYER_CONFIAG_NAME).c_str());
		if (tbMgr == nullptr)
		{
			return _Layer_AllLayer;
		}
		std::vector< LayerConfig*> *layers = tbMgr->GetTable<LayerConfig>();
		for (auto &layer : *layers)
		{
			if ((1 << layer->ID) & layerMask)
			{
				if (retLayeStr == "")
				{
					retLayeStr = Convert::ToString(layer->ID);
				}
				else
				{
					retLayeStr = retLayeStr + "|" + Convert::ToString(layer->ID);
				}
			}
		}

		SAFE_DELETE(layers);
		return retLayeStr;
	}

	void exportComponent(TiXmlElement *objectElement, std::string className,Component *component)
	{
		TiXmlElement *componentElement = new TiXmlElement(_Component);
		componentElement->SetAttribute(_Active, component->IsActive ? "true" : "false");
		componentElement->SetAttribute(_Component_ClassName, className);
		std::map<std::string, DWORD> &fieldMap = component->m_propertyTypeMap;
		objectElement->LinkEndChild(componentElement);
		if (fieldMap.empty())
		{
			return;
		}
		TiXmlElement *fieldElement = new TiXmlElement(_Component_Field);
		for (auto fieldPair : fieldMap)
		{
			fieldElement->SetAttribute(fieldPair.first, component->GetFieldValueStr(fieldPair.first));
		}

		componentElement->LinkEndChild(fieldElement);		
	}

	void exportOuterComponent(TiXmlElement *objectElement, std::string className, Component *component)
	{
		TiXmlElement *componentElement = new TiXmlElement(_Component);
		componentElement->SetAttribute(_Component_ClassName, className);
		TiXmlElement *fieldElement = new TiXmlElement(_Component_Field);

		for (auto &field : component->m_propertyTypeMap)
		{
			fieldElement->SetAttribute(field.first, component->GetFieldValueStr(field.first));
		}

		componentElement->LinkEndChild(fieldElement);
		objectElement->LinkEndChild(componentElement);
		
	}

	void saveComponentElement(TiXmlElement *objectElement, GameObject *gameObject)
	{
		std::map<std::string, Component*> &componentsMap = gameObject->GetAllComponents();

		for (auto componentPair : componentsMap)
		{
			std::string componentName = componentPair.first;
			exportComponent(objectElement, componentName, componentPair.second);
		}
	}

	void saveMaterialElement(TiXmlElement *objectElement, Material *material)
	{
		TiXmlElement *materialElement = new TiXmlElement(_Material);
		materialElement->SetAttribute(_FilePath, material->mConfigPath);
		materialElement->SetAttribute(_SelectID, material->mConfigID);

		objectElement->LinkEndChild(materialElement);
	}

	void saveTransformElement(TiXmlElement *objectElement, CTransform *transform)
	{
		TiXmlElement *transformElement = new TiXmlElement(_Transform);
		transformElement->SetAttribute(_Position, Convert::ToString(transform->Position));
		transformElement->SetAttribute(_Rotation, Convert::ToString(transform->RotationEuler));
		transformElement->SetAttribute(_Scale, Convert::ToString(transform->Scale));
		objectElement->LinkEndChild(transformElement);
	}

	void saveGameObjectElement(TiXmlElement *objectElement, GameObject *gameObject)
	{
		objectElement->SetAttribute(_InnerID, gameObject->SceneInnerID);
		objectElement->SetAttribute(_Name, gameObject->mName);
		objectElement->SetAttribute(_TypeName, gameObject->mSceneObjectType);
		objectElement->SetAttribute(_LayerMask, getLayerMaskElement(gameObject->GetLayerMask()));
		objectElement->SetAttribute(_Active, Convert::ToString(gameObject->IsActive));
		if (gameObject->GetRenderer() != nullptr)
		{
			objectElement->SetAttribute(_RenderIndex, gameObject->GetRenderer()->RenderIndex);
			saveMaterialElement(objectElement, gameObject->GetRenderer()->GetMaterial());
		}	
		if (gameObject->mSceneObjectType == TP_Particle || gameObject->mSceneObjectType == TP_Mesh)
		{
			objectElement->SetAttribute(_FilePath, gameObject->mConfigPath);
		}
		else if (gameObject->mSceneObjectType == TP_Camera)
		{
			Camera *pCamera = (Camera*)gameObject;
			objectElement->SetAttribute(_ClearColor, Convert::ToString(pCamera->GetClearColor()));
		}
		else if (gameObject->mSceneObjectType == TP_Terrain)
		{
			Terrain *terrain = (Terrain*)gameObject;
			objectElement->SetAttribute(_Size, terrain->GetSize());
		}
		objectElement->SetAttribute(_Color, Convert::ToString(gameObject->Color));
		saveTransformElement(objectElement, gameObject->Transform);
		saveComponentElement(objectElement, gameObject);
		for (auto gameObj : gameObject->GetChilds())
		{
			GameObject *childObject = gameObj.second;
			if (gameObject->mSceneObjectType == TP_Particle && childObject->mName == _ParticleGroupName)
			{ // Particle Group 不能保存
				continue;
			}
			TiXmlElement *childElement = new TiXmlElement(NM_GameObject);
			saveGameObjectElement(childElement, childObject);
			objectElement->LinkEndChild(childElement);
		}
	}

	E3D_EXPORT_DLL void SavePrefab(Prefab *prefab)
	{
		std::map<UINT, GameObject*> &objects = prefab->GetChilds();

		TiXmlDocument *doc = new TiXmlDocument();
		TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		doc->LinkEndChild(decl);
		TiXmlElement *rootElement = new TiXmlElement("Prefab");
		doc->LinkEndChild(rootElement);

		for (auto gameObj : objects)
		{
			if (gameObj.second->Flag & DONT_SAVE)
			{
				continue;
			}
			TiXmlElement *childElement = new TiXmlElement(NM_GameObject);
			GameObject *childObject = gameObj.second;
			saveGameObjectElement(childElement, childObject);
			rootElement->LinkEndChild(childElement);
		}

		doc->SaveFile(prefab->GetFilePath());
		delete doc;
	}

	E3D_EXPORT_DLL void SaveCurrentScene()
	{
		Scene *pScene = SceneManager::GetInstance().GetCurrentScene();

		// 保存rootObject的子集
		std::map<UINT, GameObject*> &objects = pScene->GetRootObject()->GetChilds();

		TiXmlDocument *doc = new TiXmlDocument();
		TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		doc->LinkEndChild(decl);
		TiXmlElement *rootElement = new TiXmlElement("Scene");
		doc->LinkEndChild(rootElement);

		for (auto gameObj : objects)
		{
			if (gameObj.second->Flag & DONT_SAVE)
			{
				continue;
			}
			TiXmlElement *childElement = new TiXmlElement(NM_GameObject);
			GameObject *childObject = gameObj.second;
			saveGameObjectElement(childElement, childObject);
			rootElement->LinkEndChild(childElement);
		}

		doc->SaveFile(pScene->GetScenePath());
		delete doc;
	}

	void RegistScnObjCreateFunc()
	{
		createObjectFun[TP_Camera] = createCamera;
		createObjectFun[TP_DLight] = createDLight;
		createObjectFun[TP_SkyBox] = createSkyBox;
		createObjectFun[TP_Mesh] = createMesh;
		createObjectFun[TP_Particle] = createParticle;
		createObjectFun[TP_Empty] = createEmpty;
		createObjectFun[TP_Cube] = createCube;
		createObjectFun[TP_Sphere] = createSphere;
		createObjectFun[TP_PLight] = createPointLight;
		createObjectFun[TP_Prefab] = createPrefab;
		createObjectFun[TP_Terrain] = createTerrain;
	}

}