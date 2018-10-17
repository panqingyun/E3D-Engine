
#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include <Object/E3DCoordinate.h>

#pragma managed
namespace E3DEngine
{
	GameObjectRef::GameObjectRef(GameObject *gameObject)
	{
		mChildList = gcnew List<GameObjectRef ^>();
		SetValue(gameObject);
	}

	System::String^ GameObjectRef::GetName()
	{
		return mName;
	}

	void GameObjectRef::SetValue(GameObject *gameObject)
	{
		mGameObject = gameObject;
		mID = gameObject->ID;
		mInnerID = gameObject->SceneInnerID;
		mTransform = gcnew TransformRef(gameObject->Transform);
		mName = gcnew String(gameObject->mName.c_str());
	}

	System::Collections::Generic::List<GameObjectRef^> ^ GameObjectRef::GetChilds()
	{
		if (mChildList->Count == 0)
		{
			mChildList = gcnew List<GameObjectRef ^>();
			std::map<UINT, GameObject*> childs = mGameObject->GetChilds();
			for (auto child : childs)
			{
				GameObjectRef ^ obj = gcnew GameObjectRef(child.second);
				child.second->TransChangeFun = TransformChange;
				mChildList->Add(obj);
			}
		}
		return mChildList;
	}

	E3DEngine::TransformRef ^ GameObjectRef::GetTransform()
	{
		return mTransform;
	}

	bool GameObjectRef::GetActive()
	{
		if (mGameObject == nullptr)
		{
			return false;
		}
		return mGameObject->IsActive;
	}

	int GameObjectRef::GetID()
	{
		return mID;
	}

	void GameObjectRef::Selected()
	{
		SceneManageRef::GetInstance()->GetCurScene()->ShowCoord(mGameObject->Transform);
	}

	int GameObjectRef::GetSceneInnerID()
	{
		return mInnerID;
	}

	void GameObjectRef::Reset()
	{
		mChildList->Clear();
	}

	void GameObjectRef::SetActive(bool active)
	{
		if (mGameObject == nullptr)
		{
			return;
		}

		mGameObject->SetActive(active);
	}

}
#pragma unmanaged