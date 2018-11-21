#pragma once
#include <Object/E3DGameObject.h>

#include "Transform.h"
#include "GameObject.h"
#include "Component.h"

#pragma managed
using namespace System;
using namespace System::Collections::Generic;

namespace E3DEngine
{
	public ref class GameObjectType
	{
	public:
		static int TP_NONE			= 0;
		static int TP_Camera		= 1;
		static int TP_Particle		= 2;
		static int TP_GameObject	= 3;
		static int TP_Prefab		= 4;
	};		

	public ref class GameObjectFlag
	{
	public:
		static int  DONT_SAVE			= 1 << 0;
		static int 	HIDE_IN_HIERARCHY	= 1 << 1;
	};

	public ref class GameObjectRef
	{
	public:
		GameObjectRef();
		GameObjectRef(GameObject *gameObject);
		String^ GetName();
		void SetValue(GameObject *gameObject);
		List<GameObjectRef^>^ GetChilds();
		List<ComponentRef^>^ GetComponents();
		ComponentRef^ AddComponent(System::String^ fullName);
		void RemoveComponent(ComponentRef ^component);
		TransformRef ^GetTransform();
		void SetActive(bool active);
		bool GetActive();
		int GetID();
		void Selected();
		void Reset();
		bool GetHasComponent(String ^fullName);
		void Update(float deltaTime);
		void AfterUpdate(float deltaTime);
		GameObject * GetGameObjectPtr();
		Vector4 ^GetColor();
		void SetColor(Vector4 ^color);
		int GetFlag();
		void SetParent(GameObjectRef ^gameObject);

	public:
		System::EventHandler  ^TransformChangeHandle;

	private:
		void getChilds();
		void getComponents();

	private:
		TransformRef ^mTransform;
		GameObject * mGameObject;
		String ^ mName;
		List<GameObjectRef ^>^ mChildList;
		List<ComponentRef^>^ mComponentList;
		int mID;
		Vector4 ^mColor;
	};
}
#pragma unmanaged