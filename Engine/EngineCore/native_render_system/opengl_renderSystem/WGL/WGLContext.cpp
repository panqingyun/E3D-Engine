
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

HGLRC GL_Context::choosePixelFormat(HDC hDC)
{
	HGLRC m_hRC = 0;
	//	PIXELFORMATDESCRIPTOR pfd;
	//int nPixelFormat = -1;
	//int nPixCount = 0;
	//float fPixAttribs[] = { 0,0 };
	//int iPixAttribs[] =
	//{
	//	WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering
	//	WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window
	//	WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, // must be HW accelerated
	//	WGL_COLOR_BITS_ARB,     32, // 8 bits of each R, G and B
	//	WGL_DEPTH_BITS_ARB,     24, // 24 bits of depth precision for window, 典型情况下深度缓冲区都是24位的,试了几台机器都不支持32位深度缓冲区
	//	WGL_DOUBLE_BUFFER_ARB,GL_TRUE, // Double buffered context
	//	WGL_PIXEL_TYPE_ARB,      WGL_TYPE_RGBA_ARB, // pf should be RGBA type
	//	WGL_STENCIL_BITS_ARB, 8,//开启模板缓冲区,模板缓冲区位数=8
	//	WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, // MSAA on,开启多重采样
	//	WGL_SAMPLES_ARB,        4, // 4x MSAA ,多重采样样本数量为4
	//	0 }; // NULL termination
	//		 //创建一个临时窗口,只是为了初始化glew库
	//
	//tempWnd->Create(_T("STATIC"), _T("Hi"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 20, 20), AfxGetMainWnd(), NULL);
	//HDC tempHdc = tempWnd->GetDC()->GetSafeHdc();
	//// Attempt to set the pixel format
	//if (!SetPixelFormat(tempHdc, 1, &pfd))//每个窗口只能设置一次
	//	return NULL;
	//HGLRC temphRC = wglCreateContext(tempHdc);//创建一个临时的环境为了初始化glew,初始化后才能够使用wglChoosePixelFormatARB，wglCreateContextAttribsARB函数
	//wglMakeCurrent(tempHdc, temphRC);//只有设置当前opengl环境后才能够初始化glew库
	//GLenum err = glewInit();//初始化glew库,一个程序中初始化一次就可以,不需要每个opengl环境都初始化
	//if (GLEW_OK != err)
	//	return NULL;
	//wglMakeCurrent(NULL, NULL);
	//wglDeleteContext(temphRC);
	//tempWnd->DestroyWindow();//销毁临时窗口
	//delete tempWnd;
	////新的查询像素格式的函数
	//wglChoosePixelFormatARB(hDC, iPixAttribs, fPixAttribs, 1, &nPixelFormat, (UINT*)&nPixCount);
	////多重采样时,如果硬件不支持就使用下面的代码关闭多重采样
	//if (nPixelFormat == -1)
	//{
	//	// Try again without MSAA
	//	iPixAttribs[18] = 1;
	//	wglChoosePixelFormatARB(hDC, iPixAttribs, fPixAttribs, 1, &nPixelFormat, (UINT*)&nPixCount);
	//}
	//// Got a format, now set it as the current one
	//if (!SetPixelFormat(hDC, nPixelFormat, &pfd))
	//{
	//	return NULL;
	//}
	//GLint attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB,  3,//主版本3
	//	WGL_CONTEXT_MINOR_VERSION_ARB,  3,//次版本号3
	//	WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,//要求返回兼容模式环境,如果不指定或指定为WGL_CONTEXT_CORE_PROFILE_BIT_ARB会返回只包含核心功能的环境
	//	0 };
	//m_hRC = wglCreateContextAttribsARB(hDC, 0, attribs);
	//if (m_hRC == NULL)
	//{
	//	printf("!!! Could not create an OpenGL 3.3 context.\n");
	//	attribs[3] = 2;
	//	m_hRC = wglCreateContextAttribsARB(hDC, 0, attribs);
	//	if (m_hRC == NULL)
	//	{
	//		printf("!!! Could not create an OpenGL 3.2 context.\n");//要求opengl3.2以上环境
	//		return NULL;
	//	}
	//}
	//wglMakeCurrent(NULL, NULL);
	return m_hRC;
}

BOOL GL_Context::OpenGLInit(HDC pDC)
{
	int pixelformat;

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
	glEnable(GL_MULTISAMPLE);
	//glEnable(GL_POLYGON_SMOOTH);     //多边形抗锯齿  
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	return TRUE;
}
