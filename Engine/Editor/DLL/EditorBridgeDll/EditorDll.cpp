// 这是主 DLL 文件。

#include "stdafx.h"

#include "EditorDll.h"
#include <EngineAPI.h>
#include <ESRenderSystemAPI.h>
#include <GLRenderSystemAPI.h>
#include "Scene.h"

#pragma managed
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
void E3DEngine::EngineDelegateRef::InitilizeEngine()
{
	m_pRenderSystem = nullptr;
	::InitilizeEngine(true);
}

void E3DEngine::EngineDelegateRef::StartAppliaction()
{
	::StartAppliaction();
}

void E3DEngine::EngineDelegateRef::StopAppliaction()
{
	::StopAppliaction();
}

void E3DEngine::EngineDelegateRef::SetupRenderSystem(int renderSystemType, IntPtr nativeWindow, int width, int height)
{
	if (renderSystemType == RenderSystemType::OPENGL)
	{
		m_pRenderSystem = CreateGLRenderSystem((HWND)nativeWindow.ToInt32(), width, height);
	}
	else if(renderSystemType == RenderSystemType::OPENGLES)
	{
		m_pRenderSystem = CreateGLESRenderSystem((HWND)nativeWindow.ToInt32(), width, height);
	}
	::SetRenderSystem(m_pRenderSystem);
}

void E3DEngine::EngineDelegateRef::SetDebugLogOutFunc(IntPtr func)
{
	::SetDebugLogOutFunc((void*)func.ToInt32());
}

void E3DEngine::EngineDelegateRef::SetAppDataPath(String^  path)
{
	char* ch2 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path);
	::SetAppDataPath(ch2);
}

void E3DEngine::EngineDelegateRef::LogicUpdate()
{
	SceneManageRef::GetInstance()->GetCurScene()->Update(0.02f);
	::LogicUpdate();
	SceneManageRef::GetInstance()->GetCurScene()->AfterUpdate(0.02f);
	SceneManageRef::GetInstance()->Update(0.02f);
}

void E3DEngine::EngineDelegateRef::RenderUpdate()
{
	::RenderUpdate();
}

void E3DEngine::EngineDelegateRef::DestoryEngine()
{
	::DestoryEngine();
}

void E3DEngine::EngineDelegateRef::CreateShareContext()
{
	::CreateShareContext();
}

void E3DEngine::EngineDelegateRef::PauseEngine(bool bPause)
{
	::PauseEngine(bPause);
}

void E3DEngine::EngineDelegateRef::ChageFrameSize(int w, int h)
{
	::ChageFrameSize(w, h);
	SceneManageRef::GetInstance()->OnFrameSizeChange();
}

void E3DEngine::EngineDelegateRef::MouseDown(int mouseButtonID, float xPos, float yPos)
{
	::MouseDown(mouseButtonID, xPos, yPos);
}

void E3DEngine::EngineDelegateRef::MouseUp(int mouseButtonID, float xPos, float yPos)
{
	::MouseUp(mouseButtonID, xPos, yPos);
}

void E3DEngine::EngineDelegateRef::MouseMove(float xPos, float yPos)
{
	::MouseMove(xPos, yPos);
}

void E3DEngine::EngineDelegateRef::KeyDown(char key)
{
	::KeyDown(key);
}

void E3DEngine::EngineDelegateRef::KeyUp(char key)
{
	::KeyUp(key);
}

void E3DEngine::EngineDelegateRef::ChangeSurface(IntPtr nativeWindow)
{
	::ChangeRenderSurface((HWND)nativeWindow.ToInt32());
}

void E3DEngine::EngineDelegateRef::RunCurrentScene(bool run)
{
	mInRun = run;
	::RunGame(run);
}

void E3DEngine::EngineDelegateRef::UpdatePhysics()
{
	::UpdatePhysics();
}

void E3DEngine::EngineDelegateRef::SetMonoPath(System::String^ env_dllPath, System::String^ assembly_dllPath, System::String^ engine_dllPath)
{
	::SetMonoPath(marshal_as<std::string>(env_dllPath),
		marshal_as<std::string>(assembly_dllPath),
		marshal_as<std::string>(engine_dllPath));
}

void E3DEngine::EngineDelegateRef::RegisterThreadFunc(IntPtr fun)
{
	::RegisterThreadOperateFunc((void*)fun.ToInt32());
}

#pragma unmanaged