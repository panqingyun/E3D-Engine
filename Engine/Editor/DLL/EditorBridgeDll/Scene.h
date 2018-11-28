#pragma once
#include <Scene/E3DSceneManager.hpp>
#include "GameObject.h"
#include <Component/E3DCoordinate.h>

#pragma managed
using namespace System;

namespace E3DEngine
{
	public ref class ObjectMoveDirection
	{
	public:
		static int NONE = 0;
		static int HORZITAL = 1;
		static int VERTICAL = 2;
	};

	void TransformChange(int ID);
	void SceneDetory();
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

		void showCameraView();

		GameObjectRef ^GetCurSelObject();
		void Update(float deltaTime);
		void AfterUpdate(float deltaTime);
		void PickObject(float x, float y);
		void OnMouseDown(int buttonID, float x, float y);
		void OnMouseUp(int mouseButtonID, float xPos, float yPos);
		void OnMouseMove(float xPos, float yPos);
		void OnKeyDown(char key);
		void OnKeyUp(char key);
	private:
		GameObjectRef ^ findGameObject(List<GameObjectRef ^>^ childList, int id);
		void createCoordinate(std::string materilPath, int selectID);

	private:
		Scene *mScene;
		GameObjectRef ^mRootObject;
		Coordinate *mObjectCoord;
		GameObjectRef ^mCurSelObject;
		bool mMouseIsPress;
		Vector2 ^mLastPos;
		char mCurKey;
		Rectangle *mCameraView;
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
		void SetRunPath(String ^path);
		void DestoryScene();
		void SetMoveDirection(int dir);
		int GetMoveDirection();
		String ^GetEditorRunPath();
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
		String^  mEditorPath;
		int mDirection;
	};
}

#pragma unmanaged