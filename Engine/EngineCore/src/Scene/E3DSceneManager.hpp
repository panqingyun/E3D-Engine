//
//  E3DSceneManager.hpp
//
//  Created by 潘庆云 on 2017/8/11.
//

#ifndef __E3D_SCENE_MANAGER_HPP__
#define __E3D_SCENE_MANAGER_HPP__

#include "E3DScene.hpp"

#define NULL_SCENE 0

namespace E3DEngine
{
	class E3D_EXPORT_DLL SceneManager : public IObject
	{
	public:
		static SceneManager& GetInstance();

	public:
		SceneManager();
		virtual void Initilize();
		virtual void Destory();		
		void LoadScene(std::string filePath);
		static Scene * GetCurrentScene();

	private:
		Scene * mCurScene;
	};
}
#endif /* E3DSceneManager_hpp */
