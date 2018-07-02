
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-1  PanQingyun. All rights reserved. *************************//

#include "E3DObject.h"
#include "../Source/EngineDelegate.h"
#include "E3DGameObject.h"

namespace E3DEngine
{
	Object::Object()
	{
		NodeType = eT_Object;
		ID = EngineDelegate::GetInstance().GenObjectID();
		//ADD_IN_SCENE(this);
		m_pBehaviour = new MonoBehaviour;
	}

	Object::~Object()
	{
		SAFE_DELETE(m_pBehaviour);
	}

	void Object::Update(float deltaTime)
	{		
		
	}

	void Object::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Object);
		setBehaviourDefaultValue();
	}

	void Object::setBehaviourDefaultValue()
	{		
		m_pBehaviour->SetFieldValue(CPP_OBJ_PTR_NAME, this);
	}

	MonoBehaviour * Object::GetMonoBehaviour()
	{
		return m_pBehaviour;
	}

}