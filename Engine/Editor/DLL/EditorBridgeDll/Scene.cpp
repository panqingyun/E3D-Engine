#include "Scene.h"
#include "stdafx.h"
#include "Source/E3DVertexManager.h"
#include <Scene/E3DSceneLoader.h>

#pragma managed
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
using namespace System;
namespace E3DEngine
{
	const int gCoordLayer = 31;
	const int gLookCoordLayer = 30;
	const int objectCoordLayer = 29;

	void TransformChange(int ID)
	{
		GameObjectRef ^refObj = SceneManageRef::GetInstance()->GetCurScene()->GetCurSelObject();
		if (refObj == nullptr || ID != refObj->GetGameObjectPtr()->ID)
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
		mCurSelObject = nullptr;
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

	void SceneRef::ShowCoord()
	{
		if (mObjectCoord == nullptr)
		{
			createCoordinate("../Data/Material/coordinate.material", 1);
		}
		mObjectCoord->Transform = mCurSelObject->GetTransform()->GetTransformPtr();
	}

	void SceneRef::Loaded()
	{
		mCurSelObject = nullptr;
		mObjectCoord = nullptr;
		mRootObject->Reset();
	}

	void SceneRef::SetSelectObject(GameObjectRef ^obj)
	{
		mCurSelObject = obj;
		mCurSelObject->Selected(); 
		ShowCoord();
	}

	E3DEngine::GameObjectRef ^ SceneRef::GetCurSelObject()
	{
		return mCurSelObject;
	}

	void SceneRef::Update(float deltaTime)
	{
		if (mCurSelObject != nullptr && mObjectCoord != nullptr)
		{
			if (!EngineDelegate::GetInstance().GetIsRun())
			{
				mCurSelObject->Update(deltaTime);
				mObjectCoord->Update(deltaTime);
			}
		}
	}

	void SceneRef::AfterUpdate(float deltaTime)
	{
		if (mCurSelObject != nullptr && mObjectCoord != nullptr)
		{
			if (!EngineDelegate::GetInstance().GetIsRun())
			{
				mCurSelObject->AfterUpdate(deltaTime);

				mObjectCoord->AfterUpdate(deltaTime);
			}
		}
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


	SceneManageRef::SceneManageRef()
	{
		mCurScene = nullptr;
		mLookCoordCamera = nullptr;
		mCoordCamera = nullptr;
		mEditorCamera = nullptr;
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
		SceneManager::GetInstance().LoadScene(InputData);
		Scene *scene = SceneManager::GetInstance().GetCurrentScene();
		if (mCurScene == nullptr)
		{
			mCurScene = gcnew SceneRef(scene);
		}
		else
		{
			mCurScene->SetValue(scene);
		}
		mCurScene->Loaded();
		return mCurScene;
	}

	void SceneManageRef::LoadEditorObject()
	{
		if (mDefaultScene != nullptr)
		{
			mDefaultScene = nullptr;
		}
		if (SceneManager::GetInstance().GetCurrentScene() == nullptr)
		{
			SceneManager::GetInstance().LoadScene("../Data/Scene/default.scene");
			mDefaultScene = SceneManager::GetInstance().GetCurrentScene();
		}

		if (mEditorCamera == nullptr)
		{
			mEditorCamera = Camera::CreateCamera();
			SetEditorCamera(mEditorCamera, true);
			mEditorCamera->SetLayerMask(-1 & ~(1 << gCoordLayer) & ~(1 << gLookCoordLayer) & ~(1<< objectCoordLayer));
			mEditorCamera->Transform->SetPosition(0, 100, 200);
			mEditorCamera->Flag |= DONT_SAVE;
		}

		Terrain * terrain = new Terrain();
		terrain->Create(512);
		terrain->SetIsEditorGrid(true);
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial("../Data/Material/Terrain.material", 1);
		Renderer *rd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID, VertexManager::GetVertex(terrain->VertexBufferName).size());
		terrain->SetRenderer(rd);
		terrain->SetActive(true);
		terrain->SetLayerMask(1);
		terrain->GetRenderer()->SetDrawModule(eDM_LINES);
		terrain->Transform->SetScale(20, 1, 20);
		terrain->Flag |= DONT_SAVE;
		ADD_IN_SCENE(terrain);
		createCoord();
	}

	mat4f trans = mat4f::createTranslation(0, 0, 100);

	void SceneManageRef::Update(float deltaTime)
	{
		mat4f rot = mEditorCamera->Transform->Rotation.transform();
		mat4f world = rot * trans;

		mCoordCamera->Transform->WorldMatrix = world;
		mCoordCamera->SetViewMatrix(world.inverse());
	}

	void SceneManageRef::OnFrameSizeChange()
	{
		vec4f newPos = mLookCoordCamera->GetWorldPoint(1, 1, 0);

		mCoordRt->Transform->SetPosition(newPos.x - 15, newPos.y - 15, 0);
	}

	E3DEngine::Camera * SceneManageRef::GetEditorMainCamera()
	{
		return mEditorCamera;
	}

	E3DEngine::Camera * SceneManageRef::GetLookCoordCamera()
	{
		return mLookCoordCamera;
	}

	void SceneManageRef::createCoord()
	{
		if (mCoordCamera == nullptr)
		{
			mCoordCamera = Camera::CreateCamera();
			SetEditorCamera(mCoordCamera, false);
			mCoordCamera->SetLayerMask(1 << gCoordLayer);
			mCoordCamera->Transform->SetPosition(0, 0, 100);
			mCoordCamera->Flag |= DONT_SAVE;

			mLookCoordCamera = Camera::CreateCamera();
			SetEditorCamera(mLookCoordCamera, false);
			mLookCoordCamera->SetLayerMask((1 << gLookCoordLayer) | (1 << objectCoordLayer));
			mLookCoordCamera->Transform->SetPosition(0, 0, 150);
			mLookCoordCamera->Flag |= DONT_SAVE;
			mLookCoordCamera->SetClearType(eCT_NotClear);
		}

		mCoordRt = new Rectangle;
		mCoordRt->CreateShape(30, 30);
		mCoordRt->SetLayerMask(1 << gLookCoordLayer);
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial("../Data/Material/coordinate.material", 2);
		Render2Texture *rtt = m->GetRenderTexture();
		Renderer *rd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID, 4);
		mCoordRt->SetRenderer(rd);
		mCoordRt->SetActive(true);
		mCoordRt->Flag |= DONT_SAVE;
		vec4f newPos = mLookCoordCamera->GetWorldPoint(1, 1, 0);
		mCoordRt->Transform->SetPosition(newPos.x - 15, newPos.y - 15, 0);
		ADD_IN_SCENE(mCoordRt);
		mCoordCamera->SetRenderTexture(rtt);

		mCoordPrefab = (Prefab*)LoadPrefab("../Data/Scene/coordinate.prefab");
		mCoordPrefab->Flag |= DONT_SAVE;
		ADD_IN_SCENE(mCoordPrefab);

	}


	void SceneRef::createCoordinate(std::string materilPath, int selectID)
	{
		mObjectCoord = new Coordinate();
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(materilPath, selectID);
		Renderer *rd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID, VertexManager::GetVertex(mObjectCoord->VertexBufferName).size());
		mObjectCoord->SetLayerMask(1);
		mObjectCoord->SetRenderer(rd);
		mObjectCoord->Flag |= DONT_SAVE;
		mObjectCoord->SetActive(true);
		ADD_IN_SCENE(mObjectCoord);
	}

}

#pragma unmanaged

