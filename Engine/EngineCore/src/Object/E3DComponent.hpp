//
//  E3DComponent.hpp
//  Created by 潘庆云 on 2017/2/8.
//

#ifndef E3DComponent_hpp
#define E3DComponent_hpp

#include "../Source/Interface.h"
#include "../Mono/MonoScriptManager.h"
#include "../Object/E3DObject.h"

namespace E3DEngine
{
    class GameObject;
	class CTransform;
	// 组件类， 目的是方便拓展， 可以挂在Object上
    class Component extends Object
    {
    public:
		Component()
		{
			gameObject = nullptr;
			Transform = nullptr;
		}

		virtual void Awake()
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Awake();
			}
		}
        virtual void Start()
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Start();
			}
        }
        virtual void Update(float deltaTime)
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Update(deltaTime);
			}
        }
        virtual void Destory()
        {
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Destory();
			}
        }
		virtual void OnCollisionEnter(GameObject* go);
    public:
        GameObject *	gameObject;
		std::string 	_Tag;
		CTransform *    Transform;
    };
}

#endif /* CComponent_hpp */
