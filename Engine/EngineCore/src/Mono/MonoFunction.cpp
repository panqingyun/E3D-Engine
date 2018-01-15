#include "MonoFunction.h"
#include "../Source/EngineDelegate.h"

void RegisterMonoFunction()
{
	REGISTER_INTERNAL_CALL(Object,		get_Name);
	REGISTER_INTERNAL_CALL(Object,		set_Name);
	REGISTER_INTERNAL_CALL(Object,		get_ID);
	REGISTER_INTERNAL_CALL(Transform,	getPosition);
	REGISTER_INTERNAL_CALL(Transform,	setPosition);
	REGISTER_INTERNAL_CALL(Transform,	getScale);
	REGISTER_INTERNAL_CALL(Transform,	setScale);
	REGISTER_INTERNAL_CALL(Transform,	getRotation);
	REGISTER_INTERNAL_CALL(Transform,	setRotation);
	REGISTER_INTERNAL_CALL(Transform,	getForward);
	REGISTER_INTERNAL_CALL(Transform,	getUp);
	REGISTER_INTERNAL_CALL(Transform,	getRight);
	REGISTER_INTERNAL_CALL(GameObject,	set_LayerMask);
	REGISTER_INTERNAL_CALL(GameObject,	get_LayerMask);
	REGISTER_INTERNAL_CALL(GameObject,	set_Material);
	REGISTER_INTERNAL_CALL(GameObject,	get_Material);
	REGISTER_INTERNAL_CALL(GameObject,	set_Active);
	REGISTER_INTERNAL_CALL(GameObject,	get_Active);
	REGISTER_INTERNAL_CALL(GameObject,	addComponent);
	REGISTER_INTERNAL_CALL(GameObject,	removeComponent);
	REGISTER_INTERNAL_CALL(GameObject,	findChildWithName);
	REGISTER_INTERNAL_CALL(GameObject,	findChildWithID);
	REGISTER_INTERNAL_CALL(GameObject,	AddChild);
	REGISTER_INTERNAL_CALL(GameObject,	CreateSkyBox);
	REGISTER_INTERNAL_CALL(Camera,		setClearColor);
	REGISTER_INTERNAL_CALL(Camera,		renderCamera);
	REGISTER_INTERNAL_CALL(Camera,		createCamera);
	REGISTER_INTERNAL_CALL(Camera,		screen2WorldPoint);
	REGISTER_INTERNAL_CALL(Camera,		getViewMatrix);
	REGISTER_INTERNAL_CALL(Camera,		getProjectionMatrix);
	REGISTER_INTERNAL_CALL(Debug,		log_error);
	REGISTER_INTERNAL_CALL(Debug,		log_warning);
	REGISTER_INTERNAL_CALL(Debug,		log_info);
	REGISTER_INTERNAL_CALL(Scene,		createScene);
	REGISTER_INTERNAL_CALL(Scene,		changeScene);
	REGISTER_INTERNAL_CALL(Scene,		destoryScene);
	REGISTER_INTERNAL_CALL(Render,		createRenderer);
	REGISTER_INTERNAL_CALL(Render,		createRendererWithoutParam);
	REGISTER_INTERNAL_CALL(Render,		setVertex2Render);
	REGISTER_INTERNAL_CALL(Render,		setDrawModule);
	REGISTER_INTERNAL_CALL(Render,		getDrawModule);
	REGISTER_INTERNAL_CALL(Material,	createMaterial);
	REGISTER_INTERNAL_CALL(Box,			Create);
	REGISTER_INTERNAL_CALL(RigidBody,	addRigidBody);
	REGISTER_INTERNAL_CALL(ParticleSystem,	createParticle);
	REGISTER_INTERNAL_CALL(ParticleGroup,	SetEmitterEnable);
	REGISTER_INTERNAL_CALL(Sphere,			Create);
	REGISTER_INTERNAL_CALL(Terrain,			Create);
	REGISTER_INTERNAL_CALL(Light,			Create);
	REGISTER_INTERNAL_CALL(Light,			setColor);

}

VOID _1_PARAM_FUNCTION(Camera, renderCamera, CS_OBJECT, cs_obj)
{
	Camera * camera = getCppObject<Camera>(cs_obj);
	if (camera == nullptr)
	{
		return;
	}
	camera->Render(0.2f);
}

VOID _4_PARAM_FUNCTION(Transform, getPosition, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform* transform = getCppObject<CTransform>(obj);
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
	CTransform* transform = getCppObject<CTransform>(obj);
	if (transform == nullptr)
	{
		return;
	}
	transform->SetPosition(x, y, z);
}

VOID _4_PARAM_FUNCTION(Transform, getScale, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform* transform = getCppObject<CTransform>(obj);
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
	CTransform* transform = getCppObject<CTransform>(obj);
	if (transform == nullptr)
	{
		return;
	}

	transform->SetScale(x, y, z);
}

VOID _4_PARAM_FUNCTION(Transform, getRotation, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform* transform = getCppObject<CTransform>(obj);
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
	CTransform* transform = getCppObject<CTransform>(obj);
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
	const float32 zFar = 3000.0f;
	Vector2 frameSize = GetRenderSystem()->GetFrameSize();
	const float32 aspect = frameSize.x / frameSize.y;
	const vec3f position = vec3f(0, 0, 200);
	const vec3f target = vec3f(0, 0, -1);
	E3DEngine::Camera *camera = new E3DEngine::Camera(position, target, fov, up, zNear, zFar, aspect);
	return camera->GetMonoBehaviour()->GetMonoObject();
}

VOID _5_PARAM_FUNCTION(Camera, setClearColor, CS_OBJECT, cs_boj, float, r, float, g, float, b, float, a)
{
	Camera * camera = getCppObject<Camera>(cs_boj);
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
	Collider * collider = getCppObject<Collider>(_collider);

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

CS_OBJECT _3_PARAM_FUNCTION(Box, Create, float, l, float, w, float, h)
{
	Box *box = new Box;
	ADD_IN_SCENE(box);
	box->Create(l, w, h);

	return box->GetMonoBehaviour()->GetMonoObject();
}

VOID _1_PARAM_FUNCTION(GameObject, removeComponent, CS_OBJECT, cs_obj)
{
	Component *com = getCppObject<Component>(cs_obj);

	if (com == nullptr)
	{
		return;
	}

	com->gameObject->RemoveComponent(com);
}

VOID _2_PARAM_FUNCTION(Object, set_Name, CS_OBJECT, cs_obj, CS_STRING, name)
{
	Object *go = getCppObject<Object>(cs_obj);

	if (go == nullptr)
	{
		return;
	}

	go->Name = Convert::ToString(name);
}

CS_STRING _1_PARAM_FUNCTION(Object, get_Name, CS_OBJECT, cs_obj)
{
	Object *go = getCppObject<Object>(cs_obj);

	if (go == nullptr)
	{
		return mono_string_empty(MonoScriptManager::GetInstance().GetEngineDomain());
	}

	return mono_string_new(MonoScriptManager::GetInstance().GetEngineDomain(), go->Name.c_str());
}

CS_OBJECT _2_PARAM_FUNCTION(GameObject, addComponent, CS_OBJECT, obj, CS_STRING, class_name)
{
	GameObject *go = getCppObject<GameObject>(obj);

	if (go == nullptr)
	{
		return nullptr;
	}
	std::string full_name = Convert::ToString(class_name);
	std::string cName = "";
	std::string sName = "";
	int dotPos = full_name.find_last_of(".");

	Component * component = nullptr;
	if (dotPos == std::string::npos)
	{
		cName = full_name;
	}
	else
	{
		cName = full_name.substr(dotPos + 1);
		sName = full_name.substr(0, dotPos);
	}
	string kName = ClassFactory::GetInstance().getTypeNameByClassName(cName);
	if (kName != "NAN")
	{
		component = go->AddComponent(kName.c_str());
	}
	else
	{
		// 不是引擎类
		component = new Component;
		component->TypeName = full_name;
		component->m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetCodeImage());
		component->m_pBehaviour->Create(sName.c_str(), cName.c_str());
		go->AddComponent(component);
	}

	if (component == nullptr)
	{
		return nullptr;
	}

	return component->GetMonoBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(GameObject, set_Material, CS_OBJECT, cs_boj, CS_OBJECT, material)
{
	Material *m = getCppObject<Material>(material);
	if (m == nullptr)
	{
		return;
	}
	GameObject * obj = getCppObject<GameObject>(cs_boj);
	if (obj == nullptr)
	{
		return;
	}
	obj->SetMaterial(m);
}


CS_OBJECT _1_PARAM_FUNCTION(GameObject, get_Material, CS_OBJECT, cs_boj)
{
	GameObject * obj = getCppObject<GameObject>(cs_boj);
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
	GameObject * go = getCppObject<GameObject>(cs_boj);
	if (go == nullptr)
	{
		return;
	}

	go->SetActive(isActive);
}


CS_BOOL _1_PARAM_FUNCTION(GameObject, get_Active, CS_OBJECT, cs_boj)
{
	GameObject * go = getCppObject<GameObject>(cs_boj);
	if (go == nullptr)
	{
		return 0;
	}

	return go->IsActive == true ? 1 : 0;
}

UINT _1_PARAM_FUNCTION(GameObject, get_LayerMask, CS_OBJECT, cs_boj)
{
	GameObject * go = getCppObject<GameObject>(cs_boj);
	if (go == nullptr)
	{
		return 0;
	}

	return go->GetLayerMask();
}


UINT _1_PARAM_FUNCTION(Object, get_ID, CS_OBJECT, cs_boj)
{
	Object * obj = getCppObject<Object>(cs_boj);
	if (obj == nullptr)
	{
		return 0;
	}
	return obj->ID;
}

VOID _2_PARAM_FUNCTION(GameObject, set_LayerMask, CS_OBJECT, cs_boj, UINT, mask)
{
	GameObject * go = getCppObject<GameObject>(cs_boj);

	if (go == nullptr)
	{
		return;
	}

	go->SetLayerMask(mask);
}

CS_ARRAY _2_PARAM_FUNCTION(ParticleSystem, createParticle, CS_OBJECT, cs_obj , CS_STRING, path)
{
	std::string particle_path = Convert::ToString(path);
	std::vector<ParticleGroup*> *pG = ParticleSystem::GetInstance().ActiveParticle(particle_path);

	MonoClass *klass = mono_class_from_name(MonoScriptManager::GetInstance().GetEngineImage(),
		NAME_SPACE,__STRINGIFY(ParticleGroup));
	MonoArray * particleGroups = mono_array_new(MonoScriptManager::GetInstance().GetEngineDomain(), klass, pG->size());
	int index = 0;
	for (auto &group : *pG)
	{
		ADD_IN_SCENE(group);
		klass = group->GetMonoBehaviour()->GetClass();
		MonoType *type = mono_class_get_type(klass);
		mono_array_setref(particleGroups, index, group->GetMonoBehaviour()->GetMonoObject());
		index++;
	}
	SAFE_DELETE(pG);
	return particleGroups;
}

VOID _2_PARAM_FUNCTION(ParticleGroup, SetEmitterEnable, CS_OBJECT, cs_obj, CS_BOOL, enable)
{
	ParticleGroup * group = getCppObject<ParticleGroup>(cs_obj);

	if (group == nullptr)
	{
		return;
	}

	group->SetEmitterEnable(enable == 1);
}

CS_OBJECT _4_PARAM_FUNCTION(Camera, screen2WorldPoint, CS_OBJECT, cs_obj, float&, x, float&, y, float&, z)
{
	Camera * camera = getCppObject<Camera>(cs_obj);

	if (camera == nullptr)
	{
		return nullptr;
	}
	vec3f newPos(x, y, z);

	newPos.x	= newPos.x / GetRenderSystem()->getFrameWidth() - 0.5;
	newPos.y	= -1 * (newPos.y / GetRenderSystem()->getFrameHeight() - 0.5);
	newPos		= camera->GetWorldPointWithScreenPoint(newPos.x, newPos.y, newPos.z);
	
	x = newPos.x;
	y = newPos.y;
	z = newPos.z;
}

VOID _1_PARAM_FUNCTION(GameObject, destory, CS_OBJECT, cs_obj)
{
	GameObject *go = getCppObject<GameObject>(cs_obj);
	if (go == nullptr)
	{
		return;
	}

	EngineDelegate::GetInstance().DestoryObject(go);
}

CS_OBJECT _2_PARAM_FUNCTION(GameObject, findChildWithName, CS_OBJECT, cs_obj, CS_STRING, name)
{
	GameObject *go = getCppObject<GameObject>(cs_obj);

	if (go == nullptr)
	{
		return nullptr;
	}
	std::string cName = Convert::ToString(name);
	GameObject * child = go->FindChild(cName);
	if (child == nullptr)
	{
		return nullptr;
	}

	return child->GetMonoBehaviour()->GetMonoObject();
}

CS_OBJECT _2_PARAM_FUNCTION(GameObject, findChildWithID, CS_OBJECT, cs_obj, UINT, id)
{
	GameObject *go = getCppObject<GameObject>(cs_obj);

	if (go == nullptr)
	{
		return nullptr;
	}

	GameObject * child = go->FindChild(id);
	if (child == nullptr)
	{
		return nullptr;
	}

	return child->GetMonoBehaviour()->GetMonoObject();
}

CS_OBJECT _1_PARAM_FUNCTION(Sphere, Create, float, r)
{
	Sphere *sphere = new Sphere();
	sphere->Create(r);
	ADD_IN_SCENE(sphere);

	return sphere->GetMonoBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(GameObject, AddChild, CS_OBJECT, cs_obj, CS_OBJECT, child)
{
	GameObject *go = getCppObject<GameObject>(cs_obj);
	if (go == nullptr)
	{
		return;
	}

	GameObject *_child = getCppObject<GameObject>(child);
	if (_child == nullptr)
	{
		return;
	}

	go->AddChild(_child);
}

CS_OBJECT _1_PARAM_FUNCTION(Terrain, Create, CS_STRING, heightMap)
{
	Terrain * terrain = new Terrain;
	terrain->Create(Convert::ToString(heightMap).c_str());
	ADD_IN_SCENE(terrain);

	return terrain->GetMonoBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(Render, setDrawModule, CS_OBJECT, cs_obj, UINT, drawModule)
{
	RenderObject * rd = getCppObject<RenderObject>(cs_obj);

	if (rd == nullptr)
	{
		return;
	}

	rd->SetDrawModule(drawModule);
}

UINT _1_PARAM_FUNCTION(Render, getDrawModule, CS_OBJECT, cs_obj)
{
	RenderObject * rd = getCppObject<RenderObject>(cs_obj);

	if (rd == nullptr)
	{
		return eDM_TRIANGLES;
	}

	return rd->GetDrawModule();
}

VOID _1_PARAM_FUNCTION(GameObject, CreateSkyBox, CS_OBJECT, material)
{
	SkyBox *skyBox = new SkyBox();
	skyBox->Create(50, 50, 50);
	Material * m = getCppObject<Material>(material);
	skyBox->SetMaterial(m);

	ADD_IN_SCENE(skyBox);
}

CS_OBJECT _1_PARAM_FUNCTION(Light, Create, UINT, lightType)
{
	Light * light = Light::Create((LightType)lightType);
	SceneManager::GetInstance().GetCurrentScene()->AddLight(light);
	return light->GetMonoBehaviour()->GetMonoObject();
}

VOID _5_PARAM_FUNCTION(Light, setColor, CS_OBJECT, cs_obj, float, r, float, g, float, b,float, a)
{
	Light *light = getCppObject<Light>(cs_obj);

	if (light == nullptr)
	{
		return;
	}
	light->Color = vec4f(r, g, b, a);
}

VOID _4_PARAM_FUNCTION(Transform, getForward, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform * transform = getCppObject<CTransform>(obj);

	if (transform == nullptr)
	{
		return;
	}
	vec3f forward = transform->GetForward();
	x = forward.x;
	y = forward.y;
	z = forward.z;
}

VOID _4_PARAM_FUNCTION(Transform, getUp, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform * transform = getCppObject<CTransform>(obj);

	if (transform == nullptr)
	{
		return;
	}
	vec3f forward = transform->GetUp();
	x = forward.x;
	y = forward.y;
	z = forward.z;
}

VOID _4_PARAM_FUNCTION(Transform, getRight, CS_OBJECT, obj, float&, x, float&, y, float&, z)
{
	CTransform * transform = getCppObject<CTransform>(obj);

	if (transform == nullptr)
	{
		return;
	}
	vec3f forward = transform->GetRight();
	x = forward.x;
	y = forward.y;
	z = forward.z;
}

VOID _2_PARAM_FUNCTION(Camera, getViewMatrix, CS_OBJECT, cs_obj, CS_ARRAY& data)
{
	Camera * camera = getCppObject<Camera>(cs_obj);
	if (camera == nullptr)
	{
		return;
	}
	const float *mData = camera->GetViewMatrix().data;

	for (int i = 0; i < 16; i ++)
	{
		mono_array_set(data, float, i, mData[i]);
	}
}

VOID _2_PARAM_FUNCTION(Camera, getProjectionMatrix, CS_OBJECT, cs_obj, CS_ARRAY& data)
{
	Camera * camera = getCppObject<Camera>(cs_obj);
	if (camera == nullptr)
	{
		return;
	}
	const float *mData = camera->GetProjectionMatrix().data;

	for (int i = 0; i < 16; i++)
	{
		mono_array_set(data, float, i, mData[i]);
	}
}