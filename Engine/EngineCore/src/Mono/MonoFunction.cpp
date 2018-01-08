#include "MonoFunction.h"
#include "../Source/EngineDelegate.h"

void RegisterMonoFunction()
{
	REGISTER_INTERNAL_CALL(Object,		get_ID);
	REGISTER_INTERNAL_CALL(Transform,	getPosition);
	REGISTER_INTERNAL_CALL(Transform,	setPosition);
	REGISTER_INTERNAL_CALL(Transform,	getScale);
	REGISTER_INTERNAL_CALL(Transform,	setScale);
	REGISTER_INTERNAL_CALL(Transform,	getRotation);
	REGISTER_INTERNAL_CALL(Transform,	setRotation);
	REGISTER_INTERNAL_CALL(GameObject,	set_LayerMask);
	REGISTER_INTERNAL_CALL(GameObject,	get_LayerMask);
	REGISTER_INTERNAL_CALL(GameObject,	set_Material);
	REGISTER_INTERNAL_CALL(GameObject,	get_Material);
	REGISTER_INTERNAL_CALL(GameObject,	set_Active);
	REGISTER_INTERNAL_CALL(GameObject,	get_Active);
	REGISTER_INTERNAL_CALL(GameObject,	addComponent);
	REGISTER_INTERNAL_CALL(Camera,		setClearColor);
	REGISTER_INTERNAL_CALL(Camera,		renderCamera);
	REGISTER_INTERNAL_CALL(Camera,		createCamera);
	REGISTER_INTERNAL_CALL(Debug,		log_error);
	REGISTER_INTERNAL_CALL(Debug,		log_warning);
	REGISTER_INTERNAL_CALL(Debug,		log_info);
	REGISTER_INTERNAL_CALL(Scene,		createScene);
	REGISTER_INTERNAL_CALL(Scene,		changeScene);
	REGISTER_INTERNAL_CALL(Scene,		destoryScene);
	REGISTER_INTERNAL_CALL(Render,		createRenderer);
	REGISTER_INTERNAL_CALL(Render,		createRendererWithoutParam);
	REGISTER_INTERNAL_CALL(Render,		setVertex2Render);
	REGISTER_INTERNAL_CALL(Material,	createMaterial);
	REGISTER_INTERNAL_CALL(Box,			createBox);
	REGISTER_INTERNAL_CALL(RigidBody,	addRigidBody);
}

inline void * getCppObject(CS_OBJECT obj)
{
	if (obj == nullptr)
	{
		return nullptr;
	}
	MonoClass *klass = mono_object_get_class(obj);
	MonoClassField *  field = mono_class_get_field_from_name(klass, CPP_OBJ_PTR_NAME);

	if (field == nullptr)
	{
		return nullptr;
	}
	void * value = nullptr;
	mono_field_get_value(obj, field, &value);
	return value;
}

VOID _1_PARAM_FUNCTION(Camera, renderCamera, CS_OBJECT, cs_obj)
{
	Camera * camera = static_cast<Camera*>(getCppObject(cs_obj));
	if (camera == nullptr)
	{
		return;
	}
	camera->Render(0.2f);
}

VOID _4_PARAM_FUNCTION(Transform, getPosition, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform* transform = static_cast<CTransform*>(getCppObject(obj));
	if (transform == nullptr)
	{
		return;
	}
	x = transform->Position.x;
	y = transform->Position.y;
	z = transform->Position.z;
}

VOID _4_PARAM_FUNCTION(Transform, setPosition, CS_OBJECT, obj, float, x, float, y, float, z)
{
	CTransform* transform = static_cast<CTransform*>(getCppObject(obj));
	if (transform == nullptr)
	{
		return;
	}
	transform->SetPosition(x, y, z);
}

VOID _4_PARAM_FUNCTION(Transform, getScale, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform* transform = static_cast<CTransform*>(getCppObject(obj));
	if (transform == nullptr)
	{
		return;
	}

	x = transform->Scale.x;
	y = transform->Scale.y;
	z = transform->Scale.z;
}

VOID _4_PARAM_FUNCTION(Transform, setScale, CS_OBJECT, obj, float, x, float, y, float, z)
{
	CTransform* transform = static_cast<CTransform*>(getCppObject(obj));
	if (transform == nullptr)
	{
		return;
	}

	transform->SetScale(x, y, z);
}

VOID _4_PARAM_FUNCTION(Transform, getRotation, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform* transform = static_cast<CTransform*>(getCppObject(obj));
	if (transform == nullptr)
	{
		return;
	}
	vec3f rotation = transform->Rotation.toEulerAngles();
	x = rotation.x;
	y = rotation.y;
	z = rotation.z;
}

VOID _4_PARAM_FUNCTION(Transform, setRotation, CS_OBJECT, obj, float, x, float, y, float, z)
{
	CTransform* transform = static_cast<CTransform*>(getCppObject(obj));
	if (transform == nullptr)
	{
		return;
	}
	transform->SetRotation(x, y, z);
}

VOID _1_PARAM_FUNCTION(Debug, log_error, CS_STRING, err)
{
	std::string _log = Convert::ToString(err);
	E3DEngine::Debug::Log(ell_Error, _log.c_str());
}

VOID _1_PARAM_FUNCTION(Debug, log_warning, CS_STRING, warning)
{
	std::string _log = Convert::ToString(warning);
	E3DEngine::Debug::Log(ell_Warning, _log.c_str());
}

VOID _1_PARAM_FUNCTION(Debug, log_info, CS_STRING, info)
{
	std::string _log = Convert::ToString(info);
	E3DEngine::Debug::Log(ell_Info, _log.c_str());
}

CS_OBJECT _1_PARAM_FUNCTION(Camera, createCamera, CS_STRING, name)
{
	std::string stdName = Convert::ToString(name);
	const float32 fov = 60.0f;
	const vec3f up = vec3f(0.0f, 1.0f, 0.0);
	const float32 zNear = 1.0f;
	const float32 zFar = 1000.0f;
	Vector2 frameSize = GetRenderSystem()->GetFrameSize();
	const float32 aspect = frameSize.x / frameSize.y;
	const vec3f position = vec3f(0, 0, 200);
	const vec3f target = vec3f(0, 0, -1);
	E3DEngine::Camera *camera = new E3DEngine::Camera(position, target, fov, up, zNear, zFar, aspect);
	return camera->GetMonoBehaviour()->GetMonoObject();
}

VOID _5_PARAM_FUNCTION(Camera, setClearColor, CS_OBJECT, cs_boj, float, r, float, g, float, b, float, a)
{
	Camera * camera = static_cast<Camera*>(getCppObject(cs_boj));
	if (camera == nullptr)
	{
		return;
	}

	camera->SetClearColor(Color4(r, g, b, a));
}

CS_OBJECT _0_PARAM_FUNCTION(Scene, createScene)
{
	Scene * scene = SceneManager::GetInstance().CreateScene();

	return scene->GetMonoBehaviour()->GetMonoObject();
}

VOID _1_PARAM_FUNCTION(Scene, changeScene, UINT, sceneId)
{
	Scene * scene = SceneManager::GetInstance().GetScene(sceneId);
	if (scene == nullptr)
	{
		Debug::Log(ell_Error, "change scene is null");
		return;
	}
	EngineDelegate::GetInstance().ChangeScene(sceneId);
}

VOID _1_PARAM_FUNCTION(Scene, destoryScene, UINT, sceneId)
{
	Scene * scene = SceneManager::GetInstance().GetScene(sceneId);
	if (scene == nullptr)
	{
		return;
	}
	SceneManager::GetInstance().DestoryScene(scene);
}

VOID _2_PARAM_FUNCTION(RigidBody, addRigidBody, CS_OBJECT, rigibody, CS_OBJECT, _collider)
{
	Collider * collider = static_cast<Collider*>(getCppObject(_collider));

	if (collider == nullptr || rigibody == nullptr)
	{
		return;
	}
	MonoClass *klass = mono_object_get_class(rigibody);

	MonoClassField *mField = mono_class_get_field_from_name(klass, "mass");

	float value = 0;
	mono_field_get_value(rigibody, mField, &value);

	btRigidBody *body = collider->CreateRigidBody(value);
	mField = mono_class_get_field_from_name(klass, CPP_OBJ_PTR_NAME);
	if (mField != nullptr)
	{
		mono_field_set_value(rigibody, mField, body);
	}
}

CS_OBJECT _1_PARAM_FUNCTION(Render, createRenderer, UINT, materialID)
{
	Renderer * render = GetRenderSystem()->GetRenderManager()->GetRenderer(materialID);

	return render->GetMonoBehaviour()->GetMonoObject();
}

VOID _1_PARAM_FUNCTION(Render, setVertex2Render, CPP_OBJECT, obj)
{
	
}

CS_OBJECT _0_PARAM_FUNCTION(Render, createRendererWithoutParam)
{
	Renderer * render = new Renderer();

	return render->GetMonoBehaviour()->GetMonoObject();
}

CS_OBJECT _1_PARAM_FUNCTION(Material, createMaterial, CS_STRING, path)
{
	std::string m_Path = Convert::ToString(path);

	E3DEngine::Material * material = GetRenderSystem()->GetMaterialManager()->CreateMaterial(m_Path);
	return material->GetBehaviour()->GetMonoObject();
}

CS_OBJECT _3_PARAM_FUNCTION(Box, createBox, float, l, float, w, float, h)
{
	Box *box = new Box;
	ADD_IN_SCENE(box);
	box->Create(l, w, h);

	return box->GetMonoBehaviour()->GetMonoObject();
}


CS_OBJECT _2_PARAM_FUNCTION(GameObject, addComponent, CS_OBJECT, obj, CS_STRING, class_name)
{
	GameObject *go = static_cast<GameObject*>(getCppObject(obj));

	if (go == nullptr)
	{
		return nullptr;
	}

	std::string cName = Convert::ToString(class_name);
	std::string sName = "";
	std::vector<std::string> nameSpaceClassName = StringBuilder::Split(cName, ".");

	Component * component = nullptr;
	if (nameSpaceClassName.size() == 0)
	{
		return nullptr;
	}
	else if (nameSpaceClassName.size() == 2)
	{
		cName = nameSpaceClassName[1];
		sName = nameSpaceClassName[0];
	}
	string kName = ClassFactory::GetInstance().getTypeNameByClassName(cName);
	if (kName != "NAN")
	{
		component = go->AddComponent(kName.c_str());
	}
	else
	{
		// 不是引擎类
		component = go->AddComponent<Component>();
		component->m_pBehaviour = new MonoBehaviour;
		component->m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetCodeImage());
		component->m_pBehaviour->Create(sName.c_str(), cName.c_str());
		component->Awake();
		component->Start();
	}

	if (component == nullptr)
	{
		return nullptr;
	}

	return component->GetMonoBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(GameObject, set_Material, CS_OBJECT, cs_boj, CS_OBJECT, material)
{
	Material *m = static_cast<Material*>(getCppObject(material));
	if (m == nullptr)
	{
		return;
	}
	GameObject * obj = static_cast<GameObject*>(getCppObject(cs_boj));
	if (obj == nullptr)
	{
		return;
	}
	obj->SetMaterial(m);
}


CS_OBJECT _1_PARAM_FUNCTION(GameObject, get_Material, CS_OBJECT, cs_boj)
{
	GameObject * obj = static_cast<GameObject*>(getCppObject(cs_boj));
	if (obj == nullptr)
	{
		return nullptr;
	}
	Material * m = obj->GetMaterial();
	if (m == nullptr)
	{
		return nullptr;
	}

	return m->GetBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(GameObject, set_Active, CS_OBJECT, cs_boj, CS_BOOL, isActive)
{
	void * node = getCppObject(cs_boj);
	if (node == nullptr)
	{
		return;
	}

	static_cast<GameObject*>(node)->SetActive(isActive);
}


CS_BOOL _1_PARAM_FUNCTION(GameObject, get_Active, CS_OBJECT, cs_boj)
{
	void * node = getCppObject(cs_boj);
	if (node == nullptr)
	{
		return 0;
	}

	return static_cast<GameObject*>(node)->IsActive == true ? 1 : 0;
}

UINT _1_PARAM_FUNCTION(GameObject, get_LayerMask, CS_OBJECT, cs_boj)
{
	void * node = getCppObject(cs_boj);
	if (node == nullptr)
	{
		return 0;
	}

	return static_cast<GameObject*>(node)->GetLayerMask();
}


UINT _1_PARAM_FUNCTION(Object, get_ID, CS_OBJECT, cs_boj)
{
	Object * obj = static_cast<Object*>(getCppObject(cs_boj));
	if (obj == nullptr)
	{
		return 0;
	}
	return obj->ID;
}

VOID _2_PARAM_FUNCTION(GameObject, set_LayerMask, CS_OBJECT, cs_boj, UINT, mask)
{
	void * node = getCppObject(cs_boj);

	if (node == nullptr)
	{
		return;
	}

	static_cast<GameObject*>(node)->SetLayerMask(mask);
}