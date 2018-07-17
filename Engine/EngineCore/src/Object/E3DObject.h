
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-1  PanQingyun. All rights reserved. *************************//

#ifndef __ENGINE_3D_NODE_H__
#define __ENGINE_3D_NODE_H__
#include "../Source/Interface.h"

class MonoBehaviour;
namespace E3DEngine
{
	typedef enum
	{
		eT_GameObject,
		eT_Scene,
		eT_Object,
		eT_Camera,
		eT_RenderObject
	} ObjectType;

#define ADD_IN_SCENE(obj)\
	if (SceneManager::GetInstance().GetCurrentScene() != nullptr)\
	{\
		SceneManager::GetInstance().GetCurrentScene()->AddChild(obj);\
	}

#define E3D_NAME_SPACE "E3DEngine"

	class CTransform;
	class Object : public Ref
	{
	public:
		Object();
		virtual ~Object();
	public:
		virtual void Update(float deltaTime);
		MonoBehaviour * GetMonoBehaviour();
		virtual void CreateBehaviour();
		virtual void SetMonoObject(MonoObject * monoObject);
	protected:
		virtual void setBehaviourDefaultValue();
	public:
		unsigned int	ID;
		std::string		mTypeName;
		std::string		mName;
		ObjectType		mType;
		MonoBehaviour * mBehaviour;
	};
}

#endif // !__ENGINE_3D_NODE_H__
