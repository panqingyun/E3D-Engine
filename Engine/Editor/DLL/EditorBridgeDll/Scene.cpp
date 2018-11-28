#include "Scene.h"
#include "stdafx.h"
#include "Source/E3DVertexManager.h"
#include <Scene/E3DSceneLoader.h>
#include <string>

#pragma managed
#include <msclr\marshal_cppstd.h>
#include "Physics/E3DPhysics.h"
using namespace msclr::interop;
using namespace System;

std::string get_std_string(String ^str)
{
	return marshal_as<std::string>(str);
}

namespace E3DEngine
{
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

	void SceneDetory()
	{
		SceneManageRef::GetInstance()->DestoryScene();
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
		/*if (mObjectCoord == nullptr)
		{
			createCoordinate("../Data/Material/coordinate.material", 1);
		}
		mObjectCoord->Transform = mCurSelObject->GetTransform()->GetTransformPtr();*/
	}

	void SceneRef::Loaded()
	{
		mCurSelObject = nullptr;
		mObjectCoord = nullptr;
		mRootObject->Reset();
	}

	void SceneRef::SetSelectObject(GameObjectRef ^obj)
	{
		if (mCurSelObject != nullptr)
		{
			mCurSelObject->GetGameObjectPtr()->Selected(false);
		}
		mCurSelObject = obj;
		mCurSelObject->GetGameObjectPtr()->Selected(true);
		ShowCoord();
	}

	E3DEngine::GameObjectRef ^ SceneRef::GetCurSelObject()
	{
		return mCurSelObject;
	}

	void SceneRef::Update(float deltaTime)
	{
		if (mCurSelObject != nullptr)
		{
			if (!EngineDelegate::GetInstance().GetIsRun())
			{
				mCurSelObject->Update(deltaTime);
			}
		}
	}

	void SceneRef::AfterUpdate(float deltaTime)
	{
		if (mCurSelObject != nullptr )
		{
			if (!EngineDelegate::GetInstance().GetIsRun())
			{
				mCurSelObject->AfterUpdate(deltaTime);
			}
		}
	}

	void SceneRef::PickObject(float x, float y)
	{
		Camera * editorMain = SceneManageRef::GetInstance()->GetEditorMainCamera();
		
		Ray ray = editorMain->ScreenPointToRay(vec2f(x, y));
		RaycastHit hitInfo;
		bool &&bHit = PhysicWorld::GetInstance().RayCast(ray, hitInfo);
		if (bHit)
		{
			GameObjectRef ^gameObj = GetGameObject(hitInfo.mGameObject->ID);
			if (gameObj != nullptr)
			{
				gameObj->Selected();
				SetSelectObject(gameObj);
			}
		}
	}

	void SceneRef::OnMouseDown(int buttonID, float x, float y)
	{
		if (buttonID == MouseButton::eLeftButton)
		{
			mLastPos->SetValue(x, y);
			mMouseIsPress = true;
		}
	}


	void SceneRef::OnMouseUp(int mouseButtonID, float xPos, float yPos)
	{
		mLastPos->SetValue(0, 0);
		mMouseIsPress = false;
		if (mouseButtonID == MouseButton::eLeftButton)
		{
			//PickObject(xPos, yPos);
		}
	}

	void SceneRef::OnMouseMove(float xPos, float yPos)
	{
		if (mMouseIsPress && mCurSelObject != nullptr)
		{
			if (SceneManageRef::GetInstance()->GetMoveDirection() == ObjectMoveDirection::HORZITAL)
			{
				Camera * pMainCamera = SceneManageRef::GetInstance()->GetEditorMainCamera();
				vec3f newPos = mCurSelObject->GetTransform()->GetTransformPtr()->GetPosition() + pMainCamera->GetRigthVector() * (xPos- mLastPos->x) / 5;

				mCurSelObject->GetTransform()->GetTransformPtr()->SetPosition(newPos);
				mLastPos->SetValue(xPos, yPos);
			}
			else if (SceneManageRef::GetInstance()->GetMoveDirection() == ObjectMoveDirection::VERTICAL)
			{
				Camera * pMainCamera = SceneManageRef::GetInstance()->GetEditorMainCamera();
				vec3f newPos = mCurSelObject->GetTransform()->GetTransformPtr()->GetPosition() + pMainCamera->GetUpVector() * ( mLastPos->y - yPos) / 5;
				mCurSelObject->GetTransform()->GetTransformPtr()->SetPosition(newPos);
				mLastPos->SetValue(xPos, yPos);
			}
		}
	}

	void SceneRef::OnKeyDown(char key)
	{
		mCurKey = key;
	}


	void SceneRef::OnKeyUp(char key)
	{
	//	mCurKey = '0';
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
		mMouseIsPress = false;
		mLastPos = gcnew Vector2();
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
		mDirection = ObjectMoveDirection::HORZITAL;
		mCurScene = nullptr;
		mLookCoordCamera = nullptr;
		mCoordCamera = nullptr;
		mEditorCamera = nullptr;
		SceneManager::GetInstance().SceneDestoryCallBack = SceneDetory;
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
			//mCurScene->SetValue(scene);
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
		return mCurScene;
	}

	void SceneManageRef::LoadEditorObject()
	{
		std::string path = get_std_string(mEditorPath);
		if (mDefaultScene != nullptr)
		{
			mDefaultScene = nullptr;
		}
		if (SceneManager::GetInstance().GetCurrentScene() == nullptr)
		{
			SceneManager::GetInstance().LoadScene(path + "/../Data/Scene/default.scene");
			mDefaultScene = SceneManager::GetInstance().GetCurrentScene();
		}

		if (mEditorCamera == nullptr)
		{
			GameObject *editorCameraGameObject = new GameObject();
			editorCameraGameObject->CreateBehaviour();
			editorCameraGameObject->SetActive(true);
			mEditorCamera = (Camera*)editorCameraGameObject->AddComponent(CAMERA_NAME);
			SetEditorCamera(mEditorCamera, true);
			editorCameraGameObject->mName = "mEditorCamera";
			editorCameraGameObject->SetColor(Color4(1, 1, 1, 1));
			editorCameraGameObject->SetLayerMask(-1 & ~LD_COORD & ~LD_LOOK_COORD & ~LD_OBJECT_COORD);
			editorCameraGameObject->Flag |= DONT_SAVE;
			mEditorCamera->OnCreate();
			mEditorCamera->OnCreateComplete();
			editorCameraGameObject->Transform->SetPosition(0, 100, 200);
		}

		GameObject *gameObject = new GameObject();
		gameObject->CreateBehaviour();
		gameObject->SetActive(true);
		gameObject->SetLayerMask(1);
		gameObject->Flag |= DONT_SAVE;

		Terrain *terrain = gameObject->AddComponent<Terrain>();
		terrain->IsEditorGrid = true;
		terrain->Size = 512;
		terrain->OnCreate();
		terrain->OnCreateComplete();
		gameObject->Transform->SetScale(20, 1, 20);
		Renderer *render = gameObject->AddComponent<Renderer>();
		render->MaterialPath = path + "/../Data/Material/Terrain.material";
		render->MaterialID = 1;
		render->OnCreate();
		render->OnCreateComplete();
		static_cast<BatchRenderer*>(render->Get())->SetDrawModule(eDM_LINES);
		ADD_IN_SCENE(gameObject);

		//createCoord();
	}

	mat4f trans = mat4f::createTranslation(0, 0, 100);

	void SceneManageRef::Update(float deltaTime)
	{
	/*	mat4f rot = mEditorCamera->Transform->Rotation.transform();
		mat4f world = rot * trans;

		mCoordCamera->Transform->WorldMatrix = world;
		mCoordCamera->SetViewMatrix(world.inverse());*/
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

	void SceneManageRef::SetRunPath(String ^path)
	{
		mEditorPath = path;
	}

	void SceneManageRef::DestoryScene()
	{
		mCurScene = nullptr;
	}

	void SceneManageRef::SetMoveDirection(int dir)
	{
		mDirection = dir;
	}

	int SceneManageRef::GetMoveDirection()
	{
		return mDirection;
	}

	void SceneManageRef::createCoord()
	{
		if (mCoordCamera == nullptr)
		{
			GameObject *coordCamerObject = new GameObject();
			coordCamerObject->CreateBehaviour();
			coordCamerObject->SetActive(true);
			coordCamerObject->SetLayerMask(LD_COORD);
			coordCamerObject->Flag |= DONT_SAVE;
			mCoordCamera = (Camera*)coordCamerObject->AddComponent(CAMERA_NAME);
			mCoordCamera->OnCreate();
			mCoordCamera->OnCreateComplete();
			coordCamerObject->Transform->SetPosition(0, 0, 100);
			SetEditorCamera(mCoordCamera, false);
			GameObject *lookGameobject = new GameObject();
			lookGameobject->CreateBehaviour();
			lookGameobject->SetActive(true); 
			lookGameobject->SetLayerMask(LD_LOOK_COORD | LD_OBJECT_COORD);
			lookGameobject->Flag |= DONT_SAVE;
			mLookCoordCamera = (Camera*)lookGameobject->AddComponent(CAMERA_NAME);
			mLookCoordCamera->OnCreate();
			mLookCoordCamera->OnCreateComplete();
			lookGameobject->Transform->SetPosition(0, 0, 150);
			SetEditorCamera(mLookCoordCamera, false);
			
			mLookCoordCamera->SetClearType(eCT_NotClear);
		}
		std::string path = get_std_string(mEditorPath);
		GameObject *gameObject = new GameObject();
		gameObject->CreateBehaviour();
		mCoordRt = gameObject->AddComponent<Rectangle>();
		gameObject->SetLayerMask(LD_LOOK_COORD);
		mCoordRt->OnCreate();
		mCoordRt->OnCreateComplete();
		gameObject->SetActive(true);
		gameObject->Transform->SetScale(50, 50, 1);
		Renderer *rd = gameObject->AddComponent<Renderer>();
		rd->MaterialID = 2;
		rd->MaterialPath = path +"/../Data/Material/coordinate.material";
		rd->OnCreate();
		rd->OnCreateComplete();
		Render2Texture *rtt = static_cast<BatchRenderer*>(rd->Get())->GetMaterial()->GetRenderTexture();
		gameObject->Flag |= DONT_SAVE;
		vec4f newPos = mLookCoordCamera->GetWorldPoint(1, 1, 0);
		gameObject->Transform->SetPosition(newPos.x - 15, newPos.y - 15, 0);
		ADD_IN_SCENE(gameObject);
		mCoordCamera->SetRenderTexture(rtt);
		mCoordPrefab = (Prefab*)LoadPrefab(path + "/../Data/Scene/coordinate.prefab");
		mCoordPrefab->Flag |= DONT_SAVE;
		ADD_IN_SCENE(mCoordPrefab);

	}


	void SceneRef::createCoordinate(std::string materilPath, int selectID)
	{
		/*mObjectCoord = new Coordinate();
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(materilPath, selectID);
		Renderer *rd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID, VertexManager::GetVertex(mObjectCoord->VertexBufferName).size());
		mObjectCoord->SetLayerMask(1);
		mObjectCoord->SetRenderer(rd);
		mObjectCoord->Flag |= DONT_SAVE;
		mObjectCoord->SetActive(true);
		ADD_IN_SCENE(mObjectCoord);*/
	}

}

#pragma unmanaged

