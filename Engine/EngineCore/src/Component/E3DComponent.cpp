
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-2-8  PanQingyun. All rights reserved. *************************//

#include "E3DComponent.hpp"
#include "../Object/E3DGameObject.h"
#include "../../3rd/Mono/mono/metadata/tabledefs.h"
#include "../Source/ClassFactory.h"
#include "../Source/EngineDelegate.h"
#include "../Physics/E3DCollider.hpp"
#include "E3DBox.h"
#include "E3DCoordinate.h"
#include "E3DRectangle.hpp"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../Mesh/E3DMesh.hpp"
#include "../Mesh/E3DMeshRender.h"
#include "../Light/E3DLight.hpp"

void ImplComponent()
{
	REGIST_CLASS(BoxCollider);
	REGIST_CLASS(SphereCollider);
	REGIST_CLASS(MeshCollider);
	REGIST_CLASS(RigidBody);
	REGIST_CLASS(CapsuleCollider);
	REGIST_CLASS(Box);
	REGIST_CLASS(Coordinate);
	REGIST_CLASS(E3DEngine::Rectangle);
	REGIST_CLASS(SkyBox);
	REGIST_CLASS(SkyDome);
	REGIST_CLASS(Sphere);
	REGIST_CLASS(Terrain);
	REGIST_CLASS(Mesh);
	REGIST_CLASS(Renderer);
	REGIST_CLASS(DirectionLight);
	REGIST_CLASS(PointLight);
	REGIST_CLASS(SpotLight);
	REGIST_CLASS(Camera);
}

DECLARE_CLASS_NAME(BoxCollider)
DECLARE_CLASS_NAME(SphereCollider)
DECLARE_CLASS_NAME(MeshCollider)
DECLARE_CLASS_NAME(RigidBody)
DECLARE_CLASS_NAME(CapsuleCollider)
DECLARE_CLASS_NAME(Box)
DECLARE_CLASS_NAME(Coordinate)
DECLARE_CLASS_NAME(E3DEngine::Rectangle)
DECLARE_CLASS_NAME(SkyBox)
DECLARE_CLASS_NAME(SkyDome)
DECLARE_CLASS_NAME(Sphere)
DECLARE_CLASS_NAME(Terrain)
DECLARE_CLASS_NAME(Mesh)
DECLARE_CLASS_NAME(Renderer)
DECLARE_CLASS_NAME(DirectionLight)
DECLARE_CLASS_NAME(SpotLight)
DECLARE_CLASS_NAME(PointLight)
DECLARE_CLASS_NAME(Camera)


E3DEngine::Component::Component()
{
	mGameObject = nullptr;
	Transform = nullptr;
	mNotStart = true;
	IsActive = true;
}

void E3DEngine::Component::OnCreate()
{
	Awake();
	OnEnable();
}

void E3DEngine::Component::OnCreateComplete()
{
	
}


void E3DEngine::Component::Awake()
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->Awake();
	}
}


void E3DEngine::Component::Start()
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->Start();
	}
}


void E3DEngine::Component::Update(float deltaTime)
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->Update(deltaTime);
	}
}


void E3DEngine::Component::LateUpdate(float deltaTime)
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->LateUpdate(deltaTime);
	}
}


void E3DEngine::Component::Destory()
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->Destory();
	}
}


void E3DEngine::Component::OnEnable()
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->OnEnable();
	}
}


void E3DEngine::Component::OnDisable()
{
	NOT_RUN_RETURN
	if (mBehaviour != nullptr)
	{
		mBehaviour->OnDisable();
	}
}

void E3DEngine::Component::OnCollisionEnter(GameObject* go)
{
	NOT_RUN_RETURN
	MonoObject * mObj = go->GetMonoBehaviour()->GetMonoObject();
	mBehaviour->CallMethod("OnCollisionEnter", (void**)&mObj);
}

void E3DEngine::Component::SetGameObject(GameObject *go)
{
	this->mGameObject = go;
	if (mBehaviour != nullptr)
	{
		mBehaviour->SetPropertyValue("gameObject", mGameObject->mBehaviour->GetMonoObject());
	}
}


E3DEngine::GameObject * E3DEngine::Component::GetGameObject()
{
	return mGameObject;
}

void E3DEngine::Component::SetPropertyValue(void* value)
{
	mBehaviour->SetPropertyValue("descPropertyValue", value);
}

void E3DEngine::Component::registProperty()
{
	MonoObject * mono_obj = GetMonoBehaviour()->GetMonoObject();
	MonoClass * mono_class = GetMonoBehaviour()->GetClass();
	MonoClassField * field = nullptr;
	void * iter = nullptr;
	while (field = mono_class_get_fields(mono_class, &iter))
	{
		const char * name = mono_field_get_name(field);
		MonoType *mono_type = mono_field_get_type(field);
		int type = mono_type_get_type(mono_type);

		int flags = mono_field_get_flags(field);
		if ((flags & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK) != FIELD_ATTRIBUTE_PUBLIC)
		{
			continue;
		}
		if (type == MONO_TYPE_I4) // int
		{
			m_propertyTypeMap[name] = FT_INT;
		}
		else if (type == MONO_TYPE_BOOLEAN)
		{
			m_propertyTypeMap[name] = FT_BOOLEAN;
		}
		else if (type == MONO_TYPE_STRING)
		{
			m_propertyTypeMap[name] = FT_STRING;
		}
		else if (type == MONO_TYPE_R4) // float
		{
			m_propertyTypeMap[name] = FT_FLOAT;
		}
		else if (type == MONO_TYPE_VALUETYPE)
		{
			// TODO
			MonoClass *k = mono_class_from_mono_type(mono_type);
		}
		else if (type == MONO_TYPE_CLASS)
		{
			// TODO
			MonoClass *k = mono_class_from_mono_type(mono_type);
		}
	}
}

std::string E3DEngine::Component::GetFieldValueStr(std::string fieldName)
{
	if (m_propertyTypeMap.find(fieldName) == m_propertyTypeMap.end())
	{
		return empty_string;
	}
	if (m_getMethodMap.find(fieldName) == m_getMethodMap.end())
	{
		return getMonoFieldValueStr(fieldName);
	}

	return getEngineFieldValueStr(fieldName);

}


std::string E3DEngine::Component::getEngineFieldValueStr(std::string fieldName)
{
	getValue get = (getValue)(m_getMethodMap[fieldName]);
	object value = get(this);
	DWORD type = m_propertyTypeMap[fieldName];
	if ((type & FT_BOOLEAN)== FT_BOOLEAN)
	{
		return object_cast<bool>(value) ? "true" : "false";
	}
	else if ((type & FT_FLOAT) == FT_FLOAT)
	{
		return Convert::ToString(object_cast<float>(value));
	}
	else if ((type & FT_INT)== FT_INT)
	{
		return Convert::ToString(object_cast<int>(value));
	}
	else if ((type & FT_STRING)== FT_STRING)
	{
		return object_cast<std::string>(value);
	}
	else if ((type & FT_VECTOR3)== FT_VECTOR3)
	{
		return Convert::ToString(object_cast<vec3f>(value));
	}
	else if ((type & FT_VECTOR2)== FT_VECTOR2)
	{
		return Convert::ToString(object_cast<vec2f>(value));
	}
	return empty_string;
}

void E3DEngine::Component::SetFieldValue(std::string fieldName, std::string fieldValueStr)
{
	if (m_propertyTypeMap.find(fieldName) == m_propertyTypeMap.end())
	{
		return;
	}

	if (m_setMethodMap.find(fieldName) == m_setMethodMap.end())
	{
		setMonoFieldVale(fieldName, fieldValueStr);
	}
	else
	{
		setEngineFieldValue(fieldName, fieldValueStr);
	}

}


void E3DEngine::Component::SetActive(bool active)
{
	IsActive = active;
}

void E3DEngine::Component::setEngineFieldValue(std::string fieldName, std::string fieldValueStr)
{
	setValue set = (setValue)(m_setMethodMap[fieldName]);
	DWORD type = m_propertyTypeMap[fieldName];
	if ((type & FT_STRING)== FT_STRING)
	{
		set(this, fieldValueStr);
	}
	else if ((type & FT_INT) == FT_INT)
	{
		set(this, Convert::ToInt(fieldValueStr));
	}
	else if ((type & FT_FLOAT) == FT_FLOAT)
	{
		set(this, Convert::ToFloat(fieldValueStr));
	}
	else if ((type &  FT_BOOLEAN) == FT_BOOLEAN)
	{
		set(this, Convert::ToBoolean(fieldValueStr));
	}
	else if ((type & FT_VECTOR3) == FT_VECTOR3)
	{
		set(this, Convert::ToVector3(fieldValueStr));
	}
	else if ((type & FT_VECTOR2) == FT_VECTOR2)
	{
		set(this, Convert::ToVector2(fieldValueStr));
	}
}

std::string E3DEngine::Component::getMonoFieldValueStr(std::string fieldName)
{
	void * field = mBehaviour->GetFieldValue(fieldName.c_str());
	if (field == nullptr)
	{
		return empty_string;
	}
	DWORD type = m_propertyTypeMap[fieldName];
	if ((type & FT_INT) == FT_INT) // int
	{
		int * p = ((int*)&field);
		return Convert::ToString(*p);
	}
	else if ((type & FT_BOOLEAN) == FT_BOOLEAN)
	{
		int * p = ((int*)&field);
		return (*p) ? "true" : "false";
	}
	else if ((type & FT_STRING) == FT_STRING)
	{
		return ((const char*)&field);
	}
	else if ((type & FT_FLOAT) == FT_FLOAT) // float
	{
		float * p = ((float*)&field);
		return Convert::ToString(*p);
	}
	return empty_string;
}

void E3DEngine::Component::setMonoFieldVale(std::string fieldName, std::string fieldValueStr)
{
	DWORD type = m_propertyTypeMap[fieldName];

	if ((type & FT_INT) == FT_INT) // int
	{
		int value = Convert::ToInt(fieldValueStr);
		mBehaviour->SetFieldValue(fieldName.c_str(), &value);
	}
	else if ((type & FT_BOOLEAN) == FT_BOOLEAN)
	{
		int  value = Convert::ToBoolean(fieldValueStr) ? 1 : 0;
		mBehaviour->SetFieldValue(fieldName.c_str(), &value);
	}
	else if ((type & FT_STRING) == FT_STRING)
	{
		MonoString * value = mono_string_new(MonoScriptManager::GetInstance().GetEngineDomain(), fieldValueStr.c_str());
		mBehaviour->SetFieldValue(fieldName.c_str(), value);
	}
	else if ((type & FT_FLOAT) == FT_FLOAT) // float
	{
		float value = Convert::ToFloat(fieldValueStr);
		mBehaviour->SetFieldValue(fieldName.c_str(), &value);
	}
	else if ((type & FT_VECTOR3) == FT_VECTOR3)
	{
		vec3f &&vec3 = Convert::ToVector3(fieldValueStr);
		MonoObject *vector3 = Convert::ToCSVector3(vec3);
		mBehaviour->SetFieldValue(fieldName.c_str(), vector3);
	}
}
