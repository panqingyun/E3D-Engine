
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-2-8  PanQingyun. All rights reserved. *************************//

#ifndef E3DComponent_hpp
#define E3DComponent_hpp

#include "../Source/Interface.h"
#include "../Mono/MonoScriptManager.h"
#include "../Object/E3DObject.h"

namespace E3DEngine
{
    class GameObject;
	class CTransform;
	// 组件类， 目的是方便拓展， 可以挂在GameObject上
    class E3D_EXPORT_DLL Component : public Object
    {
    public:
		Component();

		virtual void OnCreate();
		virtual void OnCreateComplete();
		virtual void Awake();
        virtual void Start();
        virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
        virtual void Destory();
		virtual void OnEnable();
		virtual void OnDisable();
		virtual void OnCollisionEnter(GameObject* go);
		virtual void SetGameObject(GameObject *go);
		GameObject * GetGameObject();
		virtual void SetPropertyValue(void* value);

    public:
        GameObject *	mGameObject;
		std::string 	_Tag;
		CTransform *    Transform;

	public:
		bool			mNotStart;
    };
}

#endif /* CComponent_hpp */
