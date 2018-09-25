
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-1 PanQingyun. All rights reserved. *************************//

#include "MonoScriptManager.h"
#include "../Object/E3DGameObject.h"
#include <mono/utils/mono-logger.h>
#include "../Source/EngineDelegate.h"
#include "../Physics/E3DCollider.hpp"
#include "../Source/E3DResource.h"

#define  _DEBUG_CSHARP 0
void mono_logger_call(const char *log_domain, const char *log_level, const char *message, mono_bool fatal, void *user_data)
{
	E3DEngine::Debug::Log(ell_Error, E3DEngine::StringBuilder::Format("%s ,%s ,%s" ,log_domain, log_level, message).c_str());
}
void mono_print_call(const char *string, mono_bool is_stdout)
{
	E3DEngine::Debug::Log(ell_Error,string);
}

void mono_printerr_call(const char *string, mono_bool is_stdout)
{
	E3DEngine::Debug::Log(ell_Error,string);
}

static MonoBreakPolicy NeverInsertBreakpoint(MonoMethod *method)
{
	return MONO_BREAK_POLICY_ALWAYS;
}


MonoScriptManager& MonoScriptManager::GetInstance()
{
	static MonoScriptManager ins;
	return ins;
}

void MonoScriptManager::Initialize()
{
	mono_trace_set_log_handler(mono_logger_call, nullptr);
	mono_trace_set_print_handler(mono_print_call);
	mono_trace_set_printerr_handler(mono_printerr_call);
	// Never insert system breakpoint for IL opcode Break and Debugger.Break () call.
	mono_set_break_policy(NeverInsertBreakpoint);
	
	std::string mono_dll_path = "Data/E3DAssembly";

	std::string code_dll_file = E3DEngine::Application::AppDataPath + "../Library/AssemblyCSharp.dll";

	std::string engine_dll_file ="Data/E3DAssembly/E3DEngine.dll";
	//g_set_print_handler(outPrint);
#if _DEBUG_CSHARP
	//	"--soft-breakpoints",
	// 启动调试
	const char* options[] =
	{
		"--soft-breakpoints",
		"--debugger-agent=transport=dt_socket,address=127.0.0.1:10000,server=y"
	};
	mono_jit_parse_options(sizeof(options) / sizeof(char*), (char**)options);
	mono_debug_init(MONO_DEBUG_FORMAT_MONO);
#endif

	mono_set_assemblies_path(mono_dll_path.c_str());
	mono_config_parse(NULL);
	m_pDomain = mono_jit_init(code_dll_file.c_str());
	// The soft debugger needs this
	mono_thread_set_main(mono_thread_current());
	m_pEngineAssembly = mono_domain_assembly_open(m_pDomain, engine_dll_file.c_str());
	m_pCodeAssembly = mono_domain_assembly_open(m_pDomain, code_dll_file.c_str());
	// 加载Plugin下所有的dll到domain
	loadPlugin();
	if (!m_pEngineAssembly)
	{
		E3DEngine::Debug::Log(ell_Error, "CSharp Assembly Wrong !");
		assert(false);
	}
	mono_domain_set(m_pDomain, true);
	m_pEngineImage = mono_assembly_get_image(m_pEngineAssembly);
	m_pCodeImage = mono_assembly_get_image(m_pCodeAssembly);
	registerInternalCall();
}

void MonoScriptManager::Destory()
{
	mono_jit_cleanup(m_pDomain);
}

MonoDomain * MonoScriptManager::GetEngineDomain()
{
	return m_pDomain;
}

MonoAssembly * MonoScriptManager::GetEngineAssembly()
{
	return m_pEngineAssembly;
}


MonoImage * MonoScriptManager::GetEngineImage()
{
	return m_pEngineImage;
}


MonoImage * MonoScriptManager::GetCodeImage()
{
	return m_pCodeImage;
}


MonoAssembly * MonoScriptManager::GetCodeAssembly()
{
	return m_pCodeAssembly;
}

void MonoScriptManager::registerInternalCall()
{
	RegisterMonoFunction();
}

void MonoScriptManager::loadPlugin()
{
	std::vector<FileInfo> files;
	Resource::GetFiles(Application::AppDataPath + "Plugin", files, "dll");
    for (auto &file : files)
	{
		MonoAssembly * assembly =  mono_domain_assembly_open(m_pDomain, file.FullName.c_str());
		m_assemblyLists.emplace_back(assembly);
	}
}

MonoBehaviour::MonoBehaviour()
{
	m_pMonoObject = nullptr;
}


void MonoBehaviour::SetImage(MonoImage * image)
{
	m_pImage = image;
}

void MonoBehaviour::Awake()
{
	CallMethod(AWAKE_FUNC);
}

void MonoBehaviour::Start()
{
	CallMethod(START_FUNC);
}

void MonoBehaviour::OnEnable()
{
	CallMethod(ENABLE_FUNC);
}

void MonoBehaviour::OnDisable()
{
	CallMethod(DISABLE_FUN);
}

void MonoBehaviour::LateUpdate(float deltaTime)
{
	void * arg = &deltaTime;
	CallMethod(LATEUP_FUNC, &arg);
}

void MonoBehaviour::Update(float deltaTime)
{
	void * arg = &deltaTime;
	CallMethod(UPDATE_FUNC, &arg);
}

void MonoBehaviour::Destory()
{
	CallMethod(DESTORY_FUNC);
}

void MonoBehaviour::OnCollisionEnter(btCollisionObject* collision)
{
	CallMethod(COLLISION_ENTER_FUNC, (void**)&collision);
}

void MonoBehaviour::SetFieldValue(const char * fieldName, void * value)
{
	MonoClassField *  field = mono_class_get_field_from_name(m_pClass, fieldName);
	if (field != nullptr)
	{
		mono_field_set_value(m_pMonoObject, field, value);
	}
}

void MonoBehaviour::SetPropertyValue(const char *name, void *value)
{
	MonoProperty * prop = mono_class_get_property_from_name(m_pClass, name);
	if (prop != nullptr)
	{
		mono_property_set_value(prop, m_pMonoObject, &value, &m_pException);
		if (m_pException != nullptr)
		{
			MonoString* string = mono_object_to_string(m_pException, nullptr);
			E3DEngine::Debug::Log(ell_Error, Convert::ToStdString(string).c_str());
		}
	}
}

void * MonoBehaviour::GetFieldValue(const char * fieldName)
{
	MonoClassField *  field = mono_class_get_field_from_name(m_pClass, fieldName);
	if (field == nullptr)
	{
		return nullptr;
	}
	void * value = nullptr;
	mono_field_get_value(m_pMonoObject, field, value);
	return value;
}


void * MonoBehaviour::GetPropertyValue(const char * name)
{
	MonoProperty * prop = mono_class_get_property_from_name(m_pClass, name);
	if (prop != nullptr)
	{
		void *params;
		void * val = mono_property_get_value(prop, m_pMonoObject, &params, &m_pException);

		if (m_pException != nullptr)
		{
			MonoString* string = mono_object_to_string(m_pException, nullptr);
			E3DEngine::Debug::Log(ell_Error, Convert::ToStdString(string).c_str());
		}
		return val;
	}
	return nullptr;
}

void MonoBehaviour::CallMethod(const char * name, void ** param , int paramNum /* = 0*/)
{
	MonoMethod * method = nullptr;
	if (m_MethodMap.find(name) == m_MethodMap.end())
	{
		method = mono_class_get_method_from_name(m_pClass, name, paramNum);
	}
	else
	{
		method = m_MethodMap[name];
	}
	if (method == nullptr)
	{
		return;
	}
	callMethod(param, method);

}


void MonoBehaviour::callMethod(void ** param, MonoMethod *method)
{
	if (param == nullptr)
	{
		char * arg = "";
		param = (void **)&arg;
	}
	mono_runtime_invoke(method, m_pMonoObject, param, &m_pException);
	if (m_pException != nullptr)
	{
		MonoString* string = mono_object_to_string(m_pException, nullptr);
		E3DEngine::Debug::Log(ell_Error, Convert::ToStdString(string).c_str());
	}
}

MonoObject * MonoBehaviour::GetMonoObject()
{
	return m_pMonoObject;
}


void MonoBehaviour::SetMonoObject(MonoObject *obj)
{
	if (m_pMonoObject == obj)
	{
		return;
	}
	m_pMonoObject = obj;
	m_pClass = mono_object_get_class(obj);
}

void MonoBehaviour::Create(const char * name_space, const char * className)
{	
	if (m_pMonoObject != nullptr)
	{
		/*mono_free(obj);
		obj = nullptr;*/
	}
	m_pClass = mono_class_from_name(m_pImage, name_space, className);
	m_pMonoObject = mono_object_new(MonoScriptManager::GetInstance().GetEngineDomain(), m_pClass);
	if (m_pMonoObject is nullptr)
	{
		return;
	}
	constructor();
	MonoMethod * m = nullptr;// mono_class_get_method_from_name(klass, AWAKE_FUNC, 0);
	/*if (m != nullptr)
	{
		callMethod(nullptr, m);
	}*/
	void * iter = nullptr;
	while (m = mono_class_get_methods(m_pClass, &iter))
	{
		const char * name = mono_method_get_name(m);
		m_MethodMap[name] = m;
	}
}

void MonoBehaviour::constructor()
{
	MonoMethod *con_m = mono_class_get_method_from_name(m_pClass, CONSTRUCTOR, 0);
	if (con_m != nullptr)
	{
		mono_runtime_invoke(con_m, m_pMonoObject, nullptr, &m_pException);
		if (m_pException != nullptr)
		{
			MonoString* string = mono_object_to_string(m_pException, nullptr);
			E3DEngine::Debug::Log(ell_Error, Convert::ToStdString(string).c_str());
		}
	}
}


MonoBehaviour::~MonoBehaviour()
{
	//mono_free(m_pMonoObject);
}

MonoClass * MonoBehaviour::GetClass()
{
	return m_pClass;
}
