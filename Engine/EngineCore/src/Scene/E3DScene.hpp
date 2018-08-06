//
//  E3DScene.hpp
//
//  Created by 潘庆云 on 2017/7/11.
//

#ifndef __E3D_SCENE_HPP__
#define __E3D_SCENE_HPP__

#include "../Object/E3DGameObject.h"
#include "../Object/E3DRenderObject.hpp"
#include "../Source/E3DDelegate.h"
#include "../Light/E3DLight.hpp"

namespace E3DEngine
{
	enum RenderTargetType
	{
		eMainFrameBuffer	= 0,
		eBlendBackImage		= 1,
		eNotBlendOther		= 2,
	};
    
	void RegistScnObjCreateFunc();

	class Scene : public Object
	{
	public:
		Scene();
		virtual ~Scene() override;
	public:
		void Create(std::string filePath);
		void Update(float deltaTime);
		void Destory();
		void DestoryAllOjectImmediately();
		void RenderScene(float deltaTime);
		void ChangeRenderIndex(UINT id, eRenderIndex index);
		void AddCamera(Camera * pCamera);
		void SortCamera();
		void AddObject(Object * obj);
		void RemoveObject(Object * node);
		UINT GenObjectID();
	public:
		void ChangeCameraObject(Camera *pCamera);
		void ChangeRenderObjectLayer(RenderObject * rb);
		Camera * GetCamera(UINT cameraID);
		Camera * GetMainCamera();
		void ChangeViewportSize(float w, float h);
		void AddRenderObject(RenderObject* rb, UINT layer);
	public:
		void RemoveObject(UINT ID);
		void AddLight(Light * light);
		void DeleteLight(Light *light);
		Light * GetDirectionalLight();
		std::map<UINT, Light*>& GetPointLights();

	protected:
		virtual void CreateBehaviour() override;
	public:
		event EventDelegates	SceneReloadEvent;

	private:
		std::vector<Camera*>			m_vecCamera;
		std::map<DWORD, Object*>		m_vecObjList;
		GameObject		*				rootObject;
		std::map<DWORD, RenderObject*>	m_mapRenders;
		std::map<UINT ,Light*>			m_mapLights;
		DirectionLight *				usedDirectionLight;
		UINT							m_nObjectID;
	};
}

#endif /* E3DScene_hpp */
