//
//  CComponent.cpp
//
//  Created by 潘庆云 on 2017/2/8.
//

#include "../Object/E3DComponent.hpp"
#include "../Object/E3DGameObject.h"

void E3DEngine::Component::OnCollisionEnter(GameObject* go)
{
	MonoObject * mObj = go->GetMonoBehaviour()->GetMonoObject();
	m_pBehaviour->CallMethod("OnCollisionEnter", (void**)&mObj);
}
