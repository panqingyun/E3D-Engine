#include "Application.h"
#include "EngineDelegate.h"
#include "../Utils/Include.h"
#include "FilePath.h"
#include "../Scene/E3DSceneLoader.h"

#ifdef __E3D_EDITOR__
extern "C"
{
	float cameraRotateX = 0, cameraRotateY = 0;
	bool mouseRButtonDown = false, mouseMButtonDown = false;
	vec2f curMousePosition;
	vec2f lastMousePosition;
	vec3f cameraRotation;
	vec3f curPos;
	vec3f curCameraPos;
	vec3f curCameraDir;
	float speed = 0.5f;
	std::vector<Camera *> editorCameras;
	Camera *mainEditorCamera = nullptr;
	
	Camera *GetEditorMainCamera()
	{
		return mainEditorCamera;
	}

	void editorMouseButtonDown(MouseButtonInfo* mouseInfo)
	{
		if (EngineDelegate::GetInstance().GetIsRun())
			return;
		lastMousePosition.x = mouseInfo->mPositionX;
		lastMousePosition.y = mouseInfo->mPositionY;
		if (mouseInfo->mButton == eRightButton)
		{
			mouseRButtonDown = true;
		}
		else if (mouseInfo->mButton == eMiddleButton)
		{
			mouseMButtonDown = true;
		}
	}

	void editorMouseButtonUp(MouseButtonInfo *mouseInfo)
	{
		if (EngineDelegate::GetInstance().GetIsRun())
			return;
		if (mouseInfo->mButton == eRightButton)
		{
			mouseRButtonDown = false;
		}
		else if (mouseInfo->mButton == eMiddleButton)
		{
			mouseMButtonDown = false;
		}
	}

	void editorMouseMove(MouseButtonInfo* mouseInfo)
	{
		if (mainEditorCamera == nullptr)
			return;
		if (EngineDelegate::GetInstance().GetIsRun())
			return;
		curMousePosition.x = mouseInfo->mPositionX;
		curMousePosition.y = mouseInfo->mPositionY;

		if (mouseRButtonDown)
		{
			float rotaX = curMousePosition.y - lastMousePosition.y;
			float rotaY = curMousePosition.x - lastMousePosition.x;

			lastMousePosition = curMousePosition;

			cameraRotateX += rotaX * 0.2f;
			cameraRotateY += rotaY * 0.2f;
			cameraRotation = vec3f(-cameraRotateX, -cameraRotateY, 0);
			mainEditorCamera->Transform->SetRotation(cameraRotation);
		}
		else if (mouseMButtonDown)
		{
			curPos = vec3f(-curMousePosition.x + lastMousePosition.x, curMousePosition.y - lastMousePosition.y, 0);

			vec3f dir = mainEditorCamera->GetViewInverseMatrix() * curPos;
			dir.normalize();
			vec3f newPos = mainEditorCamera->Transform->Position + dir;
			lastMousePosition = curMousePosition;
			mainEditorCamera->Transform->SetPosition(newPos);
		}
	}

	void editorKeyDown(KeyCode keyCode)
	{
		if (mainEditorCamera == nullptr)
			return;
		if (EngineDelegate::GetInstance().GetIsRun())
			return;
		curCameraPos = mainEditorCamera->Transform->Position;
		if (keyCode == KeyW)
		{
			curCameraDir = mainEditorCamera->GetForwardVector();
			curCameraDir.normalize();
			mainEditorCamera->Transform->SetPosition(curCameraPos + curCameraDir* speed);
		}
		else if (keyCode == KeyS)
		{
			curCameraDir = mainEditorCamera->GetForwardVector() * -1;
			curCameraDir.normalize();
			mainEditorCamera->Transform->SetPosition(curCameraPos + curCameraDir * speed);
		}
		else if (keyCode == KeyA)
		{
			curCameraDir = mainEditorCamera->GetRigthVector() * -1 * speed;
			curCameraDir.normalize();
			mainEditorCamera->Transform->SetPosition(curCameraPos + curCameraDir * speed);
		}
		else if (keyCode == KeyD)
		{
			curCameraDir = mainEditorCamera->GetRigthVector() * speed;
			curCameraDir.normalize();
			mainEditorCamera->Transform->SetPosition(curCameraPos + curCameraDir * speed);
		}
		else if (keyCode == KeyE)
		{
			curCameraDir = mainEditorCamera->GetUpVector() * speed;
			curCameraDir.normalize();
			mainEditorCamera->Transform->SetPosition(curCameraPos + curCameraDir * speed);
		}
		else if (keyCode == KeyQ)
		{
			curCameraDir = mainEditorCamera->GetUpVector() * -1 * speed;
			curCameraDir.normalize();
			mainEditorCamera->Transform->SetPosition(curCameraPos + curCameraDir * speed);
		}
	}

	void editorKeyUp(KeyCode keyCode)
	{
		/*if (editorCamera == nullptr)
			return;
		if (EngineDelegate::GetInstance().GetIsRun())
			return;*/
	}

	E3D_EXPORT_DLL void SetEditorCamera(E3DEngine::Camera *eCamera, bool isMainCamera)
	{
		if (isMainCamera)
		{
			mainEditorCamera = eCamera;
		}
		bool bCanInsert = true;
		for (auto &camera : editorCameras)
		{
			if (camera->ID == eCamera->ID)
			{
				bCanInsert = false;
				break;
			}
		}
		if (bCanInsert)
		{
			editorCameras.emplace_back(eCamera);
		}
	}
	const std::vector<E3DEngine::Camera *> &GetEditorCameras()
	{
		return editorCameras;
	}
}


#endif

namespace E3DEngine
{
	std::string Application::AppDataPath = "";
	std::string Application::ResourcePath = "";
	bool Application::m_bIsStop = false;
	MonoBehaviour * Application::m_pEntryBehaviour = nullptr;
	MonoBehaviour * Application::m_pBehaviour = nullptr;
	MouseButtonInfo * Application::m_pMouseInfo = nullptr;
	double Application::m_nRunTimeLong = 0;
	float Application::m_fDeltaTime = 0;

	void Application::CreatScript()
	{
        mono_add_internal_call("E3DEngine.Application::getAppDataPath", (const void *)Application::getAppDataPath);
        mono_add_internal_call("E3DEngine.Application::exitApplication", (const void *)Application::ExitApp);
        mono_add_internal_call("E3DEngine.Application::getResourcePath", (const void *)Application::getResourcePath);
	}

	void Application::StartApp(std::string sceneName)
	{
		m_bIsStop = false;
		m_nRunTimeLong = 0;
		MonoScriptManager::GetInstance().Initialize();
		CreatScript();
		std::string startApp = AppDataPath + "/app.config";
		std::string fileContent = getContentFromPath(startApp);
		if (fileContent != empty_string)
		{
			std::vector<std::string> vestr = E3DEngine::StringBuilder::Split(fileContent, "\n");
			for (auto &cfg : vestr)
			{
				if (cfg.find("entryClass") != std::string::npos)
				{
					std::vector<std::string> entryConfig = E3DEngine::StringBuilder::Split(cfg, "=");
					startCSharp(entryConfig, sceneName);
				}
				else if (cfg.find("debugWindow") != std::string::npos)
				{

				}
			}
		}
		else
		{
			Debug::Log(ell_Error, "Application::StartApp ERROR app.config");
			assert(false);
		}
		m_pMouseInfo = new MouseButtonInfo();
	}

	void Application::startCSharp(std::vector<std::string> &vestr, std::string sceneName)
	{
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
			if (sceneName == "")
			{
				m_pEntryBehaviour->CallMethod("Main");
			}
			else
			{
				SceneManager::GetInstance().LoadScene(sceneName);
			}
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
		m_nRunTimeLong += deltaTime;
		m_fDeltaTime = deltaTime;
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

		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			void * args = m_pMouseInfo->GetMonoBehaviour()->GetMonoObject();
			m_pEntryBehaviour->CallMethod(MOUSE_BUTTON_DOWN, &args);
		}
#ifdef __E3D_EDITOR__
		else
		{
			editorMouseButtonDown(m_pMouseInfo);
		}
#endif
	}

	void Application::MouseButtonUp(MouseButton btn, vec2f pos)
	{
		m_pMouseInfo->Set(btn, pos.x, pos.y);

		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			void * args = m_pMouseInfo->GetMonoBehaviour()->GetMonoObject();
			m_pEntryBehaviour->CallMethod(MOUSE_BUTTON_UP, &args);
		}
#ifdef __E3D_EDITOR__
		else
		{
			editorMouseButtonUp(m_pMouseInfo);
		}
#endif
	}

	void Application::MouseMove(vec2f pos)
	{
		m_pMouseInfo->Set(eUnKnown, pos.x, pos.y);

		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			void * args = m_pMouseInfo->GetMonoBehaviour()->GetMonoObject();
			m_pEntryBehaviour->CallMethod(MOUSE_MOVE, &args);
		}
#ifdef __E3D_EDITOR__
		else
		{
			editorMouseMove(m_pMouseInfo);
		}
#endif
	}

	void Application::KeyDown(char key)
	{
		KeyCode keyCode = NativeSystem::GetKeyCode(key);

		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			void *keyChar = &keyCode;
			m_pEntryBehaviour->CallMethod(KEY_DOWN, &keyChar);
		}
#ifdef __E3D_EDITOR__
		else
		{
			editorKeyDown(keyCode);
		}
#endif
	}

	void Application::KeyUp(char key)
	{
		KeyCode keyCode = NativeSystem::GetKeyCode(key);

		if (m_pEntryBehaviour == nullptr)
		{
			return;
		}
		if (EngineDelegate::GetInstance().GetIsRun())
		{
			void *keyChar = &keyCode;
			m_pEntryBehaviour->CallMethod(KEY_UP, &keyChar);
		}
#ifdef __E3D_EDITOR__
		else
		{
			editorKeyUp(keyCode);
		}
#endif
	}


	double Application::GetTimeSinceStart()
	{
		return m_nRunTimeLong;
	}


	float Application::GetFPS()
	{
		return 1.0 / m_fDeltaTime;
	}

	MouseButtonInfo::MouseButtonInfo(UINT mBtn, int posX, int posY)
	{
		Set(mBtn, posX, posY);
	}

	void MouseButtonInfo::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
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
