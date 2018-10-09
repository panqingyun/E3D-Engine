
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
		TP_NONE = 0,
		TP_Camera = 1,
		TP_DLight = 2,
		TP_PLight = 3,
		TP_SkyBox = 4,
		TP_Mesh	  = 5,
		TP_Particle = 6,
		TP_Cube = 7,
		TP_Sphere = 8,
		TP_Empty = 9,
		TP_Terrain  = 10,
		TP_Prefab = 11,
		TP_SkyDome = 12,
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
		unsigned int	mSceneObjectType;
		std::string		mName;
		ObjectType		mObjectType;
		MonoBehaviour * mBehaviour;
		std::string		mConfigPath;
		int				mConfigID;
	};
}

#endif // !__ENGINE_3D_NODE_H__
