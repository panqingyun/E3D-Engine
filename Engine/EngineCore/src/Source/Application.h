#pragma once

#include "Interface.h"
#include "../Mono/MonoScriptManager.h"

namespace E3DEngine
{
	class Application
	{
	public:
		Application();
		~Application();
		static void Initialize()
		{
			static Application _app;
		}
		static void CreatScript();
		static void StartApp();
		static void StopApp();
		static void UpdateApp(float deltaTime);
		static void Destory();
		static void ExitApp();

	public:
		static std::string AppDataPath;
		static std::string ResourcePath;

	private:
		static MonoBehaviour *m_pBehaviour;
		static bool m_bIsStop;
		static MonoString* getAppDataPath();
		static MonoString* getResourcePath();
	};
}