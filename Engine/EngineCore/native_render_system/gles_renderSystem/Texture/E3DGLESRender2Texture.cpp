#include "E3DGLESRender2Texture.h"

void E3DEngine::GLES_Render2Texture::CreateRenderTarget(float width, float height)
{
	m_fbo = new GLESRenderSystem::FrameBufferObject();
	m_fbo->Create(width, height, GLESRenderSystem::RENDER_TO_TEXTURE);
	m_nWidth = width;
	m_nHeight = height;
	m_nTextureBuffer = m_fbo->GetTextureBufferID();
}


void E3DEngine::GLES_Render2Texture::CreateDepthTarget(float width, float height)
{
	m_fbo = new GLESRenderSystem::FrameBufferObject();
	m_fbo->Create(width, height, GLESRenderSystem::RENDER_DEPTH);
	m_nWidth = width;
	m_nHeight = height;
	m_nTextureBuffer = m_fbo->GetTextureBufferID();
}

E3DEngine::GLES_Render2Texture::~GLES_Render2Texture()
{
	SAFE_DELETE(m_fbo);
}

void E3DEngine::GLES_Render2Texture::Bind()
{
	m_fbo->Bind();
}
