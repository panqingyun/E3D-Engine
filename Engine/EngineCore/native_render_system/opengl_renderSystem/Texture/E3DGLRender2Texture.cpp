#include "E3DGLRender2Texture.h"

void E3DEngine::GL_Render2Texture::CreateRenderTarget(float width, float height, int multiSampleLevel)
{
	m_fbo = new FrameBufferObject();
	m_fbo->Create(width, height, RENDER_TO_TEXTURE, multiSampleLevel);
	m_nWidth = width;
	m_nHeight = height;
	m_nTextureBuffer = m_fbo->GetTextureBufferID();
}


void E3DEngine::GL_Render2Texture::CreateDepthTarget(float width, float height)
{
	m_fbo = new FrameBufferObject();
	m_fbo->Create(width, height, RENDER_DEPTH);
	m_nWidth = width;
	m_nHeight = height;
	m_nTextureBuffer = m_fbo->GetTextureBufferID();
}

E3DEngine::GL_Render2Texture::~GL_Render2Texture()
{
	SAFE_DELETE(m_fbo);
	glDeleteTextures(1, &m_nTextureBuffer);
}

void E3DEngine::GL_Render2Texture::Bind()
{
	m_fbo->Bind();
}

E3DEngine::FrameBufferObject * E3DEngine::GL_Render2Texture::GetFBO()
{
	return m_fbo;
}

void E3DEngine::GL_Render2Texture::Blit(Render2Texture * dest, BlitBuffer bufferType)
{
	if (dest == nullptr)
	{
		blitFrameBuffer(nullptr, bufferType);
	}
	else
	{
		GL_Render2Texture *oglRt = static_cast<GL_Render2Texture*>(dest);
		blitFrameBuffer(oglRt->GetFBO(), bufferType);
	}
}

void E3DEngine::GL_Render2Texture::blitFrameBuffer(E3DEngine::FrameBufferObject * fbo, BlitBuffer bufferType)
{
	if (bufferType == DEPTH_BUFFER)
	{
		m_fbo->BlitFrameBuffer(fbo, GL_DEPTH_BUFFER_BIT);
	}
	else if(bufferType == COLOR_BUFFER)
	{
		m_fbo->BlitFrameBuffer(fbo, GL_COLOR_BUFFER_BIT);
	}
}
