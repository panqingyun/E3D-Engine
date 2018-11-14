#pragma once

#include "Interface.h"
#include "../Mono/MonoScriptManager.h"
#include "../Object/E3DObject.h"
#include "../Camera/E3DCamera.h"
#include "../Object/E3DCoordinate.h"

#ifdef __E3D_EDITOR__
extern "C"
{
	const std::vector<E3DEngine::Camera *> &GetEditorCameras();
	E3DEngine::Camera *GetEditorMainCamera();
	E3D_EXPORT_DLL void SetEditorCamera(E3DEngine::Camera *eCamera, bool isMainCamera);
}
#endif

namespace E3DEngine
{
	enum MouseButton
	{
		eLeftButton = 0,
		eRightButton,
		eMiddleButton,
		eUnKnown
	};

	class MouseButtonInfo : public Object
	{
	public:
		MouseButtonInfo() { }
		MouseButtonInfo(UINT mBtn, int posX, int posY);

		virtual void CreateBehaviour();
		void Set(UINT mBtn, int posX, int posY);
		int mButton;
		int mPositionX;
		int mPositionY;
	};

	class E3D_EXPORT_DLL Application : public IObject
	{
	public:
		Application();
		~Application();
		static void Initialize()
		{
			static Application _app;
		}
		static void CreatScript();
		static void StartApp(std::string sceneName = "");

		static void StopApp();
		static void UpdateApp(float deltaTime);
		static void Destory();
		static void ExitApp();
		static void MouseButtonDown(MouseButton mButton, vec2f pos);
		static void MouseButtonUp(MouseButton mButton, vec2f pos);
		static void MouseMove(vec2f position);
		static void KeyDown(char key);
		static void KeyUp(char key);
		static double GetTimeSinceStart();
		static float GetFPS();

	public:
		static std::string AppDataPath;
		static std::string ResourcePath;
		static std::string EditorDataPath;

	private:
		static void startCSharp(std::vector<std::string> &vestr, std::string sceneName);
	private:
		static MonoBehaviour *m_pEntryBehaviour;
		static MonoBehaviour *m_pBehaviour;
		static bool m_bIsStop;
		static double m_nRunTimeLong;
		static MouseButtonInfo * m_pMouseInfo;
		static MonoString* getAppDataPath();
		static MonoString* getResourcePath();
		static float m_fDeltaTime;
	};
}