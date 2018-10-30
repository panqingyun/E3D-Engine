#include "gles_adapter.h"

namespace E3DEngine
{
	namespace ES2
	{
		HINSTANCE gESInstance = nullptr;

		void LoadESLibrary()
		{
			gESInstance = LoadLibrary("libGLESv2.dll");
		}

		void ActiveTexture(GLenum texture)
		{

		}
	}
}