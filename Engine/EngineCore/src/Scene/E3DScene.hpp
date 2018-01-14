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
#include "../Light/E3DLight.hpp"

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
    
	class Scene : public Object
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
		void ChangeRenderIndex(UINT id, eRenderIndex index);
		void AddCamera(Camera * pCamera);
		void SortCamera();
		Camera * GetCamera(UINT cameraID);
		void ChangeFrameSize(float w, float h);
		void AddRenderObject(RenderObject* rb, UINT layer);
		void AddLight(Light * light);
		Light * GetDirectionalLight();

	public:
		virtual void AddChild(Object * node);
		virtual void RemoveChild(Object * node);
		virtual void RemoveChild(UINT ID);

	protected:
		virtual void CreateBehaviour() override;
	public:
		bool					dontDestoryScene;
		event EventDelegates	SceneReloadEvent;

	private:
        eSceneType		m_SceneType;
		std::vector<Camera*> m_vecCamera;
		std::map<DWORD, Object*> m_vecObjList;
		GameObject		* rootObject;
		std::map<DWORD, RenderObject*> m_mapRenders;
		std::map<UINT ,Light*> m_mapLights;
		DirectionLight * usedDirectionLight;
	};
}

#endif /* E3DScene_hpp */
