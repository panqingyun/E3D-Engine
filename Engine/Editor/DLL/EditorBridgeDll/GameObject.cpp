
#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include <Component/E3DCoordinate.h>

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

	GameObjectRef::GameObjectRef()
	{
		mGameObject = new GameObject();
		mGameObject->CreateBehaviour();
		mGameObject->SetLayerMask(1);
		mGameObject->SetActive(true);
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
		mColor = gcnew Vector4(gameObject->Color.r, gameObject->Color.g, gameObject->Color.b, gameObject->Color.a);
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
		std::list<GameObject*> childs = mGameObject->GetChilds();
		for (auto child : childs)
		{
			GameObjectRef ^ obj = gcnew GameObjectRef(child);
			child->TransChangeFun = TransformChange;
			mChildList->Add(obj);
		}
	}

	void GameObjectRef::getComponents()
	{
		mComponentList->Clear();
		std::unordered_map<std::string, Component*> componentMap = mGameObject->GetAllComponents();
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
		if (GameObjectSelected != nullptr)
		{
			GameObjectSelected(this, nullptr);
		}
	}

	void GameObjectRef::Reset()
	{
		mChildList->Clear();
	}

	bool GameObjectRef::GetHasComponent(String ^fullName)
	{
		if (mGameObject->GetAllComponents().find(marshal_as<std::string>(fullName)) == mGameObject->GetAllComponents().end())
		{
			return false;
		}
		return true;
	}

	void GameObjectRef::Update(float deltaTime)
	{
		if (mGameObject != nullptr)
		{
			mGameObject->Update(deltaTime);
		}
	}

	void GameObjectRef::AfterUpdate(float deltaTime)
	{
		if (mGameObject != nullptr)
		{
			mGameObject->AfterUpdate(deltaTime);
		}
	}

	E3DEngine::GameObject * GameObjectRef::GetGameObjectPtr()
	{
		return mGameObject;
	}

	E3DEngine::Vector4^ GameObjectRef::GetColor()
	{
		return mColor;
	}

	void GameObjectRef::SetColor(Vector4 ^color)
	{
		mColor->SetValue(color->x, color->y, color->z, color->w);
		mGameObject->SetColor(Color4(color->x, color->y, color->z, color->w));
	}

	int GameObjectRef::GetFlag()
	{
		return mGameObject->Flag;
	}

	void GameObjectRef::SetParent(GameObjectRef ^gameObject)
	{
		mGameObject->SetParent(gameObject->GetGameObjectPtr());
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