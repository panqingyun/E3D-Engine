
#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"

#pragma managed
namespace E3DEngine
{
	GameObjectRef::GameObjectRef(GameObject *gameObject)
	{
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
		mTransform = gcnew TransformRef(gameObject->Transform);
		mName = gcnew String(gameObject->mName.c_str());
	}

	System::Collections::Generic::List<GameObjectRef^> ^ GameObjectRef::GetChilds()
	{
		if (mChildList == nullptr)
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