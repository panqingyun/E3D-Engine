//
//  Light.cpp
//  Created by 潘庆云 on 2017/3/21.
//

#include "E3DLight.hpp"
#include "../Scene/E3DSceneManager.hpp"

namespace E3DEngine
{
	PointLight::PointLight()
	{
		CreateBehaviour();
	}

	void PointLight::CreateBehaviour()
	{
		Type = ePOINT_LIGHT;
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(PointLight);
		setBehaviourDefaultValue();
	}

	void PointLight::setBehaviourDefaultValue()
	{
		Light::setBehaviourDefaultValue();
		TRANSFER_FIELD_VALUE(Range);
	}

	DirectionLight::DirectionLight()
	{
		Type = eDIRECTION_LIGHT;
		CreateBehaviour();
	}

	void DirectionLight::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(DirectionLight);
		setBehaviourDefaultValue();
	}

	void DirectionLight::setBehaviourDefaultValue()
	{
		Light::setBehaviourDefaultValue();
	}

	SpotLight::SpotLight()
	{
		Type = ePOINT_LIGHT;
		CreateBehaviour();
	}

	void SpotLight::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(SpotLight);
		setBehaviourDefaultValue();
	}

	void SpotLight::setBehaviourDefaultValue()
	{
		Light::setBehaviourDefaultValue();
		TRANSFER_FIELD_VALUE(Range);
		TRANSFER_FIELD_VALUE(SpotAngle);
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
		m_pBehaviour->SetFieldValue("Color", color);
		TRANSFER_FIELD_VALUE(Intensity);
		GameObject::setBehaviourDefaultValue();
	}
}
