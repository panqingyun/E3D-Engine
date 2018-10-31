#include "gles_adapter.h"

namespace E3DEngine
{
	namespace ES2
	{
#define __String(x) #x

		HMODULE gESModule = nullptr;
		PFNGLDELETEBUFFERSPROC _glGenFrameBuffer;

		void LoadESLibrary()
		{
			gESModule = LoadLibrary("libGLESv2.dll");
			if (gESModule == nullptr)
			{
				return;
			}
			_glGenFrameBuffer = (PFNGLDELETEBUFFERSPROC)GetProcAddress(gESModule, __String(glGenFramebuffers));
		}

		void GenFramebuffers(GLsizei n, GLuint* framebuffers)
		{
			_glGenFrameBuffer(n, framebuffers);
		}
	}
}