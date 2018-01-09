//
//  EngineAPI.h
//  Created by 潘庆云 on 2017/1/19.
//

#ifndef GLEngineAPI_h
#define GLEngineAPI_h

#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <set>

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define DEPRECATED_ATTRIBUTE
#endif

#ifdef _WIN32
#include <windows.h>
#include <iterator> 
#define __api_function_  __declspec(dllexport)
#else
define UINT unsigned int
#define __api_function_ __attribute__ ((visibility("default")))
#endif

#ifdef WIN32 
typedef HWND NATIVE_WINDOW_TYPE;
#endif
#ifdef __ANDROID__
#define NATIVE_WINDOW_TYPE void *
#endif
enum RenderSystemType
{
	eRS_D3D,
	eRS_GL,
	eRS_GLES2,
};

//////////////////////////////////////////////////////////////////////////
/// dll export function
//////////////////////////////////////////////////////////////////////////
extern "C"
{
	/// <summary>
	/// 初始化
	/// </summary>
	/// <param> screenWidth </param>  屏幕宽度
	/// <param> screenHeight </param> 屏幕高度
	__api_function_ void InitilizeEngine();
	/// <summary>
	/// 启动程序脚本
	/// </summary>
	__api_function_ void StartAppliaction();
	/// <summary>
	/// 关闭程序脚本
	/// </summary>
	__api_function_ void StopAppliaction();
	/// <summary>
	/// 初始化OpenGLES IOS 创建默认的fbo
	/// </summary>
	__api_function_ void SetupGLBuffer();
	/// <summary>
	/// 创建EGL
	/// </summary>
	__api_function_ void SetupRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height);
	///------------------------------------------------------
	/// 日志输出
	__api_function_ void setDebugLogOutFunc(void * func);
	///------------------------------------------------------

	/// <summary>
	/// 更新
	/// </summary>
	/// <param> deltaTime </param>  时间
	__api_function_ void EngineUpdate();
	/// <summary>
	/// 销毁
	/// </summary>
	__api_function_ void DestoryEngine();
	/// <summary>
	/// 暂停或恢复引擎
	/// </summary>
	__api_function_ void PauseEngine(bool bPause);
	/// <summary>
	/// 修改宽高
	/// </summary>
	__api_function_ void ChageFrameSize(int w, int h);
	/// <summary>
	/// 鼠标 或手指按下
	/// </summary>
	/// <param name = mouseButtonID>鼠标键ID 0 左键 1 右键 2 中键</param>
	__api_function_ void MouseDown(int mouseButtonID, float xPos, float yPos);
	/// <summary>
	/// 鼠标或手指抬起
	/// </summary>
	/// <param name = mouseButtonID>鼠标键ID 0 左键 1 右键 2 中键</param>
	__api_function_ void MouseUp(int mouseButtonID, float xPos, float yPos);
	/// <summary>
	/// 鼠标或手指移动
	/// </summary>
	__api_function_ void MouseMove(float xPos, float yPos);
	/// <summary>
	/// 按键按下
	/// </summary>
	/// <param name = key>按键字符值</param>
	__api_function_ void KeyDown(char key);
	/// <summary>
	/// 按键抬起
	/// </summary>
	/// <param name = key>按键字符值</param>
	__api_function_ void KeyUp(char key);	

}

#endif /* GLEngineAPI_h */
