#pragma once
#include <Scene/E3DSceneManager.hpp>
#include "GameObject.h"
#include <Object/E3DCoordinate.h>

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
		void ShowCoord();
		void Loaded();
		void SetSelectObject(GameObjectRef ^obj);
		GameObjectRef ^GetCurSelObject();
		void Update(float deltaTime);
		void AfterUpdate(float deltaTime);

	private:
		GameObjectRef ^ findGameObject(List<GameObjectRef ^>^ childList, int id);
		void createCoordinate(std::string materilPath, int selectID);

	private:
		Scene *mScene;
		GameObjectRef ^mRootObject;
		Coordinate *mObjectCoord;
		GameObjectRef ^mCurSelObject;
	};

	public ref class SceneManageRef
	{
	private:
		SceneManageRef();
		static SceneManageRef^ _ins;
	public:
		static SceneManageRef^ GetInstance();
		SceneRef^ GetCurScene();
		SceneRef^ LoadScene(String^ path);
		void LoadEditorObject();
		void Update(float deltaTime);
		void OnFrameSizeChange();
		Camera *GetEditorMainCamera();
		Camera *GetLookCoordCamera();
	private:
		void createCoord();

	private:

		Camera *mEditorCamera;
		Camera *mCoordCamera;
		Camera *mLookCoordCamera;
		Scene *mDefaultScene;
		Prefab *mCoordPrefab; 
		Rectangle *mCoordRt;
		SceneRef ^ mCurScene;
	};
}

#pragma unmanaged