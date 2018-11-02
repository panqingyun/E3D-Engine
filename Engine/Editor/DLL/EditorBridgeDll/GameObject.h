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
		static int TP_NONE = 0;
		static int TP_Camera = 1;
		static int TP_DLight = 2;
		static int TP_PLight = 3;
		static int TP_SkyBox = 4;
		static int TP_Mesh = 5;
		static int TP_Particle = 6;
		static int TP_Cube = 7;
		static int TP_Sphere = 8;
		static int TP_Empty = 9;
		static int TP_Terrain = 10;
		static int TP_Prefab = 11;
		static int TP_SkyDome = 12;
	};

	public ref class GameObjectRef
	{
	public:
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
		int GetSceneInnerID();
		void Reset();
		bool GetHasComponent(String ^fullName);
		void Update(float deltaTime);
		void AfterUpdate(float deltaTime);
		GameObject * GetGameObjectPtr();
		Vector4 ^GetColor();
		void SetColor(Vector4 ^color);

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
		int mInnerID;
		Vector4 ^mColor;
	};
}
#pragma unmanaged