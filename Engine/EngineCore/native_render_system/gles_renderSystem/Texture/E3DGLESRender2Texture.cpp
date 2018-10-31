#include "E3DGLESRender2Texture.h"

void E3DEngine::GLES_Render2Texture::Update(float deltaTime)
{
	
}

void E3DEngine::GLES_Render2Texture::CreateRenderTarget(float width, float height)
{
	m_fbo = new GLESRenderSystem::FrameBufferObject();
	m_fbo->Create(width, height, GLESRenderSystem::RENDER_TO_TEXTURE);
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

void E3DEngine::GLES_Render2Texture::SetTextureUniformIndex(int index, UINT program)
{
	m_nTextureUniform = ES2::GetUniformLocation(program, m_strTextureUniformName.c_str());
	ES2::Uniform1i(m_nTextureUniform, index);
	m_nTextureIndex = index;
}

void E3DEngine::GLES_Render2Texture::ActiveBindTexture()
{
	ES2::ActiveTexture(m_nTextureEnum);
	ES2::BindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
	ES2::Uniform1i(m_nTextureUniform, m_nTextureIndex);
}

void E3DEngine::GLES_Render2Texture::InvalidTexture()
{
	ES2::BindTexture(GL_TEXTURE_2D, 0);
}

void E3DEngine::GLES_Render2Texture::SetClampType(int tp)
{

}

void E3DEngine::GLES_Render2Texture::SetFilterType(int tp)
{

}
