
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-2-8  PanQingyun. All rights reserved. *************************//

#include "../Object/E3DComponent.hpp"
#include "../Object/E3DGameObject.h"

void E3DEngine::Component::OnCollisionEnter(GameObject* go)
{
	MonoObject * mObj = go->GetMonoBehaviour()->GetMonoObject();
	m_pBehaviour->CallMethod("OnCollisionEnter", (void**)&mObj);
}
