#include "Scene.h"
#include "stdafx.h"

#pragma managed
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
using namespace System;
namespace E3DEngine
{

	SceneRef::SceneRef(Scene *scene)
	{
		SetValue(scene);
	}

	String^ SceneRef::GetName()
	{
		return gcnew String(mScene->mName.c_str());
	}

	E3DEngine::GameObjectRef ^ SceneRef::GetRootObject()
	{
		return mRootObject;
	}

	void SceneRef::SetValue(Scene *scene)
	{
		mScene = scene;
		if (mRootObject == nullptr)
		{
			mRootObject = gcnew GameObjectRef(scene->GetRootObject());
		}
		else
		{
			mRootObject->SetValue(scene->GetRootObject());
		}
	}

	E3DEngine::SceneManageRef^ SceneManageRef::GetInstance()
	{
		if (_ins == nullptr)
		{
			_ins = gcnew SceneManageRef();
		}
		return _ins;
	}

	E3DEngine::SceneRef^ SceneManageRef::GetCurScene()
	{
		Scene *scene = SceneManager::GetInstance().GetCurrentScene();
		if (mCurScene == nullptr)
		{
			mCurScene = gcnew SceneRef(scene);
		}
		else
		{
			mCurScene->SetValue(scene);
		}
		return mCurScene;
	}

	E3DEngine::SceneRef^ SceneManageRef::LoadScene(String^ path)
	{
		std::string InputData = marshal_as<std::string>(path);
		Scene *scene = SceneManager::GetInstance().LoadScene(InputData);
		if (mCurScene == nullptr)
		{
			mCurScene = gcnew SceneRef(scene);
		}
		else
		{
			mCurScene->SetValue(scene);
		}

		return mCurScene;
	}
}

#pragma unmanaged

