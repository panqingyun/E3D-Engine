//
//  E3DSceneManager.hpp
//
//  Created by 潘庆云 on 2017/8/11.
//

#ifndef E3DSceneManager_hpp
#define E3DSceneManager_hpp

#include "E3DScene.hpp"

#define NULL_SCENE 0

namespace E3DEngine
{
	class SceneManager implement IObject
	{
	public:
		static SceneManager& GetInstance()
		{
			static SceneManager _ins;
			return _ins;
		}

	public:
		SceneManager();
		virtual void Initilize();
		virtual void Destory();		
		Scene * CreateScene();

		bool ChangeScene(uint sceneID);
		bool ChangeScene(Scene * scene);
		Scene * GetCurrentScene();
		Scene * GetScene(uint sceneID);		
		void DestoryScene(Scene * scene);

	private:
		std::map<uint, Scene*>  m_mapScenes;
		uint					m_lastSceneID;
		uint					m_currentUseSceneID;
	};
}

#endif /* E3DSceneManager_hpp */
