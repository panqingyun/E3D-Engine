/************************************************************************/
/* Node                                                                  
/* Create by PanQingyun
/* 2017-9-30
/************************************************************************/
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
	protected:
		virtual void setBehaviourDefaultValue();
	public:
		unsigned int			ID;
		std::string		TypeName;
		std::string		Name;
		ObjectType		NodeType;
		MonoBehaviour * m_pBehaviour;
	};
}

#endif // !__ENGINE_3D_NODE_H__
