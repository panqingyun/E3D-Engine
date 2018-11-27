//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-21 PanQingyun. All rights reserved. *************************//
#include "E3DLight.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Source/E3DDebug.h"
#include "../Object/E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Source/Application.h"

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

	void PointLight::MakeShadow()
	{
		// TODO 点光源创建透视投影摄像机

	}

	DirectionLight::DirectionLight()
	{
		Type = eDIRECTION_LIGHT;
		CREATE_BEHAVIOUR(DirectionLight);
	}

	void DirectionLight::MakeShadow()
	{
		CreateShadow = true; 
		// 平行光 创建正交投影摄像机
		GameObject *gameObject = new GameObject();
		gameObject->CreateBehaviour();
		gameObject->SetLayerMask(-1 & ~LD_SKYBOX & ~LD_OBJECT_COORD & ~LD_COORD & ~LD_NOSHADOW);
		shadowCamera = (Camera*)gameObject->AddComponent("E3DEngine.Camera");
		shadowCamera->Perspective = false;
		shadowCamera->Pos = Transform->Position + CenterPosition;
		shadowCamera->Target = CenterPosition;
		shadowCamera->Near = 1;
		shadowCamera->Far = 1000;
		shadowCamera->Size = Range;
		shadowCamera->SetActive(true);
		//shadowCamera = new E3DEngine::Camera(Transform->Position + CenterPosition, CenterPosition, vec3f(0, 1, 0), -halfSize, halfSize, -halfSize, halfSize, 1, 1000);
		shadowCamera->OnCreate();
		shadowCamera->OnCreateComplete();
		TextureData tData;
		tData.width = TextureSize;
		tData.height = TextureSize;
		tData.target = RENDER_DEPTH;
		Render2Texture *rtt = GetRenderSystem()->GetTextureDataManager()->CreateRender2TextureSingleThread(&tData);
		shadowCamera->SetRenderTexture(rtt);
		shadowCamera->SetClearType(eCT_Depth);
		shadowCamera->SetIsShadowCamera();
		shadowCamera->mName = "ShadowCamera";
		gameObject->Flag |= (DONT_SAVE | HIDE_IN_HIERARCHY);
		ADD_IN_SCENE(gameObject);
	}

	void DirectionLight::OnCreateComplete()
	{
		Light::OnCreateComplete();
		SetDirection(mGameObject->Transform->Position);
		SceneManager::GetCurrentScene()->AddLight(this);
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

	void SpotLight::MakeShadow()
	{
		// 追光 透视投影摄像机
	}

	void Light::setBehaviourDefaultValue()
	{
		/*MonoObject * color = Convert::ToCSVector4(vec4f(Color.r, Color.g,Color.b,Color.a));
		mBehaviour->SetFieldValue("Color", color);
		TRANSFER_FIELD_VALUE(Intensity);*/
		//GameObject::setBehaviourDefaultValue();
	}

	void Light::OnCreateComplete()
	{
		if (CreateShadow)
		{
			MakeShadow();
		}
		SceneManager::GetCurrentScene()->AddLight(this);
	}

	E3DEngine::Camera * Light::GetShadowCamera()
	{
		return shadowCamera;
	}
}
