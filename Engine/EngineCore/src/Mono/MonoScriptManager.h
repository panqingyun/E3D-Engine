
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-1 PanQingyun. All rights reserved. *************************//

#pragma once
#include "../Source/Interface.h"
#include "MonoFunction.h"

#define CONSTRUCTOR ".ctor"
#define AWAKE_FUNC "Awake"
#define START_FUNC "Start"
#define UPDATE_FUNC "Update"
#define DESTORY_FUNC "Destory"
#define ENABLE_FUNC "OnEnable"
#define DISABLE_FUN "OnDisable"
#define LATEUP_FUNC "LateUpdate"
#define COLLISION_ENTER_FUNC "OnCollisionEnter"

#define NAME_SPACE "E3DEngine"
#define NEW_INSTANCE(_class)\
	mBehaviour->Create(NAME_SPACE, #_class);


class MonoBehaviour : public E3DEngine::IObject
{
public:
	MonoBehaviour();
	~MonoBehaviour();
	void SetImage(MonoImage * image);
	void Create(const char * name_space, const char * className);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Destory();
	void OnEnable();
	void OnDisable();
	void LateUpdate(float deltaTime);
#ifndef __IGNORED_INCLUDE__
	void OnCollisionEnter(btCollisionObject* collision);
#endif
	void SetFieldValue(const char *fieldName, void *value);
	void SetPropertyValue(const char *name, void *value);
	void *GetFieldValue(const char * fieldName);
	void *GetPropertyValue(const char * name);
	void CallMethod(const char * name, void ** param = nullptr, int paramNum = 0);
	MonoClass * GetClass();
	MonoObject * GetMonoObject();
	void SetMonoObject(MonoObject *obj);
private:
	void constructor();
	void callMethod(void ** param, MonoMethod *method);

private:
	MonoClass *m_pClass;
	MonoObject *m_pMonoObject;
	std::map<std::string, MonoMethod*> m_MethodMap;

	MonoObject * m_pException;
	MonoImage * m_pImage;

};

class MonoScriptManager
{
public:
  	static MonoScriptManager& GetInstance();
public:
	void Initialize();
	void Destory();

	MonoDomain * GetEngineDomain();
	MonoAssembly * GetEngineAssembly();
	MonoImage * GetEngineImage();

	MonoImage * GetCodeImage();
	MonoAssembly * GetCodeAssembly();
	void SetMonoPath(std::string env_dllPath, std::string assembly_dllPath, std::string engine_dllPath);

private:
	void registerInternalCall();
	void loadPlugin();

private:
	MonoImage *m_pCodeImage;
	MonoImage *m_pEngineImage;
	MonoDomain *m_pDomain; 
	MonoAssembly *m_pCodeAssembly;
	MonoAssembly *m_pEngineAssembly;
	std::vector<MonoAssembly *> m_assemblyLists;
	std::string  mono_dll_path;
	std::string  code_dll_file;
	std::string  engine_dll_file;
};



