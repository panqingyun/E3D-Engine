// 这是主 DLL 文件。

#include "stdafx.h"

#include "EditorDll.h"
#include <EngineAPI.h>
#include <RenderSystemAPI.h>

#pragma managed
void E3DEngine::EngineDelegateRef::InitilizeEngine()
{
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

void E3DEngine::EngineDelegateRef::SetupRenderSystem(IntPtr nativeWindow, int width, int height)
{
	::SetRenderSystem(CreateRenderSystem((HWND)nativeWindow.ToInt32(), width, height));
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

void E3DEngine::EngineDelegateRef::EngineUpdate()
{
	::EngineUpdate();
}

void E3DEngine::EngineDelegateRef::DestoryEngine()
{
	::DestoryEngine();
}

void E3DEngine::EngineDelegateRef::PauseEngine(bool bPause)
{
	::PauseEngine(bPause);
}

void E3DEngine::EngineDelegateRef::ChageFrameSize(int w, int h)
{
	::ChageFrameSize(w, h);
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

void E3DEngine::EngineDelegateRef::CreateEditor()
{
	::CreateEditor();
}

void E3DEngine::EngineDelegateRef::ChangeSurface(IntPtr nativeWindow)
{
	::ChangeRenderSurface((HWND)nativeWindow.ToInt32());
}
#pragma unmanaged