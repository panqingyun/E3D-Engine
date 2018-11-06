//
//  GLEngineAPI.c
//
//  Created by 潘庆云 on 2017/1/19.
//

#include <include/EngineAPI.h>
#include "E3DUtil.hpp"
#include "../Source/E3DPlatformConfig.h"
#include "../Mesh/E3DMeshRender.h"
#include "../Source/EngineDelegate.h"
#ifndef WIN32
#include <sys/time.h>
#endif
#include "../Source/Application.h"
#include "../Camera/E3DCamera.h"
/*
 * 接口函数
 */
long getCurrentTime()
{
#ifdef WIN32
	return  GetTickCount();
#else
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}
extern "C"
{
	__api_function_ void InitilizeEngine(bool isEditor)
	{
		E3DEngine::EngineDelegate::GetInstance().Initilize(isEditor);
	}
	
	__api_function_ void StartAppliaction(const char* startScene)
	{
		Application::StartApp(startScene);
	}

	__api_function_ void StopAppliaction()
	{
		Application::StopApp();
	}

	__api_function_ void LogicUpdate()
	{
		static DWORD lastTime = getCurrentTime();
		DWORD curTime = getCurrentTime();
		float _deltaTime = (float)(curTime - lastTime) / 1000.0f;
		lastTime = curTime;
		Time::deltaTime = _deltaTime;
		E3DEngine::EngineDelegate::GetInstance().UpdateLogic(_deltaTime);
		
	}

	__api_function_ void RenderUpdate()
	{
		EngineDelegate::GetInstance().UpdateRender();
	}

	__api_function_ void CreateShareContext()
	{
		GetRenderSystem()->CreateShareContext();
	}
	
	__api_function_ void SetRenderSystem(void* renderSystem)
	{
		SetRenderSystem(static_cast<RenderSystem*>(renderSystem));
	}

	__api_function_ void DestoryEngine()
	{
		E3DEngine::EngineDelegate::GetInstance().Destory();
	}

	__api_function_ void SetAppDataPath(const char * path)
	{
		Application::AppDataPath = path;
		Application::ResourcePath = Application::AppDataPath + "Resource/";
	}

	__api_function_ void PauseEngine(bool bPause)
	{
		E3DEngine::EngineDelegate::GetInstance().SetEnginePause(bPause);
	}

	__api_function_ void ChageFrameSize(int w, int h)
	{
		GetRenderSystem()->setFrameWidth(w);
		GetRenderSystem()->setFrameHeight(h);
		SceneManager::GetCurrentScene()->ChangeViewportSize(w, h);
	}

	__api_function_ void SetDebugLogOutFunc(void * func)
	{
		Debug::OutputLogFunc = (DebugOutput)func;
	}

	__api_function_ void MouseDown(int mouseButtonID, float xPos, float yPos)
	{
		Application::MouseButtonDown((MouseButton)mouseButtonID, vec2f(xPos, yPos));
	}
	__api_function_ void MouseUp(int mouseButtonID, float xPos, float yPos)
	{
		Application::MouseButtonUp((MouseButton)mouseButtonID, vec2f(xPos, yPos));
	}
	__api_function_ void MouseMove(float xPos, float yPos)
	{
		Application::MouseMove(vec2f(xPos, yPos));
	}
	__api_function_ void KeyDown(char key)
	{
		Application::KeyDown(key);
	}
	__api_function_ void KeyUp(char key)
	{
		Application::KeyUp(key);
	}

	__api_function_ void RunGame(bool isRun)
	{
		E3DEngine::EngineDelegate::GetInstance().SetIsRun(isRun);
	}

	__api_function_ void ChangeRenderSurface(NATIVE_WINDOW_TYPE handle)
	{
		GetRenderSystem()->ChangeRenderSurface(handle);
	}
	
	__api_function_ void UpdatePhysics()
	{
		static DWORD _lastTime = getCurrentTime();
		DWORD curTime = getCurrentTime();
		float _deltaTime = (float)(curTime - _lastTime) / 1000.0f;
		_lastTime = curTime;

		EngineDelegate::GetInstance().UpdatePhysics(_deltaTime);
	}

	__api_function_ void SetMonoPath(std::string env_dllPath, std::string assembly_dllPath, std::string engine_dllPath)
	{
		MonoScriptManager::GetInstance().SetMonoPath(env_dllPath, assembly_dllPath, engine_dllPath);
	}

	__api_function_ void RegisterThreadOperateFunc(void *func)
	{
		ThreadTool::GetInstance().RegisterThreadFunc((OpThreadFun)func);
	}
}

/*
 * 全局函数
 */

// returns a random number
inline float asm_rand()
{
#if _MSC_VER == 1300
	
	static unsigned __int64 q = time( nullptr );
	
	_asm {
		movq mm0, q
		
		// do the magic MMX thing
		pshufw mm1, mm0, 0x1E
		paddd mm0, mm1
		
		// move to integer memory location and free MMX
		movq q, mm0
		emms
	}
	
	return float( q );
#else
	// VC6 does not support pshufw
	return float( rand() );
#endif
}

// returns the maximum random number
inline float asm_rand_max()
{
	
#if _MSC_VER == 1300
	return 9223372036854775807.0f;
#else
	return float( RAND_MAX );
#endif
	
}

unsigned int GetPlatform()
{
#if (TARGET_PLATFORM == PLATFORM_ANDROID )
	return PLATFORM_ANDROID;
#elif (TARGET_PLATFORM == PLATFORM_WIN32)
	return PLATFORM_WIN32;
#elif (TARGET_PLATFORM == PLATFORM_IOS)
	return PLATFORM_IOS;
#endif
}

// 随机值： 0.0f - 1.0f
float UnitRandom()
{
	return asm_rand() / asm_rand_max();
}

// 随机值： fLow - fHigh
float RangeRandom( float fLow, float fHigh )
{
	return fLow + ( fHigh - fLow ) * UnitRandom();
}

// 随机值： (-1) - (1)
float SymmetricRandom()
{
	return 2.f * UnitRandom() - 1.f;
}

float RangeNumber(float &number, float max, float min)
{
	if (number > max)
	{
		number = max;
	}
	else if (number < min)
	{
		number = min;
	}
	return number;
}
