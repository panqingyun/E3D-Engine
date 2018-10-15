#pragma once
#include <Object/E3DGameObject.h>

#include "Transform.h"
#include "GameObject.h"

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
		TransformRef ^GetTransform();
		void SetActive(bool active);
		bool GetActive();
	private:
		TransformRef ^mTransform;
		GameObject * mGameObject;
		String ^ mName;

	};
}
#pragma unmanaged