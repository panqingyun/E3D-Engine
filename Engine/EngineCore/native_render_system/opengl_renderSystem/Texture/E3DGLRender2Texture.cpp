#include "E3DGLRender2Texture.h"

void E3DEngine::GL_Render2Texture::CreateRenderTarget(float width, float height)
{
	m_fbo = new FrameBufferObject();
	m_fbo->Create(width, height, RENDER_TO_TEXTURE);
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
