
#include "EGLContext.h"
#include <assert.h>
#include <src/RenderSystem/E3DRenderSystem.hpp>

#ifndef __IOS__
/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1 
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2 
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8
#endif

#ifdef WIN32
EGLBoolean EGL_Context::CreateEGLEnv(bool isOffScreen)
{
	EGLint numConfigs;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	pESContext->eglDisplay = eglGetDisplay(DisplayID);

	if (pESContext->eglDisplay == EGL_NO_DISPLAY)
	{
		return EGL_FALSE;
	}

	if (!eglInitialize(pESContext->eglDisplay, &MajorVersion, &MinorVersion))
	{
		return EGL_FALSE;
	}

	if (!eglGetConfigs(pESContext->eglDisplay, nullptr, 0, &numConfigs))
	{
		return EGL_FALSE;
	}

	if (!chooseConfig(isOffScreen, Config, numConfigs))
	{
		return EGL_FALSE;
	}

	if (!createSurface(isOffScreen, Config))
	{
		return EGL_FALSE;
	}
	pESContext->eglContext = eglCreateContext(pESContext->eglDisplay, Config, EGL_NO_CONTEXT, contextAttribs);
	
	if (pESContext->eglContext == EGL_NO_CONTEXT)
	{
		return EGL_FALSE;
	};
	return UseContext();
}
#endif

void EGL_Context::ChangeSurface(EGLNativeWindowType windowHandle)
{
	pESContext->hWnd = windowHandle;
	createSurface(false, Config);
}

void EGL_Context::UseShareContext()
{
	eglMakeCurrent(pESContext->eglDisplay, pESContext->eglSurface, pESContext->eglSurface, eglShareContext);
}


void EGL_Context::CreateShareContext()
{
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
	eglShareContext = eglCreateContext(pESContext->eglDisplay, Config, pESContext->eglContext, contextAttribs);
	glFlush();
}

EGLBoolean EGL_Context::chooseConfig(bool isOffScreen, EGLConfig &config, EGLint &numConfigs)
{
	if (isOffScreen)
	{
		EGLint attribList[] =
		{
			EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_RED_SIZE, 5,
			EGL_GREEN_SIZE, 6,
			EGL_BLUE_SIZE, 5,
			EGL_DEPTH_SIZE, 1,
			EGL_NONE
		};
		if (!eglChooseConfig(pESContext->eglDisplay, attribList, &config, 1, &numConfigs))
		{
			return EGL_FALSE;
		}
	}
	else
	{
		BOOL flags = GL_TRUE;
		EGLint attribList[] =
		{
			EGL_RED_SIZE,       8,
			EGL_GREEN_SIZE,     8,
			EGL_BLUE_SIZE,      8,
			EGL_ALPHA_SIZE,      8,
			EGL_DEPTH_SIZE,      8,
			EGL_STENCIL_SIZE,	 8,
			EGL_SAMPLE_BUFFERS,  1,
			EGL_SAMPLES, 4,
			EGL_NONE
		};
		if (!eglChooseConfig(pESContext->eglDisplay, attribList, &config, 1, &numConfigs))
		{
			return EGL_FALSE;
		}
	}
	return EGL_TRUE;
}

void EGL_Context::InitGLES(EGLNativeDisplayType displayID, EGLNativeWindowType windowHandle, bool isOffScreen)
{
	pESContext = new ESContext;
	if (pESContext != nullptr)
	{
		memset(pESContext, 0, sizeof(ESContext));
	}
	pESContext->hWnd = windowHandle;
	DisplayID = displayID;
	if (!CreateEGLEnv(isOffScreen))
	{
		assert(false);
	}
}

void EGL_Context::SwapBuffer()
{
	glFinish();
	eglSwapBuffers(pESContext->eglDisplay, pESContext->eglSurface);
}

bool EGL_Context::UseContext()
{
	return eglMakeCurrent(pESContext->eglDisplay, pESContext->eglSurface, pESContext->eglSurface, pESContext->eglContext);
}

EGLBoolean EGL_Context::createSurface(bool isOffScreen, EGLConfig config)
{
	EGLSurface surface = nullptr;
	if (isOffScreen)
	{
		EGLint PBufAttribs[] =
		{
			EGL_WIDTH, OffScreenWidth,
			EGL_HEIGHT, OffScreenHeight,
			EGL_LARGEST_PBUFFER, EGL_TRUE,
			EGL_NONE
		};
		surface = eglCreatePbufferSurface(pESContext->eglDisplay, config, PBufAttribs);
	}
	else
	{
		surface = eglCreateWindowSurface(pESContext->eglDisplay, config, (EGLNativeWindowType)pESContext->hWnd, nullptr);
	}

	if (surface == EGL_NO_SURFACE)
	{
		return EGL_FALSE;
	}

	// Check to see what size pbuffer we were allocated
	if (isOffScreen)
	{
		EGLint os_width;
		EGLint os_height;
		if (!eglQuerySurface(pESContext->eglDisplay, surface, EGL_WIDTH, &os_width) ||
			!eglQuerySurface(pESContext->eglDisplay, surface, EGL_HEIGHT, &os_height))
		{
			return EGL_FALSE;
		}
	}
	pESContext->eglSurface = surface;
	return EGL_TRUE;
}

