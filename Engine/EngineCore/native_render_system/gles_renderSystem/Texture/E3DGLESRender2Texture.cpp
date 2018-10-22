#include "E3DGLESRender2Texture.h"

void E3DEngine::GLES_Render2Texture::Update(float deltaTime)
{
	
}

void E3DEngine::GLES_Render2Texture::CreateRenderTarget(float width, float height)
{
	m_fbo = new FrameBufferObject();
	m_fbo->Create(width, height, RENDER_TO_TEXTURE);
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
	m_nTextureUniform = glGetUniformLocation(program, m_strTextureUniformName.c_str());
	glUniform1i(m_nTextureUniform, index);
	m_nTextureIndex = index;
}

void E3DEngine::GLES_Render2Texture::ActiveBindTexture()
{
	glActiveTexture(m_nTextureEnum);
	glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
	glUniform1i(m_nTextureUniform, m_nTextureIndex);
}

void E3DEngine::GLES_Render2Texture::InvalidTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void E3DEngine::GLES_Render2Texture::SetClampType(int tp)
{

}

void E3DEngine::GLES_Render2Texture::SetFilterType(int tp)
{

}
