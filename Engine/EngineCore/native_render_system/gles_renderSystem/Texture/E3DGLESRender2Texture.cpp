#include "E3DGLESRender2Texture.h"

void E3DEngine::GLES_Render2Texture::CreateRenderTarget(float width, float height, int mutliSapmleLevel)
{
	m_fbo = new GLESRenderSystem::FrameBufferObject();
	m_fbo->Create(width, height, RENDER_TO_TEXTURE);
	m_nWidth = width;
	m_nHeight = height;
	m_nTextureBuffer = m_fbo->GetTextureBufferID();
}


void E3DEngine::GLES_Render2Texture::CreateDepthTarget(float width, float height)
{
	m_fbo = new GLESRenderSystem::FrameBufferObject();
	m_fbo->Create(width, height, RENDER_DEPTH);
	m_nWidth = width;
	m_nHeight = height;
	m_nTextureBuffer = m_fbo->GetTextureBufferID();
}

void E3DEngine::GLES_Render2Texture::Blit(Render2Texture * dest, BlitBuffer bufferType)
{
	if (dest == nullptr)
	{
		blitFrameBuffer(nullptr, bufferType);
	}
	else
	{
		GLES_Render2Texture *glesRt = static_cast<GLES_Render2Texture*>(dest);
		blitFrameBuffer(glesRt->GetFBO(), bufferType);
	}
}

E3DEngine::GLES_Render2Texture::~GLES_Render2Texture()
{
	SAFE_DELETE(m_fbo);
}

void E3DEngine::GLES_Render2Texture::Bind()
{
	m_fbo->Bind();
}

E3DEngine::GLESRenderSystem::FrameBufferObject * E3DEngine::GLES_Render2Texture::GetFBO()
{
	return m_fbo;
}

void E3DEngine::GLES_Render2Texture::blitFrameBuffer(E3DEngine::GLESRenderSystem::FrameBufferObject * fbo, BlitBuffer bufferType)
{
	if (bufferType == DEPTH_BUFFER)
	{
		m_fbo->BlitFrameBuffer(fbo, GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		m_fbo->BlitFrameBuffer(fbo, GL_COLOR_BUFFER_BIT);
	}
}
