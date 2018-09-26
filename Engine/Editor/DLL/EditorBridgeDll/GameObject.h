#pragma once
#include <Object/E3DGameObject.h>

#include "Transform.h"
#include "GameObject.h"

#pragma managed
using namespace System;
using namespace System::Collections::Generic;

namespace E3DEngine
{
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