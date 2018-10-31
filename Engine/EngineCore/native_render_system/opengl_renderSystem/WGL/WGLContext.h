#ifndef __GL_CONTEXT_H__
#define __GL_CONTEXT_H__
#include "../Include/Include.h"

class GL_Context
{

public:
	BOOL OpenGLInit(HDC pDC);

	BOOL SwapBuffer();

	BOOL UseContext();

	BOOL ChangeSurface(HDC pDc);

	HGLRC choosePixelFormat(HDC hDC);

public:
	HGLRC					hglrc;
	HDC						DisplayID;

private:
	void createSecondWnd();
};


#endif
