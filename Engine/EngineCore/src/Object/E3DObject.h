
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

	const std::string NM_GameObject = "GameObject";
	const std::string TP_Camera = "Camera";
	const std::string TP_DLight = "DirectionLight";
	const std::string TP_PLight = "PointLight";
	const std::string TP_SkyBox = "SkyBox";
	const std::string TP_Mesh = "Mesh";
	const std::string TP_Particle = "Particle";
	const std::string TP_Cube = "Cube";
	const std::string TP_Sphere = "Sphere";
	const std::string TP_Empty = "Empty";
	const std::string _typeName = "Type";
	const std::string TP_Terrain = "Terrain";
	const std::string TP_Prefab = "Prefab";
	const std::string TP_SkyDome = "SkyDome";
	const std::string _ParticleGroupName = "<particle-group>";


#define ADD_IN_SCENE(obj)\
	if (SceneManager::GetCurrentScene() != nullptr)\
	{\
		SceneManager::GetCurrentScene()->AddObject(obj);\
	}

#define E3D_NAME_SPACE "E3DEngine"

	class CTransform;
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
		std::string		mTypeName;
		std::string		mName;
		ObjectType		mType;
		MonoBehaviour * mBehaviour;
		std::string		mConfigPath;
		int				mConfigID;
	};
}

#endif // !__ENGINE_3D_NODE_H__
