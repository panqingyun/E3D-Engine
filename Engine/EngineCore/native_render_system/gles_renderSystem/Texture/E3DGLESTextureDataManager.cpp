//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLESTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

void E3DEngine::GLES_TextureDataManager::Init()
{
	DEFAULT_TEXTURE_FILE = "Resource/Material/texture/common.png";
}

GLuint E3DEngine::GLES_TextureDataManager::CreateTexture(std::string imageName,TextureData &tData)
{
	if (m_mapTextureBuffer.find(imageName) != m_mapTextureBuffer.end())
	{
		return m_mapTextureBuffer[imageName];
	}
	
	GLuint TextureBuffer = 0;
	glGenTextures(1, &TextureBuffer);
	glActiveTexture(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer);
	setTextureParam(tData);
	glTexImage2D(GL_TEXTURE_2D, 0, tData.rgbModule, tData.width, tData.height, 0, tData.rgbModule, GL_UNSIGNED_BYTE, tData.imgData);
	if (tData.useMipMap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	m_mapTextureBuffer[imageName] = TextureBuffer;
	glBindTexture(GL_TEXTURE_2D, 0);
	return TextureBuffer;
}


void E3DEngine::GLES_TextureDataManager::setTextureParam(TextureData &tData)
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

E3DEngine::TextureData * E3DEngine::GLES_TextureDataManager::GetTextureDataFromFile(std::string imageName)
{
	E3DEngine::TextureData * imgData = new E3DEngine::TextureData();
	int width, height, bpp;
	char *bits = (char*)stbi_load(imageName.c_str(), &width, &height, &bpp, 0);
	char * outByte = nullptr;

	if (bpp == 3)
	{
		imgData->rgbModule = GL_RGB;
		outByte = (char*)malloc(width * height * 3);
		memcpy(outByte, bits, width*height * 3);
	}
	else if (bpp == 4)
	{
		imgData->rgbModule = GL_RGBA;
		outByte = (char*)malloc(width * height * 4);
		memcpy(outByte, bits, width*height * 4);
	}
	else
	{
		// TODO
		Debug::Log(ell_Error, "bpp is not in support format!");
		assert(false);
	}
	imgData->imgData = outByte;
	imgData->height = height;
	imgData->width = width;
	stbi_image_free(bits);
	return imgData;
}

void E3DEngine::GLES_TextureDataManager::Cleanup()
{
	for (std::map<std::string, GLuint>::iterator it = m_mapTextureBuffer.begin();
		it != m_mapTextureBuffer.end(); ++it)
	{
		glDeleteTextures(1, &it->second);
	}
	m_mapTextureBuffer.clear();
}
