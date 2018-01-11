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

namespace E3DEngine
{
	void GLES_RenderSystem::Initilize()
	{
		m_pTextureDataManager = new GLES_TextureDataManager;
		m_pTextureDataManager->Init();
		m_pMaterialManager = new GLES_MaterialManager;
		m_pRenderManager = new GLES_RendererManager;
	}


	void GLES_RenderSystem::Cleanup()
	{
		m_pMaterialManager->Cleanup();
		m_pTextureDataManager->Cleanup();
	}


	void GLES_RenderSystem::BindDefaultBackbuffer()
	{
#ifdef __IOS__
		defaultFrameBuffer->Bind();
#else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif // __IOS_

	}

	E3DEngine::Render2Texture * GLES_RenderSystem::CreateRtt(float width, float height)
	{
		GLES_Render2Texture * rtt = new GLES_Render2Texture();
		rtt->CreateRenderTarget(width, height);
		return rtt;
	}

	void GLES_RenderSystem::SetupDefaultFrameBuffer()
	{
		defaultFrameBuffer = new FrameBufferObject();
		defaultFrameBuffer->Create(m_frameWidth, m_frameHeight, RENDER_BUFFER);
	}

	void GLES_RenderSystem::BeginFrame()
	{
		m_pEGL_Context_Ex->UseContext();
#ifdef WIN32
		//m_pEGL_Context->UseContext();
#endif
#ifdef __IOS__
		if (m_NeedClear)
		{
			BindDefaultFBO();
			defaultFrameBuffer->Clear();
		}
#else
		BindDefaultFBO();
		//clearFrameBufferObject();

#endif
				
	}


	void GLES_RenderSystem::clearFrameBufferObject()
	{
#ifdef __IOS__
		defaultFrameBuffer->Clear();
#else
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif
		
	}

	void GLES_RenderSystem::EndFrame()
	{
		m_pEGL_Context_Ex->SwapBuffer();
		glFlush();
	}

	void GLES_RenderSystem::CreateOpenGLES(EGLNativeDisplayType displayID,EGLNativeWindowType windowHandle)
	{
		m_pEGL_Context_Ex = new EGL_Context();
		m_pEGL_Context_Ex->InitGLES(displayID, windowHandle);
		m_pEGL_Context_Ex->UseContext();
	}

	GLES_RenderSystem::GLES_RenderSystem()
	{
		defaultFrameBuffer = nullptr;
	}

	void GLES_RenderSystem::BindDefaultFBO()
	{		
#ifdef __IOS__
		defaultFrameBuffer->Bind();
		glBindRenderbuffer(GL_RENDERBUFFER, defaultFrameBuffer->GetRenderBufferID());
#else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_frameWidth, m_frameHeight);
#endif		
	}

	void GLES_RenderSystem::Clear(Color4 color, int clearType)
	{
		UINT type = 0;
		if (clearType & eCT_Color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			type |= GL_COLOR_BUFFER_BIT;
		}
		if (clearType & eCT_Depth)
		{
			glClearDepthf(1);
			type |= GL_DEPTH_BUFFER_BIT;
		}
		if (type & eCT_Stencil)
		{
			glClearStencil(1);
			type |= GL_STENCIL_BUFFER_BIT;
		}
		glClear(type);
	}

}

#if GLES_VERSION == 2
void CreateRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height)
{
	E3DEngine::GLES_RenderSystem * renderSystem = new E3DEngine::GLES_RenderSystem;
	renderSystem->Initilize();
	renderSystem->setFrameWidth(width);
	renderSystem->setFrameHeight(height);
	SetRenderSystem(renderSystem);
	renderSystem->CreateOpenGLES(EGL_DEFAULT_DISPLAY, nativeWindow);
}

#endif
