//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-21 PanQingyun. All rights reserved. *************************//
#include "E3DLight.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Source/E3DDebug.h"
#include "../Object/E3DTransform.hpp"

namespace E3DEngine
{
	PointLight::PointLight()
	{
		Range = 0;
		Type = ePOINT_LIGHT;
		CREATE_BEHAVIOUR(PointLight);
		TRANSFER_FIELD_VALUE(Range);
		Light::setBehaviourDefaultValue();
	}

	void PointLight::CreateShadow()
	{
		// TODO 点光源创建透视投影摄像机

	}

	DirectionLight::DirectionLight()
	{
		Type = eDIRECTION_LIGHT;
		CREATE_BEHAVIOUR(DirectionLight);
	}

	void DirectionLight::CreateShadow()
	{
		// 平行光 创建正交投影摄像机
	}


	void DirectionLight::CreateComplete()
	{
		SetDirection(Transform->Position);
	}

	void DirectionLight::TransformChange()
	{
		mDirection = Transform->Rotation * mDirection;
	}

	void DirectionLight::SetDirection(vec3f dir)
	{
		mDirection = dir;
	}

	vvision::vec3f &DirectionLight::GetDirection()
	{
		return mDirection;
	}

	SpotLight::SpotLight()
	{
		Type = ePOINT_LIGHT;
		CREATE_BEHAVIOUR(SpotLight);
		TRANSFER_FIELD_VALUE(Range);
		TRANSFER_FIELD_VALUE(SpotAngle);
		Light::setBehaviourDefaultValue();
	}

	void SpotLight::CreateShadow()
	{
		// 追光 透视投影摄像机
	}

	Light * Light::Create(LightType type)
	{
		Light * light = nullptr;
		switch (type)
		{
		case eDIRECTION_LIGHT:
			if (SceneManager::GetCurrentScene()->GetDirectionalLight() != nullptr)
			{
				Debug::Log(ell_Warning, "there must be only one direction light in the same scene");
				return nullptr;
			}
			light = new DirectionLight;
			break;
		case ePOINT_LIGHT:
			light = new PointLight;
			break;
		case eSPOT_LIGHT:
			light = new SpotLight;
			break;
		default:
			break;
		}
		SceneManager::GetCurrentScene()->AddLight(light);
		//ADD_IN_SCENE(light);
		return light;
	}

	void Light::setBehaviourDefaultValue()
	{
		MonoObject * color = Convert::ToCSVector4(vec4f(Color.r, Color.g,Color.b,Color.a));
		mBehaviour->SetFieldValue("Color", color);
		TRANSFER_FIELD_VALUE(Intensity);
		GameObject::setBehaviourDefaultValue();
	}
}
