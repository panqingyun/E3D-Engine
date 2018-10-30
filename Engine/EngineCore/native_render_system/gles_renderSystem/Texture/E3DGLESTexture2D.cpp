//
//  Texture.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//
#include "E3DGLESTexture2D.hpp"
#include "../E3DGLESRenderSystem.hpp"

namespace E3DEngine
{

	GLES_Texture2D::~GLES_Texture2D()
	{
		if (m_nTextureBuffer != 0)
		{
			glDeleteTextures(1, &m_nTextureBuffer);
		}
	}

	void GLES_Texture2D::Create(std::string fileName, TextureData &tData)
	{
		DWORD  rgbModule = 0;
		if (tData.rgbModule == PixelFormat::R8G8B8)
		{
			rgbModule = GL_RGB;
		}
		else if (tData.rgbModule == PixelFormat::R8G8B8A8)
		{
			rgbModule = GL_RGBA;
		}
		else
		{
			// TODO
		}
		m_nTextureBuffer = GLES_RenderSystem::GetRenderSystem()->GetTextureDataManager()->GetTextureBuffer(fileName);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		setTextureParam(tData);
		glTexImage2D(GL_TEXTURE_2D, 0, rgbModule, tData.width, tData.height, 0, rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
		if (tData.useMipMap)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture2D::setTextureParam(TextureData &tData)
	{
		unsigned int clampType = 0;
		unsigned int filterType = 0;
		switch (tData.clampType)
		{
		case CLAMP_TYPE::CLAMP_TO_EDGE:
			clampType = GL_CLAMP_TO_EDGE;
			break;
		case  CLAMP_TYPE::MIRRORED_REPEAT:
			clampType = GL_MIRRORED_REPEAT;
			break;
		case CLAMP_TYPE::REPEAT:
			clampType = GL_REPEAT;
			break;
		default:
			assert(false);
		}

		switch (tData.filterType)
		{
		case FILTER_TYPE::LINEAR:
			filterType = GL_LINEAR;
			break;
		case  FILTER_TYPE::NEAREST:
			filterType = GL_NEAREST;
			break;
		case FILTER_TYPE::LINEAR_MIPMAP_LINEAR:
			filterType = GL_LINEAR_MIPMAP_LINEAR;
			tData.useMipMap = true;
			break;
		case  FILTER_TYPE::LINEAR_MIPMAP_NEAREST:
			filterType = GL_LINEAR_MIPMAP_NEAREST;
			tData.useMipMap = true;
			break;
		case  FILTER_TYPE::NEAREST_MIPMAP_LINEAR:
			filterType = GL_NEAREST_MIPMAP_LINEAR;
			tData.useMipMap = true;
			break;
		case  FILTER_TYPE::NEAREST_MIPMAP_NEAREST:
			filterType = GL_NEAREST_MIPMAP_NEAREST;
			tData.useMipMap = true;
			break;
		default:
			assert(false);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clampType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clampType);
	}

	void GLES_Texture2D::SetTextureData(TextureData &tData)
	{
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, tData.rgbModule, tData.width, tData.height, 0, tData.rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture2D::Create(TextureData &tData)
	{
		glGenTextures(1, &m_nTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		
		/*glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
		unsigned int eFormat = GL_RGBA;
		
		glTexImage2D(GL_TEXTURE_2D, 0, tData.rgbModule, tData.width, tData.height, 0, tData.rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture2D::SetTextureUniformIndex(int i, GLuint ProgramHandle)
	{
		m_nTextureUniform = glGetUniformLocation(ProgramHandle, m_strTextureUniformName.c_str());
		glUniform1i(m_nTextureUniform, i);
		m_nTextureIndex = i;
	}
		
	void GLES_Texture2D::ActiveBindTexture()
	{
		glActiveTexture(m_nTextureEnum);
		glBindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		glUniform1i(m_nTextureUniform, m_nTextureIndex);
	}

	void GLES_Texture2D::InvalidTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLES_Texture2D::GLES_Texture2D()
	{
		m_nTextureBuffer = 0;
	}

	GLuint & GLES_Texture2D::GetTextureBuffer()
	{
		return m_nTextureBuffer;
	}

}
