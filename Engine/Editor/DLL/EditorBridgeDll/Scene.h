#pragma once
#include <Scene/E3DSceneManager.hpp>
#include "GameObject.h"

#pragma managed
using namespace System;

namespace E3DEngine
{
	void TransformChange(int ID);
	public ref class SceneRef
	{
	public:
		SceneRef(Scene *scene);
		GameObjectRef ^ GetRootObject();
		void SetValue(Scene *scene);
		String ^GetName();
		String ^GetScenePath();
		void SaveScene(String ^path);
		GameObjectRef ^GetGameObject(int ID);

	private:
		GameObjectRef ^ findGameObject(List<GameObjectRef ^>^ childList, int id);

	private:
		Scene *mScene;
		GameObjectRef ^mRootObject;
	};

	public ref class SceneManageRef
	{
	private:
		SceneManageRef()
		{

		}
		static SceneManageRef^ _ins;
	public:
		static SceneManageRef^ GetInstance();
		SceneRef^ GetCurScene();
		SceneRef^ LoadScene(String^ path);
	private:
		SceneRef ^ mCurScene;
	};
}

#pragma unmanaged