#include "Application.h"
#include "EngineDelegate.h"
#include "../Utils/Include.h"
#include "FilePath.h"

namespace E3DEngine
{
	std::string Application::AppDataPath = "";
	std::string Application::ResourcePath = "";
	bool Application::m_bIsStop = false;
	MonoBehaviour * Application::m_pEntryBehaviour = nullptr;
	MonoBehaviour * Application::m_pBehaviour = nullptr;
	MouseButtonInfo * Application::m_pMouseInfo = nullptr;
	void Application::CreatScript()
	{
        mono_add_internal_call("E3DEngine.Application::getAppDataPath", (const void *)Application::getAppDataPath);
        mono_add_internal_call("E3DEngine.Application::exitApplication", (const void *)Application::ExitApp);
        mono_add_internal_call("E3DEngine.Application::getResourcePath", (const void *)Application::getResourcePath);
	}

	void Application::StartApp()
	{
		m_bIsStop = false;
		MonoScriptManager::GetInstance().Initialize();
		CreatScript();
		m_pMouseInfo = new MouseButtonInfo();
		std::string startApp = AppDataPath + "/app.config";
		std::string fileContent = getContentFromPath(startApp);
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
				m_pEntryBehaviour = new MonoBehaviour;
				m_pEntryBehaviour->SetImage(MonoScriptManager::GetInstance().GetCodeImage());
				m_pEntryBehaviour->Create(entryNameSpce.c_str(), entryClassName.c_str());
				m_pEntryBehaviour->CallMethod("Main");
			}
		}
		else
		{
			Debug::Log(ell_Error, "Application::StartApp ERROR app.config");
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
		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		m_pEntryBehaviour->Update(deltaTime);
	}

	void Application::Destory()
	{
		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		m_pEntryBehaviour->Destory();
	}


	void Application::ExitApp()
	{
		StopApp();
		exit(0);
	}

	Application::Application()
	{
		
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

	void Application::MouseButtonDown(MouseButton btn, vec2f pos)
	{
		m_pMouseInfo->Set(btn, pos.x, pos.y);
		void * args = m_pMouseInfo->GetMonoBehaviour()->GetMonoObject();
		m_pEntryBehaviour->CallMethod(MOUSE_BUTTON_DOWN, &args);
	}

	void Application::MouseButtonUp(MouseButton btn, vec2f pos)
	{
		m_pMouseInfo->Set(btn, pos.x, pos.y);
		void * args = m_pMouseInfo->GetMonoBehaviour()->GetMonoObject();
		m_pEntryBehaviour->CallMethod(MOUSE_BUTTON_UP, &args);
	}

	void Application::MouseMove(vec2f pos)
	{
		m_pMouseInfo->Set(eUnKnown, pos.x, pos.y);
		void * args = m_pMouseInfo->GetMonoBehaviour()->GetMonoObject();
		m_pEntryBehaviour->CallMethod(MOUSE_MOVE, &args);
	}

	void Application::KeyDown(char key)
	{
		KeyCode keyCode = NativeSystem::GetKeyCode(key);
		void *keyChar = &keyCode;
		m_pEntryBehaviour->CallMethod(KEY_DOWN, &keyChar);
	}

	void Application::KeyUp(char key)
	{
		KeyCode keyCode = NativeSystem::GetKeyCode(key);
		void *keyChar = &keyCode;
		m_pEntryBehaviour->CallMethod(KEY_UP, &keyChar);
	}


	MouseButtonInfo::MouseButtonInfo(UINT mBtn, int posX, int posY)
	{
		Set(mBtn, posX, posY);
	}

	void MouseButtonInfo::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(MouseButtonInfo);
		Object::setBehaviourDefaultValue();
	}


	void MouseButtonInfo::Set(UINT mBtn, int posX, int posY)
	{
		CreateBehaviour();
		mButton = mBtn;
		mPositionX = posX;
		mPositionY = posY;
		TRANSFER_FIELD_VALUE(mButton);
		TRANSFER_FIELD_VALUE(mPositionX);
		TRANSFER_FIELD_VALUE(mPositionY);
	}

}
