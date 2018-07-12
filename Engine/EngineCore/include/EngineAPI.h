//
//  EngineAPI.h
//  Created by 潘庆云 on 2017/1/19.
//

/*
* 对外导出接口  
* 
*/

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
#define UINT unsigned int
#define __api_function_ __attribute__ ((visibility("default")))
#endif

#ifdef WIN32 
typedef HWND NATIVE_WINDOW_TYPE;
#else
#define NATIVE_WINDOW_TYPE void *
#define EGLNativeDisplayType void *
#define EGLNativeWindowType NATIVE_WINDOW_TYPE
#define EGL_DEFAULT_DISPLAY 0
#endif

//////////////////////////////////////////////////////////////////////////
/// dll export function
//////////////////////////////////////////////////////////////////////////
extern "C"
{
	/// <summary>
	/// 初始化
	/// </summary>
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
	/// 创建RenderSystem
	/// </summary>
	/// <param name = "width"> 渲染视口宽度 </param>
	/// <param name = "height"> 渲染视口高度 </param> 
#ifdef OPEN_GL_ES
	// 启动OPEN_GL_ES
	__api_function_ void SetupRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height);
#endif
#ifdef D3D_11
	// TODO 启动D3D_11 渲染
#endif
#ifdef D3D_9
	// TODO 启动D3D_9渲染
#endif
#ifdef OPEN_GL
	// TODO 启动OPEN_GL渲染
#endif
	///------------------------------------------------------
	/// 日志输出
	__api_function_ void SetDebugLogOutFunc(void * func);
	///------------------------------------------------------
	/// <summary>
	/// 设置运行，目录
	/// </summary>
	__api_function_ void SetAppDataPath(const char * path);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name = "deltaTime"> 时间 </param>
	__api_function_ void EngineUpdate();
	/// <summary>
	/// 销毁
	/// </summary>
	__api_function_ void DestoryEngine();
	/// <summary>
	/// 暂停或恢复运行
	/// </summary>
	__api_function_ void PauseEngine(bool bPause);
	/// <summary>
	/// 修改渲染缓冲区尺寸
	/// </summary>
	__api_function_ void ChageFrameSize(int w, int h);
	/// <summary>
	/// 鼠标 或手指按下
	/// </summary>
	/// <param name = "mouseButtonID">鼠标键ID 0 左键 1 右键 2 中键</param>
	__api_function_ void MouseDown(int mouseButtonID, float xPos, float yPos);
	/// <summary>
	/// 鼠标或手指抬起
	/// </summary>
	/// <param name = "mouseButtonID">鼠标键ID 0 左键 1 右键 2 中键</param>
	__api_function_ void MouseUp(int mouseButtonID, float xPos, float yPos);
	/// <summary>
	/// 鼠标或手指移动
	/// </summary>
	__api_function_ void MouseMove(float xPos, float yPos);
	/// <summary>
	/// 按键按下
	/// </summary>
	/// <param name = "key">按键字符值</param>
	__api_function_ void KeyDown(char key);
	/// <summary>
	/// 按键抬起
	/// </summary>
	/// <param name = "key">按键字符值</param>
	__api_function_ void KeyUp(char key);	
	/// <summary>
	/// 编辑器的地格
	/// </summary>
	__api_function_ void CreateEditorGrid();
	/// <summary>
	/// 编辑器的摄像机
	/// </summary>
	__api_function_ void CreateEditorCamera();

}

#endif /* GLEngineAPI_h */
