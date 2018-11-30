// EditorDll.h

#pragma once

#include <EngineAPI.h>
using namespace System;

#pragma  managed
namespace E3DEngine 
{
	public ref class RenderSystemType
	{
	public:
		static int OPENGL = 0;
		static int OPENGLES = 1;
	};

	public ref class ThreadInfoDefine
	{
	public:
		static int LOGIC_THREAD_ID	= 0;
		static int PHYSIC_THREAD_ID = 1;
		static int RENDER_THREAD_ID = 2;

		static int SUSPEND_THREAD	= 0;
		static int RESUME_THREAD	= 1;
		static int LOCK_THREAD		= 2;
		static int LOCK_END			= 3;
	};

	public ref class EngineDelegateRef
	{
	public: 
		void InitilizeEngine();
		void StartAppliaction();
		void StopAppliaction();
		void SetupRenderSystem(int renderSystem, IntPtr nativeWindow, int width, int height);
		void SetDebugLogOutFunc(IntPtr func);
		void SetAppDataPath(String^ path);
		void LogicUpdate();
		void RenderUpdate();
		void DestoryEngine();
		void CreateShareContext();
		void PauseEngine(bool bPause);
		void ChageFrameSize(int w, int h);
		void MouseDown(int mouseButtonID, float xPos, float yPos);
		void MouseUp(int mouseButtonID, float xPos, float yPos);
		void MouseMove(float xPos, float yPos);
		void KeyDown(char key);
		void KeyUp(char key);
		void ChangeSurface(IntPtr nativeWindow);
		void RunCurrentScene(bool run);
		void UpdatePhysics();
		void SetMonoPath(System::String^ env_dllPath, System::String^ assembly_dllPath, System::String^ engine_dllPath);
		void RegisterThreadFunc(IntPtr fun);
		int GetFPS();
	private:
		bool mInRun;
		void *m_pRenderSystem;
	};
}
#pragma unmanaged