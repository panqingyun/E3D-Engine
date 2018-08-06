//
//  E3DSceneManager.cpp
//
//  Created by 潘庆云 on 2017/8/11.
//

#include "E3DSceneManager.hpp"
#include "../Source/EngineDelegate.h"
#include "../Object/E3DObject.h"
#include "../Source/FilePath.h"

namespace E3DEngine
{
	
	SceneManager::SceneManager()
	{
		mCurScene = nullptr;
		E3DEngine::RegistScnObjCreateFunc();
	}

	void SceneManager::Initilize()
	{

	}

	void SceneManager::Destory()
	{		

	}

	E3DEngine::Scene * SceneManager::LoadScene(std::string filePath)
	{		
		if (mCurScene != nullptr)
		{
			mCurScene->Destory();
			SAFE_DELETE(mCurScene);
		}
		mCurScene = new Scene();
		mCurScene->Create(filePath);

		return mCurScene;
	}

	E3DEngine::Scene * SceneManager::GetCurrentScene()
	{
		return GetInstance().mCurScene;
	}

}
