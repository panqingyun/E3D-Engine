//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-21 PanQingyun. All rights reserved. *************************//
#include "E3DLight.hpp"
#include "../Scene/E3DSceneManager.hpp"

namespace E3DEngine
{
	PointLight::PointLight()
	{
		Range = 0;
		CreateBehaviour();
	}

	void PointLight::CreateBehaviour()
	{
		Type = ePOINT_LIGHT;
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(PointLight);
		setBehaviourDefaultValue();
	}

	void PointLight::setBehaviourDefaultValue()
	{
		Light::setBehaviourDefaultValue();
		TRANSFER_FIELD_VALUE(Range);
	}

	void PointLight::CreateShadow()
	{
		// TODO 点光源创建透视投影摄像机

	}

	DirectionLight::DirectionLight()
	{
		Type = eDIRECTION_LIGHT;
		CreateBehaviour();
	}

	void DirectionLight::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(DirectionLight);
		setBehaviourDefaultValue();
	}

	void DirectionLight::setBehaviourDefaultValue()
	{
		Light::setBehaviourDefaultValue();
	}

	void DirectionLight::CreateShadow()
	{
		// 平行光 创建正交投影摄像机
	}

	SpotLight::SpotLight()
	{
		Type = ePOINT_LIGHT;
		CreateBehaviour();
	}

	void SpotLight::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(SpotLight);
		setBehaviourDefaultValue();
	}

	void SpotLight::setBehaviourDefaultValue()
	{
		Light::setBehaviourDefaultValue();
		TRANSFER_FIELD_VALUE(Range);
		TRANSFER_FIELD_VALUE(SpotAngle);
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
			if (SceneManager::GetInstance().GetCurrentScene()->GetDirectionalLight() != nullptr)
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
		SceneManager::GetInstance().GetCurrentScene()->AddLight(light);
		//ADD_IN_SCENE(light);
		return light;
	}

	void Light::setBehaviourDefaultValue()
	{
		MonoObject * color = Convert::ToCSVector4(Color);
		mBehaviour->SetFieldValue("Color", color);
		TRANSFER_FIELD_VALUE(Intensity);
		GameObject::setBehaviourDefaultValue();
	}
}
