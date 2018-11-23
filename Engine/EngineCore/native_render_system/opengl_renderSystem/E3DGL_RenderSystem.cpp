//
//  RenderSystem.cpp
//
//  Created by ≈À«Ï‘∆ on 2017/1/22.
//

#include "E3DGL_RenderSystem.h"
#include "Texture/E3DGLTextureDataManager.hpp"
#include "Material/E3DGLMaterialManager.hpp"
#include "Texture/E3DGLRender2Texture.h"
#include "RenderObject/E3DGLRenderManager.hpp"
#include <include/EngineAPI.h>
#include "Shader/E3DGLShaderManager.h"
#include <../../src/Source/E3DDebug.h>

E3DEngine::GL_RenderSystem * g_RenderSystem = nullptr;
namespace E3DEngine
{
	void GL_RenderSystem::Initilize()
	{
		m_pTextureDataManager = dynamic_cast<TextureDataManager*>(new GL_TextureDataManager);
		m_pMaterialManager = dynamic_cast<MaterialManager*>(new GL_MaterialManager);
		m_pRenderManager = dynamic_cast<RendererManager*>(new GL_RendererManager);
		m_pShaderManager = dynamic_cast<ShaderManager*>(new GL_ShaderManager);
	}


	void GL_RenderSystem::Cleanup()
	{
		m_pMaterialManager->Cleanup();
		m_pTextureDataManager->Cleanup();
		m_pRenderManager->Cleanup();
		//SAFE_DELETE(defaultFrameBuffer);
	}


	void GL_RenderSystem::BindDefaultBackbuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_frameWidth, m_frameHeight);

	}

	void GL_RenderSystem::SetupDefaultFrameBuffer()
	{
		defaultFrameBuffer = new FrameBufferObject();
		defaultFrameBuffer->Create(m_frameWidth, m_frameHeight, RENDER_BUFFER);
	}

	void GL_RenderSystem::BeginFrame()
	{
		m_pGL_Context->UseContext();
		BindDefaultBackbuffer();
	}


	void GL_RenderSystem::clearFrameBufferObject()
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	}

	void GL_RenderSystem::EndFrame()
	{
		m_pGL_Context->SwapBuffer();
	}

	void GL_RenderSystem::CreateOpenGL(HDC displayID)
	{
		m_pGL_Context = new GL_Context();
		m_pGL_Context->OpenGLInit(displayID);
		m_pGL_Context->UseContext();
		glCullFace(GL_BACK);
		//glEnable(GL_FRAMEBUFFER_SRGB);
	}

	GL_RenderSystem::GL_RenderSystem()
	{
		defaultFrameBuffer = nullptr;
	}

	void GL_RenderSystem::Clear(Color4 color, int clearType)
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

	void GL_RenderSystem::ChangeRenderSurface(HWND windowHandle)
	{
		m_pGL_Context->ChangeSurface(::GetDC(windowHandle));
	}

	GL_RenderSystem* GL_RenderSystem::GetRenderSystem()
	{
		return g_RenderSystem;
	}

	void GL_RenderSystem::CreateShareContext()
	{
		m_bIsMutilThreadRender = true;
	}

	void GL_RenderSystem::UseShareContext()
	{
		if (m_bIsMutilThreadRender)
		{
			m_pGL_Context->UseShareContext();
		}
	}


	void GL_RenderSystem::UseRenderContext()
	{
		if (m_bIsMutilThreadRender)
		{
			m_pGL_Context->UseContext();
		}
	}


	void GL_RenderSystem::SetCullFaceType(CULL_FACE type)
	{
		glCullFace(type == eCF_BACK ? GL_BACK : GL_FRONT);
	}

	void GL_RenderSystem::Pick(vec2f pickPos)
	{

	}

}

void* CreateGLRenderSystem(NATIVE_WINDOW_TYPE nativeWindow, int width, int height)
{
	E3DEngine::GL_RenderSystem * renderSystem = new E3DEngine::GL_RenderSystem;
	renderSystem->Initilize();
	renderSystem->setFrameWidth(width);
	renderSystem->setFrameHeight(height);
	renderSystem->CreateOpenGL(GetDC(nativeWindow));
	g_RenderSystem = renderSystem;
	return renderSystem;
}