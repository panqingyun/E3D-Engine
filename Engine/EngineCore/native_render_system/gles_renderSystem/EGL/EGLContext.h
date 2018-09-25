#ifndef __GL_CONTEXT_H__
#define __GL_CONTEXT_H__
#include "../Include/Include.h"

#ifndef __IOS__
typedef struct
{
	/// Put your user data here...
	void*       userData;
	/// Window width
	GLint       width;
	/// Window height
	GLint       height;
	/// Window handle
	EGLNativeWindowType  hWnd;
	/// EGL display
	EGLDisplay  eglDisplay;
	/// EGL context
	EGLContext  eglContext;
	/// EGL surface 
	EGLSurface  eglSurface;
} ESContext;
#endif

class EGL_Context
{
#ifndef __IOS__
public:
	void InitGLES(EGLNativeDisplayType displayID, EGLNativeWindowType windowHandle, bool isOffScreen = false);

	void SwapBuffer();

	bool UseContext();

	void ChangeSurface(EGLNativeWindowType windowHandle);

protected:
	EGLBoolean CreateEGLEnv(bool isOffScreen);

	EGLBoolean createSurface(bool isOffScreen, EGLConfig config);

	EGLBoolean chooseConfig(bool isOffScreen,  EGLConfig& config, EGLint& numConfigs);

public:
	ESContext			*	pESContext;
	EGLNativeDisplayType	DisplayID;
	EGLNativeWindowType		WindowID;
	GLuint					OffScreenWidth;
	GLuint					OffScreenHeight;
	EGLint					AttribList[15];
	EGLConfig				Config;
	EGLint					MajorVersion;
	EGLint					MinorVersion;
#endif
};


#endif
