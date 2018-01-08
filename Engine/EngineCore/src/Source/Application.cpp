#include "Application.h"
#include "EngineDelegate.h"

namespace E3DEngine
{
	std::string Application::AppDataPath = "";
	std::string Application::ResourcePath = "";
	bool Application::m_bIsStop = false;
	MonoBehaviour * Application::m_pBehaviour = nullptr;
	void Application::CreatScript()
	{
		mono_add_internal_call("E3DEngine.Application::getAppDataPath", Application::getAppDataPath);
		mono_add_internal_call("E3DEngine.Application::exitApplication", Application::ExitApp);
		mono_add_internal_call("E3DEngine.Application::getResourcePath", Application::getResourcePath);
	}

	void Application::StartApp()
	{
		m_bIsStop = false;
		MonoScriptManager::GetInstance().Initialize();
		CreatScript();
		std::string startApp = "app.config";
		std::string fileContent = vvision::getContentFromPath(startApp);
		if (fileContent != empty_string)
		{
			std::vector<std::string> vestr = E3DEngine::StringBuilder::Split(fileContent, "=");
			if (vestr.size() == 2)
			{
				string entryClass = vestr[1];
				std::vector<std::string> nameSpace_className = StringBuilder::Split(entryClass, ":");
				std::string entryNameSpce = "";
				std::string entryClassName = "";
				if (nameSpace_className.size() == 2)
				{
					entryNameSpce = StringBuilder::Trim(nameSpace_className[0]);
					entryClassName = StringBuilder::Trim(nameSpace_className[1]);
				}
				else if (nameSpace_className.size() == 1)
				{
					entryClassName = StringBuilder::Trim(nameSpace_className[0]);
				}
				m_pBehaviour = new MonoBehaviour;
				m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetCodeImage());
				m_pBehaviour->Create(entryNameSpce.c_str(), entryClassName.c_str());
				m_pBehaviour->CallMethod("Main");
			}
		}
		else
		{
			assert(false);
		}
	}

	void Application::StopApp()
	{
		SceneManager::GetInstance().Destory();
		MonoScriptManager::GetInstance().Destory();
		m_bIsStop = true;
	}

	void Application::UpdateApp(float deltaTime)
	{
		if (m_bIsStop)
		{
			return;
		}
		if (m_pBehaviour == nullptr)
		{
			return;
		}
		m_pBehaviour->Update(deltaTime);
	}

	void Application::Destory()
	{
		if (m_pBehaviour == nullptr)
		{
			return;
		}
		m_pBehaviour->Destory();
	}


	void Application::ExitApp()
	{
		StopApp();
		exit(0);
	}

	Application::Application()
	{
		string strPath = "";
#ifdef WIN32
		char exeFullPath[MAX_PATH]; // Full path
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);
#endif
		strPath = (string)exeFullPath;    // Get full path of the file
		int pos = strPath.find_last_of('\\', strPath.length());
		AppDataPath = strPath.substr(0, pos);  // Return the directory without the file name
		ResourcePath = AppDataPath + "/Resource";		
	}

	Application::~Application()
	{
	}
	MonoString* Application::getAppDataPath()
	{
		return mono_string_new(MonoScriptManager::GetInstance().GetEngineDomain(), AppDataPath.c_str());
	}
	MonoString* Application::getResourcePath()
	{
		return mono_string_new(MonoScriptManager::GetInstance().GetEngineDomain(), ResourcePath.c_str());
	}
}