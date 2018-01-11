//
//  EngineDelegate.hpp
//  Obj
//
//  Created by 潘庆云 on 2017/1/17.
//  Copyright © 2017年 潘庆云. All rights reserved.
//

#ifndef EngineDelegate_hpp
#define EngineDelegate_hpp

#include "../../include/Include.h"
#include "../Camera/E3DCamera.h"
#include "../ParticleSystem/E3DParticleFactory.hpp"
#include "../ParticleSystem/E3DParticleSystem.hpp"
#include "../ParticleSystem/E3DParticlePool.h"
#include "../Effect/E3DEffectFactory.hpp"
#include "../Effect/E3DTextureFrameEffect.hpp"
#include "../Light/E3DLight.hpp"
#include "../Scene/E3DScene.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Mesh/E3DMeshFactory.hpp"
#include "../Object/E3DDynamicRectangle.hpp"
#include "../Object/E3DRectangle.hpp"
#include "../Object/E3DTransform.hpp"
#include "E3DDebug.h"
#include "E3DTimer.hpp"
#include "ClassFactory.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "E3DAutoreleasePool.h"
#include "../Object/E3DBox.h"
#include "../Object/E3DSphere.h"
#include "../Physics/E3DPhysics.h"
#include "NativeSystem.h"
#include "Application.h"
#include "../Mono/MonoScriptManager.h"
#include "../Physics/E3DCollider.hpp"

#define RAD2DEG(x) (x * 180.0 / M_PI)
#define CAMERA_Z_POS 50.0

#define MainCameraName "main_camera"
#define MeshCamera "mesh_camera"
#define HL_VIDEO_CAMERA "HL_VIDEO_CAMERA"
#define LAYER_CONFIAG_NAME "Resource/LayerConfig.xml"

namespace E3DEngine
{
#define USE_GPU_IMAGE
	class EngineDelegate implement IObject
	{
	public:
		static EngineDelegate &GetInstance()
		{
			static EngineDelegate _ins;
			return _ins;
		};
		~EngineDelegate();
		void Initilize();
		void SetupMainCamera(Camera *camera);
		void SetupCamera(const char * name, Camera *camera);
		void SetCameraRotateByMat(const char* name ,mat4f new_mat,bool isCameraFront);
		void InitConfig(const char * path);
		void SetResourcePath(const char * path);
		void DestoryTableManager(std::string id);
		TableManager * GetTableManager(std::string id);		
		void SetCommonResourcePath(const char * path);		
		void DestoryScene(Scene *scene);	
		void Destory();
		
	public:
		UINT GenObjectID();
		void DestoryObject(GameObject* obj);
		void ChangeScene(Scene* scene);
		void ChangeScene(uint sceneID);
		void AddDonotDestory(GameObject* obj);
		void DeleteCamera(std::string name);
		void SetEnginePause(bool bPause);
		bool GetEnginePause();
        void SetSceneType(int type);

	private:
		EngineDelegate();
	private:
		std::map<std::string, TableManager*>	m_mapTableManager;
		eTargetPlatform							m_ePlatform;
		std::map<std::string, ISystem*>			m_mapSystems;
		const char *							m_strResourcePath;
		bool									m_bIsInited;
		UINT									m_nObjectID;
		bool									m_bPause;
		std::map<UINT, GameObject*>			m_mapDoNotDestoryObject;
		Scene		*							m_pLastScene;
		
	public:
		mat4f RotateMatrix;
		event EventDelegates SceneClearEvent;
		void Update(float deltaTime, bool selfClear = true);
	};
}

#endif /* EngineDelegate_hpp */
