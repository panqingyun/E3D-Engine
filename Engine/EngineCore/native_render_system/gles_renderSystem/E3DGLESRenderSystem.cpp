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
		m_pTextureDataManager = dynamic_cast<TextureDataManager*>(new GLES_TextureDataManager);
		m_pTextureDataManager->Init();
		m_pMaterialManager = dynamic_cast<MaterialManager*>(new GLES_MaterialManager);
		m_pRenderManager = dynamic_cast<RendererManager*>(new GLES_RendererManager);
	}


	void GLES_RenderSystem::Cleanup()
	{
		m_pMaterialManager->Cleanup();
		m_pTextureDataManager->Cleanup();
		m_pRenderManager->Cleanup();
		SAFE_DELETE(defaultFrameBuffer);
	}


	void GLES_RenderSystem::BindDefaultBackbuffer()
	{
#ifdef __IOS__
		defaultFrameBuffer->Bind();
        defaultFrameBuffer->BindRenderBuffer();
#else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, m_frameWidth, m_frameHeight);
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
#ifdef __IOS__
        BindDefaultBackbuffer();
        defaultFrameBuffer->Clear();
#else
        m_pEGL_Context->UseContext();
		BindDefaultBackbuffer();
#endif
        glCullFace(GL_BACK);
				
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
#ifndef __IOS__
		m_pEGL_Context->SwapBuffer();
        glFlush();
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

void CreateRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height)
{
	E3DEngine::GLES_RenderSystem * renderSystem = new E3DEngine::GLES_RenderSystem;
	renderSystem->Initilize();
	renderSystem->setFrameWidth(width);
	renderSystem->setFrameHeight(height);
	SetRenderSystem(renderSystem);
	renderSystem->CreateOpenGLES(EGL_DEFAULT_DISPLAY, nativeWindow);
}

