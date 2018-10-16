#include "Scene.h"
#include "stdafx.h"

#pragma managed
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
using namespace System;
namespace E3DEngine
{
	void TransformChange(int ID)
	{
		GameObjectRef ^refObj = SceneManageRef::GetInstance()->GetCurScene()->GetGameObject(ID);
		if (refObj == nullptr)
		{
			return;
		}
		if (refObj->TransformChangeHandle != nullptr)
		{
			refObj->TransformChangeHandle(refObj, nullptr);
		}
	}

	SceneRef::SceneRef(Scene *scene)
	{
		SetValue(scene);
	}

	String^ SceneRef::GetName()
	{
		return gcnew String(mScene->mName.c_str());
	}

	System::String ^ SceneRef::GetScenePath()
	{
		return gcnew String(mScene->GetScenePath().c_str());
	}

	void SceneRef::SaveScene(String ^path)
	{
		if (mScene->GetScenePath() == "")
		{
			mScene->SetScenePath(marshal_as<std::string>(path));
		}
		mScene->Save();
	}

	E3DEngine::GameObjectRef ^ SceneRef::GetGameObject(int ID)
	{
		List<GameObjectRef ^>^ childList = mRootObject->GetChilds();
		return findGameObject(childList, ID);
	}

	GameObjectRef ^ SceneRef::findGameObject(List<GameObjectRef ^>^ childList, int ID)
	{
		GameObjectRef ^ retObj = nullptr;
		for (int i = 0; i < childList->Count; i++)
		{
			if (childList[i]->GetID() == ID)
			{
				retObj = childList[i];
			}
			else
			{
				retObj = findGameObject(childList[i]->GetChilds(), ID);
			}

			if (retObj != nullptr)
			{
				break;
			}
		}
		return retObj;
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
		if (scene == nullptr)
		{
			return nullptr;
		}
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

