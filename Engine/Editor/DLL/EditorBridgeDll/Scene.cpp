#include "Scene.h"
#include "stdafx.h"
#include <Scene/E3DSceneLoader.h>

#pragma managed
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
using namespace System;
namespace E3DEngine
{
	void TransformChange(int ID)
	{
		GameObjectRef ^refObj = SceneManageRef::GetInstance()->GetCurScene()->GetCurSelObject();
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

	void SceneRef::ShowCoord(CTransform *transform)
	{
		if (mObjectCoord == nullptr)
		{
			createCoordinate("../Data/Material/coordinate.material", 1);
		}
		mObjectCoord->SetTransform(transform);
	}

	void SceneRef::Loaded()
	{
		mObjectCoord = nullptr;
		mRootObject->Reset();
	}

	void SceneRef::SetSelectObject(GameObjectRef ^obj)
	{
		mCurSelObject = obj;
	}

	E3DEngine::GameObjectRef ^ SceneRef::GetCurSelObject()
	{
		return mCurSelObject;
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
			mDefaultScene = SceneManager::GetInstance().LoadScene("../Data/Scene/default.scene");
		}

		if (mEditorCamera == nullptr)
		{
			mEditorCamera = Camera::CreateCamera();
			SetEditorCamera(mEditorCamera, true);
			mEditorCamera->SetLayerMask(-1 & ~(1<<30) & ~(1<<29));
			mEditorCamera->Transform->SetPosition(0, 100, 200);
			mEditorCamera->Flag |= DONT_SAVE;
		}

		Terrain * terrain = new Terrain();
		terrain->Create(512);
		terrain->SetIsEditorGrid(true);
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial("../Data/Material/Terrain.material", 1);
		terrain->SetMaterial(m);
		terrain->SetLayerMask(1);
		terrain->GetRenderer()->SetDrawModule(eDM_LINES);
		terrain->Flag |= DONT_SAVE;
		ADD_IN_SCENE(terrain);
		createCoord();
	}

	mat4f rotation180 = Quatf::fromEulerAngles(0, 180, 0).transform();
	mat4f trans = mat4f::createTranslation(0, 0, -100);

	void SceneManageRef::Update()
	{
		mat4f rot = mEditorCamera->Transform->Rotation.transform();
		mat4f world = rot * trans * rotation180;

		mCoordCamera->Transform->WorldMatrix = world;
	}

	void SceneManageRef::OnFrameSizeChange()
	{
		vec3f newPos = mLookCoordCamera->GetWorldPointWithScreenPoint(1, 1, 0);

		mCoordRt->Transform->SetPosition(newPos.x - 15, newPos.y - 15, 0);
	}

	void SceneManageRef::createCoord()
	{
		if (mCoordCamera == nullptr)
		{
			mCoordCamera = Camera::CreateCamera();
			SetEditorCamera(mCoordCamera, false);
			mCoordCamera->SetLayerMask(1 << 30);
			mCoordCamera->Transform->SetPosition(0, 0, -100);
			mCoordCamera->Transform->SetRotation(0, 180, 0);
			mCoordCamera->Flag |= DONT_SAVE;

			mLookCoordCamera = Camera::CreateCamera();
			SetEditorCamera(mLookCoordCamera, false);
			mLookCoordCamera->SetLayerMask(1 << 29);
			mLookCoordCamera->Transform->SetPosition(0, 0, 150);
			mLookCoordCamera->Flag |= DONT_SAVE;
			mLookCoordCamera->SetClearType(eCT_NotClear);
		}

		mCoordRt = new Rectangle;
		mCoordRt->CreateShape(30, 30);
		mCoordRt->SetLayerMask(1 << 29);
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial("../Data/Material/coordinate.material", 2);
		Render2Texture *rtt = m->GetRtt();
		m->SetTexture(rtt);
		Renderer *rd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID);
		mCoordRt->SetRenderer(rd);
		vec3f newPos = mLookCoordCamera->GetWorldPointWithScreenPoint(1, 1, 0);
		mCoordRt->Transform->SetPosition(newPos.x - 15, newPos.y - 15, 0);
		ADD_IN_SCENE(mCoordRt);
		mCoordCamera->SetRenderTexture(rtt);

		mCoordPrefab = (Prefab*)LoadPrefab("../Data/Scene/coordinate.prefab");
		mCoordPrefab->SetLayerMask(1 << 30);
		mCoordPrefab->Flag |= DONT_SAVE;
		mCoordPrefab->Transform->SetNeedUpdate(false);
		ADD_IN_SCENE(mCoordPrefab);

	}

	void SceneRef::createCoordinate(std::string materilPath, int selectID)
	{
		mObjectCoord = new Coordinate();
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(materilPath, selectID);
		Renderer *rd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID);
		mObjectCoord->SetLayerMask(1 << 30);
		mObjectCoord->SetRenderer(rd);
		mObjectCoord->Flag |= DONT_SAVE;
		ADD_IN_SCENE(mObjectCoord);
	}

}

#pragma unmanaged

