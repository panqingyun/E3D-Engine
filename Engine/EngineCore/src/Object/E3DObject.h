
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

	enum SceneObjectType
	{
		TP_NONE			= 0,
		TP_Camera		= 1,
		TP_Particle		= 2,
		TP_GameObject	= 3, 
		TP_Prefab		= 4,
	};

	const std::string NM_GameObject = "GameObject";
	const std::string _ParticleGroupName = "<particle-group>";
	const std::string _TypeName = "Type";


#define ADD_IN_SCENE(obj)\
	if (SceneManager::GetCurrentScene() != nullptr)\
	{\
		SceneManager::GetCurrentScene()->AddObject(obj);\
	}

#define E3D_NAME_SPACE "E3DEngine"

	class E3D_EXPORT_DLL Object : public Ref
	{
	public:
		Object();
		virtual ~Object();
	public:
		virtual void Update(float deltaTime);
		MonoBehaviour * GetMonoBehaviour();
		virtual void CreateBehaviour();
		virtual void SetMonoObject(MonoObject * monoObject);

		std::string GetName();
	protected:
		virtual void setBehaviourDefaultValue();
	public:
		unsigned int	ID;
		std::string		mName;
		std::string		mTypeName;
		ObjectType		mObjectType;
		MonoBehaviour * mBehaviour;
		std::string		mConfigPath;
		int				mConfigID;
	};
}

#endif // !__ENGINE_3D_NODE_H__
