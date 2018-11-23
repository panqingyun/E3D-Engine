//
//  RenderSystem.cpp
//
//  Created by 潘庆云 on 2017/1/22.
//

#include "E3DGLESRenderSystem.hpp"
#include "Texture/E3DGLESTextureDataManager.hpp"
#include "Material/E3DGLESMaterialManager.hpp"
#include "Texture/E3DGLESRender2Texture.h"
#include "RenderObject/E3DGLESRenderManager.hpp"
#include <include/EngineAPI.h>
#include "Shader/E3DGLESShaderManager.h"

E3DEngine::GLES_RenderSystem * g_RenderSystem = nullptr;
namespace E3DEngine
{
	using namespace GLESRenderSystem;
	void GLES_RenderSystem::Initilize()
	{
		m_pTextureDataManager = dynamic_cast<TextureDataManager*>(new GLES_TextureDataManager);
		m_pMaterialManager = dynamic_cast<MaterialManager*>(new GLES_MaterialManager);
		m_pRenderManager = dynamic_cast<RendererManager*>(new GLES_RendererManager);
		m_pShaderManager = dynamic_cast<ShaderManager*>(new GLES_ShaderManager);
	}


	void GLES_RenderSystem::Cleanup()
	{
		m_pMaterialManager->Cleanup();
		m_pTextureDataManager->Cleanup();
		m_pRenderManager->Cleanup();
		//SAFE_DELETE(defaultFrameBuffer);
	}


	void GLES_RenderSystem::BindDefaultBackbuffer()
	{
#ifdef __IOS__
		defaultFrameBuffer->Bind();
        defaultFrameBuffer->BindRenderBuffer();
#else
		ES2::BindFramebuffer(GL_FRAMEBUFFER, 0);
		ES2::Viewport(0, 0, m_frameWidth, m_frameHeight);
#endif // __IOS_

	}

	void GLES_RenderSystem::SetupDefaultFrameBuffer()
	{
		defaultFrameBuffer = new FrameBufferObject();
		defaultFrameBuffer->Create(m_frameWidth, m_frameHeight, RENDER_BUFFER);
	}

	void GLES_RenderSystem::BeginFrame()
	{
#ifdef __IOS__
        BindDefaultBackbuffer();
        defaultFrameBuffer->Clear();
#else
        m_pEGL_Context->UseContext();
		BindDefaultBackbuffer();
#endif
				
	}


	void GLES_RenderSystem::clearFrameBufferObject()
	{
#ifdef __IOS__
		defaultFrameBuffer->Clear();
#else
		ES2::ClearColor(0, 0, 0, 0);
		ES2::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif
		
	}

	void GLES_RenderSystem::EndFrame()
	{
#ifndef __IOS__
		m_pEGL_Context->SwapBuffer();
		ES2::Flush();
#endif
	}

	void GLES_RenderSystem::CreateOpenGLES(EGLNativeDisplayType displayID,EGLNativeWindowType windowHandle)
	{
#ifdef __IOS__
        SetupDefaultFrameBuffer();
#else
        m_pEGL_Context = new EGL_Context();
        m_pEGL_Context->InitGLES(displayID, windowHandle);
		m_pEGL_Context->UseContext();
#endif
		ES2::CullFace(GL_BACK);
		ES2::Enable(GL_STENCIL_TEST);
	}

	GLES_RenderSystem::GLES_RenderSystem()
	{
		defaultFrameBuffer = nullptr;
	}

	void GLES_RenderSystem::Clear(Color4 color, int clearType)
	{
		UINT type = 0;
		if (clearType & eCT_Color)
		{
			ES2::ClearColor(color.r, color.g, color.b, color.a);
			type |= GL_COLOR_BUFFER_BIT;
		}
		if (clearType & eCT_Depth)
		{
			ES2::ClearDepthf(1);
			type |= GL_DEPTH_BUFFER_BIT;
		}
		if (type & eCT_Stencil)
		{
			ES2::ClearStencil(1);
			type |= GL_STENCIL_BUFFER_BIT;
		}
		ES2::Clear(type);
	}

	void GLES_RenderSystem::ChangeRenderSurface(EGLNativeWindowType windowHandle)
	{
		m_pEGL_Context->ChangeSurface(windowHandle);
	}

	GLES_RenderSystem* GLES_RenderSystem::GetRenderSystem()
	{
		return g_RenderSystem;
	}

	void GLES_RenderSystem::UseRenderContext()
	{
		//m_pEGL_Context->UseContext();
	}


	void GLES_RenderSystem::UseShareContext()
	{
		//m_pEGL_Context->UseShareContext();
	}


	void GLES_RenderSystem::CreateShareContext()
	{
		//m_pEGL_Context->CreateShareContext();
	}


	void GLES_RenderSystem::SetCullFaceType(CULL_FACE type)
	{
		ES2::CullFace(type == eCF_BACK ? GL_BACK : GL_FRONT);
	}

}

__api_function_ void* CreateGLESRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height)
{
	E3DEngine::ES2::LoadESLibrary();
	E3DEngine::GLES_RenderSystem * renderSystem = new E3DEngine::GLES_RenderSystem;
	renderSystem->Initilize();
	renderSystem->setFrameWidth(width);
	renderSystem->setFrameHeight(height);
	renderSystem->CreateOpenGLES(EGL_DEFAULT_DISPLAY, nativeWindow);
	g_RenderSystem = renderSystem;
	return renderSystem;
}
