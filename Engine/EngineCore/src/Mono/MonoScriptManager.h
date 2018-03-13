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
	m_pBehaviour->Create(NAME_SPACE, #_class);


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
	void OnCollisionEnter(btCollisionObject* collision);
	void SetFieldValue(const char *fieldName, void *value);
	void SetPropertyValue(const char *name, void *value);
	void *GetFieldValue(const char * fieldName);
	void *GetPropertyValue(const char * name);
	void CallMethod(const char * name, void ** param = nullptr);
	MonoClass * GetClass();
	MonoObject * GetMonoObject();
	void SetMonoObject(MonoObject *obj) { m_pMonoObject = obj; }
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
  	static MonoScriptManager& GetInstance()
	{
		static MonoScriptManager ins;
		return ins;
	}
public:
	void Initialize();
	void Destory();

	MonoDomain * GetEngineDomain();
	MonoAssembly * GetEngineAssembly();
	MonoImage * GetEngineImage();

	MonoImage * GetCodeImage();
	MonoAssembly * GetCodeAssembly();

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
};



