//
//  Texture.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//
#include "E3DGLESTexture.hpp"
#include <src/RenderSystem/E3DRenderSystem.hpp>

namespace E3DEngine
{

	GLES_Texture::~GLES_Texture()
	{
		if (m_nTextureBuffer != 0)
		{
			glDeleteTextures(1, &m_nTextureBuffer);
		}
	}

	void GLES_Texture::Create(std::string fileName)
	{
		m_nTextureBuffer = GetRenderSystem()->GetTextureDataManager()->CreateTextureBuffer(fileName);
	}
	
	void GLES_Texture::SetTextureData(void * textureData, int width, int height, int imgDepth)
	{
		unsigned int eFormat = GL_RGBA;
		switch (imgDepth)
		{
		case 3:     // Most likely case
			eFormat = GL_RGB;
			break;
		case 4:
			eFormat = GL_RGBA;
			break;
		case 1:
			eFormat = GL_LUMINANCE;
			break;
		default:
			break;
		}
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, eFormat, width, height, 0, eFormat, GL_UNSIGNED_BYTE, textureData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture::Create(void *textureData, int width, int height, int imgDepth)
	{
		glGenTextures(1, &m_nTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		unsigned int eFormat = GL_RGBA;
		switch (imgDepth)
		{
		case 3:     // Most likely case
			eFormat = GL_RGB;
			break;
		case 4:
			eFormat = GL_RGBA;
			break;
		case 1:
			eFormat = GL_LUMINANCE;
			break;
		default:
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, eFormat, width, height, 0, eFormat, GL_UNSIGNED_BYTE, textureData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture::SetTextureEnum(unsigned int enumNumber)
	{
		m_nTextureEnum = enumNumber;
	}
	
	void GLES_Texture::SetTextureUniformLocation(int i, GLuint ProgramHandle)
	{
		m_nTextureUniform = glGetUniformLocation(ProgramHandle, m_strTextureUniformName.c_str());
		glUniform1i(m_nTextureUniform, i);
		m_nTextureIndex = i;
	}
		
	void GLES_Texture::ActiveBindTexture()
	{
		glActiveTexture(m_nTextureEnum);
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		glUniform1i(m_nTextureUniform, m_nTextureIndex);
	}

	void GLES_Texture::InvalidTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture::SetTextureUniformName(std::string name)
	{
		m_strTextureUniformName = name;
	}

	GLES_Texture::GLES_Texture()
	{
		m_nTextureBuffer = 0;
	}

	GLuint & GLES_Texture::GetTextureBuffer()
	{
		return m_nTextureBuffer;
	}

}
