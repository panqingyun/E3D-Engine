//
//  GLEngineAPI.c
//
//  Created by 潘庆云 on 2017/1/19.
//

#include <include/EngineAPI.h>
#include "E3DUtil.hpp"
#include "../Source/E3DPlatformConfig.h"
#include "../Mesh/E3DMesh.h"
#include "../Source/EngineDelegate.h"
#include "../../include/Include.h"
#ifdef __IOS__
#include <sys/time.h>
#endif
/*
 * 接口函数
 */
long getCurrentTime()
{
#ifndef WIN32
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
#ifdef WIN32
	return  GetTickCount();
#endif
}
extern "C"
{
#ifdef WIN32
#include "..\..\extern\windows_net\E3DNet.h"
#endif
//#include "../../gles_renderSystem/E3DGLESRenderSystem.hpp"
	__api_function_ void InitilizeEngine()
	{
#ifdef WIN32
		E3DNet::GetInstance().InitLogic();
#endif
		E3DEngine::EngineDelegate::GetInstance().Initilize();
	}
	
	__api_function_ void StartAppliaction()
	{
		Application::StartApp();
	}
	__api_function_ void StopAppliaction()
	{
		Application::StopApp();
	}
	__api_function_ void SetupGLBuffer()
	{
		//E3DEngine::EngineDelegate::GetInstance().GetRenderSystem()->SetupDefaultFrameBuffer();
	}

	__api_function_ void EngineUpdate()
	{
		static DWORD lastTime = getCurrentTime();
		DWORD curTime = getCurrentTime();
		float _deltaTime = (float)(curTime - lastTime) / 1000.0f;
		lastTime = curTime;
		Time::deltaTime = _deltaTime;
#ifdef WIN32
		E3DNet::GetInstance().Update(_deltaTime);
#endif
		E3DEngine::EngineDelegate::GetInstance().Update(_deltaTime, true);
		
	}

	__api_function_ void DestoryEngine()
	{
#ifdef WIN32
		E3DNet::GetInstance().Destory();
#endif
		E3DEngine::EngineDelegate::GetInstance().Destory();
	}

	__api_function_ void SetAppDataPath(const char * path)
	{
		Application::AppDataPath = path;
		Application::ResourcePath = Application::AppDataPath + "/Resource";
	}

	__api_function_ void PauseEngine(bool bPause)
	{
		E3DEngine::EngineDelegate::GetInstance().SetEnginePause(bPause);
	}

	__api_function_ void ChageFrameSize(int w, int h)
	{
		GetRenderSystem()->setFrameWidth(w);
		GetRenderSystem()->setFrameHeight(h);
		SceneManager::GetInstance().GetCurrentScene()->ChangeFrameSize(w, h);
	}

	__api_function_ void SetupRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height)
	{
		CreateRenderSystem(nativeWindow, width, height);
	}

	__api_function_ void setDebugLogOutFunc(void * func)
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


void ChangeFileNameToDDS( string &name )
{
	basic_string <char>::size_type indexChar = name.find_last_of( '.' );
	if( indexChar != -1 )
	{
		name = name.substr( 0, indexChar ) + ".dds";
	}
}

vec3f V42V3(vec4f vec)
{
	vec3f v3(vec.x,vec.y,vec.z);
	return v3;
}

vec4f V32V4(vec3f vec)
{
	vec4f v4(vec.x, vec.y, vec.z, 1.0f);
	return v4;
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
mat4f ConvertAiMatrix4x42Mat4f(aiMatrix4x4 aiMat)
{
	mat4f mat4;
	for (int i = 0; i < 4; ++ i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat4.at(i, j) = aiMat[i][j];
		}
	}
	return mat4;
}
