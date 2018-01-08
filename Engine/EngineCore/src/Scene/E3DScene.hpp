//
//  E3DScene.hpp
//
//  Created by 潘庆云 on 2017/7/11.
//

#ifndef E3DScene_hpp
#define E3DScene_hpp

#include "../Object/E3DGameObject.h"
#include "../Object/E3DRenderObject.hpp"
#include "../Source/E3DDelegate.h"
#include "../Source/E3DRenderQueue.h"

namespace E3DEngine
{
    enum eSceneType
    {
        eSceneType_defult = 0,
        eSceneType_edittext = 1,
    };

	enum RenderTargetType
	{
		eMainFrameBuffer	= 0,
		eBlendBackImage		= 1,
		eNotBlendOther		= 2,
	};
    
	class Scene extends Object
	{
	public:
		Scene();
		virtual ~Scene() override;
	public:
		void Update(float deltaTime);
		void Destory();
		void SetDontDestory(bool dontDestory);
		void SceneReload();
		void DestoryAllOjectImmediately();        
		void SetSceneType(eSceneType type);
		eSceneType GetSceneType();
		void RenderScene(float deltaTime);
		void ChangeRenderIndex(QWORD id, eRenderIndex index);
		void AddCamera(Camera * pCamera);
		void SortCamera();
		Camera * GetCamera(QWORD cameraID);
		void ChangeFrameSize(float w, float h);

	public:
		virtual void AddChild(Object * node);
		virtual void RemoveChild(Object * node);
		virtual void RemoveChild(QWORD ID);

	protected:
		virtual void CreateBehaviour() override;
	public:
		bool					dontDestoryScene;
		event EventDelegates	SceneReloadEvent;
		CTransform * Transform;

	private:
        eSceneType		m_SceneType;
		std::vector<Camera*> m_vecCamera;
		std::map<DWORD, Object*> m_vecObjList;
	};
}

#endif /* E3DScene_hpp */
