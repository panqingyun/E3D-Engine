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
			ES2::DeleteTextures(1, &m_nTextureBuffer);
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
		else if (tData.rgbModule == PixelFormat::L8A8)
		{
			rgbModule = GL_LUMINANCE_ALPHA;
		}
		else if (tData.rgbModule == PixelFormat::L8)
		{
			rgbModule = GL_LUMINANCE;
		}
		else
		{
			assert(false);
		}
		m_nTextureBuffer = GLES_RenderSystem::GetRenderSystem()->GetTextureDataManager()->GetTextureBuffer(fileName);
		ES2::ActiveTexture(GL_TEXTURE_2D);
		ES2::BindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		setTextureParam(tData);
		ES2::TexImage2D(GL_TEXTURE_2D, 0, rgbModule, tData.width, tData.height, 0, rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
		if (tData.useMipMap)
		{
			ES2::GenerateMipmap(GL_TEXTURE_2D);
		}
		ES2::BindTexture(GL_TEXTURE_2D, 0);
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

		ES2::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
		ES2::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
		ES2::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clampType);
		ES2::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clampType);
	}

	void GLES_Texture2D::SetTextureData(TextureData &tData)
	{
		ES2::BindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		ES2::TexImage2D(GL_TEXTURE_2D, 0, tData.rgbModule, tData.width, tData.height, 0, tData.rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
		ES2::BindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture2D::Create(TextureData &tData)
	{
		ES2::GenTextures(1, &m_nTextureBuffer);
		ES2::BindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		
		/*ES2::TexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		ES2::TexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		ES2::TexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		ES2::TexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
		unsigned int eFormat = GL_RGBA;
		
		ES2::TexImage2D(GL_TEXTURE_2D, 0, tData.rgbModule, tData.width, tData.height, 0, tData.rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
		ES2::BindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES_Texture2D::SetTextureUniformIndex(int i, GLuint ProgramHandle)
	{
		m_nTextureUniform = ES2::GetUniformLocation(ProgramHandle, m_strTextureUniformName.c_str());
		ES2::Uniform1i(m_nTextureUniform, i);
		m_nTextureIndex = i;
	}
		
	void GLES_Texture2D::ActiveBindTexture()
	{
		ES2::ActiveTexture(m_nTextureEnum);
		ES2::BindTexture(GL_TEXTURE_2D, m_nTextureBuffer);
		ES2::Uniform1i(m_nTextureUniform, m_nTextureIndex);
	}

	void GLES_Texture2D::InvalidTexture()
	{
		ES2::BindTexture(GL_TEXTURE_2D, 0);
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
