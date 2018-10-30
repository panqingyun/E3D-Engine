
#include "WGLContext.h"
#include <src/RenderSystem/E3DRenderSystem.hpp>

BOOL GL_Context::SwapBuffer()
{
	glFlush();
	return ::SwapBuffers(DisplayID);
}

BOOL GL_Context::UseContext()
{
	return wglMakeCurrent(DisplayID,hglrc);
}


BOOL GL_Context::ChangeSurface(HDC pDc)
{
	return FALSE;
}

BOOL GL_Context::OpenGLInit(HDC pDC)
{
	int n;								//当前选择的像素格式索引
	DisplayID = pDC;
	static PIXELFORMATDESCRIPTOR pfd =
	{									//像素点格式信息描述结构体
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |		//支持Windows与OpenGL二环境绘图
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,			//使用双缓存交换显示图形
		PFD_TYPE_RGBA,			    // RGBA type 
		32,							// 32-bit color depth 
		0, 0, 0, 0, 0, 0,			// color bits ignored 
		0,							// no alpha buffer 
		0,							// shift bit ignored 
		0,							// no accumulation buffer 
		0, 0, 0, 0,					// accum bits ignored 
		32,							// 32-bit z-buffer     
		8,							// no stencil buffer 
		0,							// no auxiliary buffer 
		PFD_MAIN_PLANE,				// main layer 
		0,							// reserved 
		0, 0, 0						// layer masks ignored 
	};

	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(pDC, &pfd)) == 0)
	{
		return FALSE;
	}

	if (SetPixelFormat(pDC, pixelformat, &pfd) == FALSE)
	{
		return FALSE;
	}

	n = ::GetPixelFormat(pDC);
	::DescribePixelFormat(pDC, n, sizeof(pfd), &pfd);

	hglrc = wglCreateContext(pDC);	//创建绘制情景对象

	wglMakeCurrent(pDC, hglrc);		//选择绘制情景对象
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glPointSize(1);
	glLineWidth(1);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return TRUE;
}
