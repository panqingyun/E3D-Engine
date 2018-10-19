
#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include <Object/E3DCoordinate.h>

#pragma managed
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
namespace E3DEngine
{
	GameObjectRef::GameObjectRef(GameObject *gameObject)
	{
		mChildList = gcnew List<GameObjectRef ^>();
		mComponentList = gcnew List<ComponentRef ^>();
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
		getChilds();
		getComponents();
	}

	System::Collections::Generic::List<GameObjectRef^> ^ GameObjectRef::GetChilds()
	{
		return mChildList;
	}

	void GameObjectRef::getChilds()
	{
		mChildList->Clear();
		std::map<UINT, GameObject*> childs = mGameObject->GetChilds();
		for (auto child : childs)
		{
			GameObjectRef ^ obj = gcnew GameObjectRef(child.second);
			child.second->TransChangeFun = TransformChange;
			mChildList->Add(obj);
		}
	}

	void GameObjectRef::getComponents()
	{
		mComponentList->Clear();
		std::map<std::string, Component*> componentMap = mGameObject->GetAllComponents();
		for (auto &component : componentMap)
		{
			ComponentRef ^componentRef = gcnew ComponentRef(component.second);
			mComponentList->Add(componentRef);
		}
	}

	System::Collections::Generic::List<ComponentRef^>^ GameObjectRef::GetComponents()
	{
		return mComponentList;
	}

	E3DEngine::ComponentRef^ GameObjectRef::AddComponent(System::String^ fullName)
	{
		Component * component = mGameObject->AddComponent(marshal_as<std::string>(fullName));
		ComponentRef ^componentRef = gcnew ComponentRef(component);
		mComponentList->Add(componentRef);
		return componentRef;
	}

	void GameObjectRef::RemoveComponent(ComponentRef ^component)
	{
		mGameObject->RemoveComponent(component->GetComponentPtr());
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