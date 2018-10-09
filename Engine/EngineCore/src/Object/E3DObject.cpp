
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-1  PanQingyun. All rights reserved. *************************//

#include "E3DObject.h"
#include "../Source/EngineDelegate.h"
#include "E3DGameObject.h"

namespace E3DEngine
{
	Object::Object()
	{
		mObjectType = eT_Object;
		if (SceneManager::GetCurrentScene() != nullptr)
		{
			ID = SceneManager::GetCurrentScene()->GenObjectID();
		}
		//ADD_IN_SCENE(this);
		mBehaviour = new MonoBehaviour;
	}

	Object::~Object()
	{
		SAFE_DELETE(mBehaviour);
	}

	void Object::Update(float deltaTime)
	{		
		
	}

	void Object::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Object);
		setBehaviourDefaultValue();
	}


	void Object::SetMonoObject(MonoObject * monoObject)
	{
		if (mBehaviour->GetMonoObject() != nullptr)
		{
			return;
		}
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		mBehaviour->SetMonoObject(monoObject);
		setBehaviourDefaultValue();
	}


	std::string Object::GetName()
	{
		return mName;
	}

	void Object::setBehaviourDefaultValue()
	{		
		mBehaviour->SetFieldValue(CPP_OBJ_PTR_NAME, this);
	}

	MonoBehaviour * Object::GetMonoBehaviour()
	{
		return mBehaviour;
	}

}