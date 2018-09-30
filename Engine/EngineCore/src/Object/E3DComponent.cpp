
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-2-8  PanQingyun. All rights reserved. *************************//

#include "../Object/E3DComponent.hpp"
#include "../Object/E3DGameObject.h"


E3DEngine::Component::Component()
{
	mGameObject = nullptr;
	Transform = nullptr;
	mNotStart = true;
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
	if (mBehaviour != nullptr)
	{
		mBehaviour->Awake();
	}
}


void E3DEngine::Component::Start()
{
	if (mBehaviour != nullptr)
	{
		mBehaviour->Start();
	}
}


void E3DEngine::Component::Update(float deltaTime)
{
	if (mBehaviour != nullptr)
	{
		mBehaviour->Update(deltaTime);
	}
}


void E3DEngine::Component::LateUpdate(float deltaTime)
{
	if (mBehaviour != nullptr)
	{
		mBehaviour->LateUpdate(deltaTime);
	}
}


void E3DEngine::Component::Destory()
{
	if (mBehaviour != nullptr)
	{
		mBehaviour->Destory();
	}
}


void E3DEngine::Component::OnEnable()
{
	if (mBehaviour != nullptr)
	{
		mBehaviour->OnEnable();
	}
}


void E3DEngine::Component::OnDisable()
{
	if (mBehaviour != nullptr)
	{
		mBehaviour->OnDisable();
	}
}

void E3DEngine::Component::OnCollisionEnter(GameObject* go)
{
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

}
