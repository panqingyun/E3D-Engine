
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-1  PanQingyun. All rights reserved. ************************//

#include "MonoFunction.h"
#include "../Source/EngineDelegate.h"
#include "../Source/E3DVertexManager.h"

void RegisterMonoFunction()
{
	REGISTER_INTERNAL_CALL(Object,		get_Name);
	REGISTER_INTERNAL_CALL(Object,		set_Name);
	REGISTER_INTERNAL_CALL(Object,		get_ID);
	REGISTER_INTERNAL_CALL(Transform,	getPosition);
	REGISTER_INTERNAL_CALL(Transform,   setPosition);
	REGISTER_INTERNAL_CALL(Transform,	getScale);
	REGISTER_INTERNAL_CALL(Transform,	setScale);
	REGISTER_INTERNAL_CALL(Transform,	getRotation);
	REGISTER_INTERNAL_CALL(Transform,	setRotation);
	REGISTER_INTERNAL_CALL(Transform,	getForward);
	REGISTER_INTERNAL_CALL(Transform,	getUp);
	REGISTER_INTERNAL_CALL(Transform,	getRight);
	REGISTER_INTERNAL_CALL(GameObject,	set_LayerMask);
	REGISTER_INTERNAL_CALL(GameObject,	get_LayerMask);
	REGISTER_INTERNAL_CALL(Renderer,	set_Material);
	REGISTER_INTERNAL_CALL(Renderer,	get_Material);
	REGISTER_INTERNAL_CALL(GameObject,	set_Active);
	REGISTER_INTERNAL_CALL(GameObject,	get_Active);
	REGISTER_INTERNAL_CALL(GameObject,	get_Renderer);
	REGISTER_INTERNAL_CALL(GameObject,	addComponent);
	REGISTER_INTERNAL_CALL(GameObject,	getComponent);
	REGISTER_INTERNAL_CALL(GameObject,	removeComponent);
	REGISTER_INTERNAL_CALL(GameObject,	findChildWithName);
	REGISTER_INTERNAL_CALL(GameObject,	findChildWithName);
	REGISTER_INTERNAL_CALL(GameObject,	newGameObject);
	REGISTER_INTERNAL_CALL(GameObject,	AddChild);
	REGISTER_INTERNAL_CALL(Camera,		get_MainCamera);
	REGISTER_INTERNAL_CALL(Camera,		renderCamera);
	REGISTER_INTERNAL_CALL(Camera,		screen2WorldPoint);
	REGISTER_INTERNAL_CALL(Camera,		getViewMatrix);
	REGISTER_INTERNAL_CALL(Camera,		getProjectionMatrix);
	REGISTER_INTERNAL_CALL(Debug,		log_error);
	REGISTER_INTERNAL_CALL(Debug,		log_warning);
	REGISTER_INTERNAL_CALL(Debug,		log_info);
	REGISTER_INTERNAL_CALL(Scene,		createScene);
	REGISTER_INTERNAL_CALL(Renderer,	createRenderer);
	REGISTER_INTERNAL_CALL(Renderer,	createRendererWithoutParam);
	REGISTER_INTERNAL_CALL(Renderer,	setVertex2Render);
	REGISTER_INTERNAL_CALL(Renderer,	setDrawModule);
	REGISTER_INTERNAL_CALL(Renderer,	getDrawModule);
	REGISTER_INTERNAL_CALL(Material,	createMaterial);
	REGISTER_INTERNAL_CALL(RigidBody,	    set_Mass);
	REGISTER_INTERNAL_CALL(RigidBody,		get_Mass);
	REGISTER_INTERNAL_CALL(ParticleSystem,	createParticle);
	REGISTER_INTERNAL_CALL(ParticleGroup,	SetEmitterEnable);
	REGISTER_INTERNAL_CALL(Light,			setColor);
	REGISTER_INTERNAL_CALL(PointLight,		set_Range);
	REGISTER_INTERNAL_CALL(PointLight,		get_Range);
	REGISTER_INTERNAL_CALL(Renderer, set_RenderIndex);
	REGISTER_INTERNAL_CALL(Renderer, get_RenderIndex);
	REGISTER_INTERNAL_CALL(RigidBody,		get_Friction);
	REGISTER_INTERNAL_CALL(RigidBody,		get_Restitution);
	REGISTER_INTERNAL_CALL(RigidBody,		set_Friction);
	REGISTER_INTERNAL_CALL(RigidBody,		set_Restitution);
	REGISTER_INTERNAL_CALL(Collider,		setSize);
	REGISTER_INTERNAL_CALL(Collider,		getSize);
	REGISTER_INTERNAL_CALL(CapsuleCollider, set_Radius);
	REGISTER_INTERNAL_CALL(CapsuleCollider, get_Radius);
	REGISTER_INTERNAL_CALL(CapsuleCollider, set_Height);
	REGISTER_INTERNAL_CALL(CapsuleCollider, get_Height);
	REGISTER_INTERNAL_CALL(Material,		UpdateFloatValue);
	REGISTER_INTERNAL_CALL(Material,		UpdateFloat2Value);
	REGISTER_INTERNAL_CALL(Material,		UpdateFloat3Value);
	REGISTER_INTERNAL_CALL(Material,		UpdateFloat4Value);

}

VOID _1_PARAM_FUNCTION(GameObject, newGameObject, CS_OBJECT, cs_obj)
{
	GameObject *go = new GameObject();
	go->mName = "GameObject";
	go->SetMonoObject(cs_obj);
	go->SetActive(true);
	go->SetLayerMask(1);
	ADD_IN_SCENE(go);
}

VOID _1_PARAM_FUNCTION(Camera, renderCamera, CS_OBJECT, cs_obj)
{
	Camera * camera = getCppObject<Camera>(cs_obj);
	if (camera == nullptr)
	{
		return;
	}
	camera->Render();
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
	transform->SetLocalPosition(x, y, z);
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

	transform->SetLocalScale(x, y, z);
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
	transform->SetLocalRotation(x, y, z);
}

VOID _1_PARAM_FUNCTION(Debug, log_error, CS_STRING, err)
{
	std::string _log = Convert::ToStdString(err);
	E3DEngine::Debug::Log(ell_Error, _log.c_str());
}

VOID _1_PARAM_FUNCTION(Debug, log_warning, CS_STRING, warning)
{
	std::string _log = Convert::ToStdString(warning);
	E3DEngine::Debug::Log(ell_Warning, _log.c_str());
}

VOID _1_PARAM_FUNCTION(Debug, log_info, CS_STRING, info)
{
	std::string _log = Convert::ToStdString(info);
	E3DEngine::Debug::Log(ell_Info, _log.c_str());
}

CS_OBJECT _1_PARAM_FUNCTION(Scene, createScene, CS_STRING, path)
{
	SceneManager::GetInstance().LoadScene(Convert::ToStdString(path));
	Scene * scene = SceneManager::GetInstance().GetCurrentScene();
	return scene->GetMonoBehaviour()->GetMonoObject();
}

CS_OBJECT _1_PARAM_FUNCTION(Renderer, createRenderer, UINT, materialID)
{
	// TODO
	BatchRenderer * render = GetRenderSystem()->GetRenderManager()->GetRenderer(materialID, 0);

	return render->GetMonoBehaviour()->GetMonoObject();
}

VOID _1_PARAM_FUNCTION(Renderer, setVertex2Render, CPP_OBJECT, obj)
{
	
}

CS_OBJECT _0_PARAM_FUNCTION(Renderer, createRendererWithoutParam)
{
	BatchRenderer * render = new BatchRenderer();

	return render->GetMonoBehaviour()->GetMonoObject();
}

CS_OBJECT _2_PARAM_FUNCTION(Material, createMaterial, CS_STRING, path, int, id)
{
	std::string m_Path = Convert::ToStdString(path);

	E3DEngine::Material * material = GetRenderSystem()->GetMaterialManager()->CreateMaterial(m_Path, id);
	return material->GetBehaviour()->GetMonoObject();
}

VOID _1_PARAM_FUNCTION(GameObject, removeComponent, CS_OBJECT, cs_obj)
{
	Component *com = getCppObject<Component>(cs_obj);

	if (com == nullptr)
	{
		return;
	}

	com->mGameObject->RemoveComponent(com);
}

VOID _2_PARAM_FUNCTION(Object, set_Name, CS_OBJECT, cs_obj, CS_STRING, name)
{
	Object *go = getCppObject<Object>(cs_obj);

	if (go == nullptr)
	{
		return;
	}

	go->mName = Convert::ToStdString(name);
}

CS_STRING _1_PARAM_FUNCTION(Object, get_Name, CS_OBJECT, cs_obj)
{
	Object *go = getCppObject<Object>(cs_obj);

	if (go == nullptr)
	{
		return mono_string_empty(MonoScriptManager::GetInstance().GetEngineDomain());
	}

	return mono_string_new(MonoScriptManager::GetInstance().GetEngineDomain(), go->mName.c_str());
}

CS_OBJECT _2_PARAM_FUNCTION(GameObject, addComponent, CS_OBJECT, obj, CS_STRING, class_name)
{
	GameObject *go = getCppObject<GameObject>(obj);

	if (go == nullptr)
	{
		return nullptr;
	}
	std::string full_name = Convert::ToStdString(class_name);

	Component * component = go->AddComponent(full_name.c_str());

	if (component == nullptr)
	{
		return nullptr;
	}

	component->OnCreate();
	component->OnCreateComplete();
	return component->GetMonoBehaviour()->GetMonoObject();
}

CS_OBJECT _2_PARAM_FUNCTION(GameObject, getComponent, CS_OBJECT, obj, CS_STRING, class_name)
{
	GameObject *go = getCppObject<GameObject>(obj);

	if (go == nullptr)
	{
		return nullptr;
	}
	std::string full_name = Convert::ToStdString(class_name);

	Component * component = go->GetComponent(full_name.c_str());

	if (component == nullptr)
	{
		return nullptr;
	}

	return component->Get()->GetMonoBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(Renderer, set_Material, CS_OBJECT, cs_boj, CS_OBJECT, material)
{
	Material *m = getCppObject<Material>(material);
	if (m == nullptr)
	{
		return;
	}
	BatchRenderer * obj = getCppObject<BatchRenderer>(cs_boj);
	if (obj == nullptr)
	{
		return;
	}
	obj->SetMaterial(m);
}


CS_OBJECT _1_PARAM_FUNCTION(Renderer, get_Material, CS_OBJECT, cs_boj)
{
	BatchRenderer * obj = getCppObject<BatchRenderer>(cs_boj);
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
	std::string particle_path = Convert::ToStdString(path);
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

VOID _4_PARAM_FUNCTION(Camera, screen2WorldPoint, CS_OBJECT, cs_obj, float&, x, float&, y, float&, z)
{
	Camera * camera = getCppObject<Camera>(cs_obj);

	if (camera == nullptr)
	{
		return;
	}
	vec3f newPos(x, y, z);
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
	GameObject::Destory(go);
}

CS_OBJECT _2_PARAM_FUNCTION(GameObject, findChildWithName, CS_OBJECT, cs_obj, CS_STRING, name)
{
	GameObject *go = getCppObject<GameObject>(cs_obj);

	if (go == nullptr)
	{
		return nullptr;
	}
	std::string cName = Convert::ToStdString(name);
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

VOID _2_PARAM_FUNCTION(Renderer, setDrawModule, CS_OBJECT, cs_obj, UINT, drawModule)
{
	RenderObject * rd = getCppObject<RenderObject>(cs_obj);

	if (rd == nullptr)
	{
		return;
	}

	rd->SetDrawModule(drawModule);
}

UINT _1_PARAM_FUNCTION(Renderer, getDrawModule, CS_OBJECT, cs_obj)
{
	RenderObject * rd = getCppObject<RenderObject>(cs_obj);

	if (rd == nullptr)
	{
		return eDM_TRIANGLES;
	}

	return rd->GetDrawModule();
}

VOID _5_PARAM_FUNCTION(Light, setColor, CS_OBJECT, cs_obj, float, r, float, g, float, b,float, a)
{
	Light *light = getCppObject<Light>(cs_obj);

	if (light == nullptr)
	{
		return;
	}
	/*light->Color.r = r;
	light->Color.g = g;
	light->Color.b = b;
	light->Color.a = a;*/
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

VOID _2_PARAM_FUNCTION(Camera, getViewMatrix, CS_OBJECT, cs_obj, CS_ARRAY&, data)
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

VOID _2_PARAM_FUNCTION(Camera, getProjectionMatrix, CS_OBJECT, cs_obj, CS_ARRAY&, data)
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

VOID _2_PARAM_FUNCTION(PointLight, set_Range, CS_OBJECT, light, float, range)
{
	PointLight * pl = getCppObject<PointLight>(light);
	if (pl == nullptr)
	{
		return;
	}
	pl->Range = range;
}

float _1_PARAM_FUNCTION(PointLight, get_Range, CS_OBJECT, light)
{
	PointLight * pl = getCppObject<PointLight>(light);
	if (pl == nullptr)
	{
		return 0;
	}

	return pl->Range;
}

UINT _1_PARAM_FUNCTION(Renderer, get_RenderIndex, CS_OBJECT, cs_boj)
{
	RenderObject* rb = getCppObject<RenderObject>(cs_boj);
	if (rb == nullptr)
	{
		return 0;
	}

	return rb->RenderIndex;
}
VOID _2_PARAM_FUNCTION(Renderer, set_RenderIndex, CS_OBJECT, cs_boj, UINT, ri)
{
	RenderObject* rb = getCppObject<RenderObject>(cs_boj);
	if (rb == nullptr)
	{
		return;
	}

	rb->SetRenderIndex(ri);
}

CS_OBJECT _0_PARAM_FUNCTION(Camera, get_MainCamera)
{
	Camera *pCamera = SceneManager::GetCurrentScene()->GetMainCamera();
	if (pCamera == nullptr)
	{
		return nullptr;
	}
	return pCamera->GetMonoBehaviour()->GetMonoObject();
}

VOID _2_PARAM_FUNCTION(RigidBody, set_Mass, CS_OBJECT, rigibody, float, mass)
{
	RigidBody * rb = getCppObject<RigidBody>(rigibody);
	if (rb == nullptr)
	{
		return;
	}

	RigidBody::SetMass(rb, mass);
}

float _1_PARAM_FUNCTION(RigidBody, get_Mass, CS_OBJECT, rigibody)
{
	RigidBody * rb = getCppObject<RigidBody>(rigibody);
	if (rb == nullptr)
	{
		return 0;
	}

	return object_cast<float>(RigidBody::GetMass(rb));
}

float _1_PARAM_FUNCTION(RigidBody, get_Friction, CS_OBJECT, rigibody)
{
	RigidBody * rb = getCppObject<RigidBody>(rigibody);
	if (rb == nullptr)
	{
		return 0;
	}

	return object_cast<float>(RigidBody::GetFriction(rb));
}

float _1_PARAM_FUNCTION(RigidBody, get_Restitution, CS_OBJECT, rigibody)
{
	RigidBody * rb = getCppObject<RigidBody>(rigibody);
	if (rb == nullptr)
	{
		return 0;
	}

	return object_cast<float>(RigidBody::GetRestitution(rb));
}

VOID _2_PARAM_FUNCTION(RigidBody, set_Friction, CS_OBJECT, rigibody, float, friction)
{
	RigidBody * rb = getCppObject<RigidBody>(rigibody);
	if (rb == nullptr)
	{
		return;
	}

	RigidBody::SetFriction(rb,friction);
}

VOID _2_PARAM_FUNCTION(RigidBody, set_Restitution, CS_OBJECT, rigibody, float, restitution)
{
	RigidBody * rb = getCppObject<RigidBody>(rigibody);
	if (rb == nullptr)
	{
		return;
	}

	RigidBody::SetRestitution(rb, restitution);
}

VOID _2_PARAM_FUNCTION(Collider, setSize, CS_OBJECT, collider, float, x, float, y, float, z)
{

}

VOID _2_PARAM_FUNCTION(Collider, getSize, CS_OBJECT, collider, float&, x, float&, y, float&, z)
{

}

VOID _2_PARAM_FUNCTION(CapsuleCollider, set_Radius, CS_OBJECT, capsuleCollider, float, radius)
{
	CapsuleCollider * collider = getCppObject<CapsuleCollider>(capsuleCollider);
	if (collider == nullptr)
	{
		return;
	}

	collider->SetRadius(radius);
}

float _1_PARAM_FUNCTION(CapsuleCollider, get_Radius, CS_OBJECT, capsuleCollider)
{
	CapsuleCollider * collider = getCppObject<CapsuleCollider>(capsuleCollider);
	if (collider == nullptr)
	{
		return 0;
	}

	return collider->GetRadius();
}

VOID _2_PARAM_FUNCTION(CapsuleCollider, set_Height, CS_OBJECT, capsuleCollider, float, height)
{
	CapsuleCollider * collider = getCppObject<CapsuleCollider>(capsuleCollider);
	if (collider == nullptr)
	{
		return;
	}

	collider->SetHieght(height);
}

float _1_PARAM_FUNCTION(CapsuleCollider, get_Height, CS_OBJECT, capsuleCollider)
{
	CapsuleCollider * collider = getCppObject<CapsuleCollider>(capsuleCollider);
	if (collider == nullptr)
	{
		return 0;
	}

	return collider->GetHeight();
}

CS_OBJECT _1_PARAM_FUNCTION(GameObject, get_Renderer, CS_OBJECT, gameObject)
{
	GameObject *gameObj = getCppObject<GameObject>(gameObject);

	if (gameObj == nullptr)
	{
		return nullptr;
	}

	if (gameObj->GetRenderer() == nullptr)
	{
		return nullptr;
	}

	return gameObj->GetRenderer()->GetMonoBehaviour()->GetMonoObject();
}

VOID _3_PARAM_FUNCTION(Material, UpdateFloatValue, CS_OBJECT, material, CS_STRING, name, float, value)
{
	Material *m = getCppObject<Material>(material);
	if (m == nullptr)
	{
		return;
	}
	std::string uniformName = Convert::ToStdString(name);
	m->GetShader()->UpdateFloatValue(uniformName, value);
}

VOID _4_PARAM_FUNCTION(Material, UpdateFloat2Value, CS_OBJECT, material, CS_STRING, name, float, value1, float, value2)
{
	Material *m = getCppObject<Material>(material);
	if (m == nullptr)
	{
		return;
	}
	std::string uniformName = Convert::ToStdString(name);
	m->GetShader()->UpdateFloatValue(uniformName, value1, value2);
}

VOID _5_PARAM_FUNCTION(Material, UpdateFloat3Value, CS_OBJECT, material, CS_STRING, name, float, value1, float, value2, float, value3)
{
	Material *m = getCppObject<Material>(material);
	if (m == nullptr)
	{
		return;
	}
	std::string uniformName = Convert::ToStdString(name);
	m->GetShader()->UpdateFloatValue(uniformName, value1, value2, value3);
}

VOID _6_PARAM_FUNCTION(Material, UpdateFloat4Value, CS_OBJECT, material, CS_STRING, name, float, value1, float, value2, float, value3, float, value4)
{
	Material *m = getCppObject<Material>(material);
	if (m == nullptr)
	{
		return;
	}
	std::string uniformName = Convert::ToStdString(name);
	m->GetShader()->UpdateFloatValue(uniformName, value1, value2, value3, value4);
}

VOID _4_PARAM_FUNCTION(Camera, world2ScreenPoint, CS_OBJECT, cs_obj, float&, x, float&, y, float&, z)
{
	Camera * camera = getCppObject<Camera>(cs_obj);

	if (camera == nullptr)
	{
		return;
	}
	vec3f newPos(x, y, z);

	vec3f &&pos = camera->GetScreenPointWithWorlPoint(newPos);

	x = pos.x;
	y = pos.y;
	z = pos.z;
}