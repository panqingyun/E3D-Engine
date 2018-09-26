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

GLuint E3DEngine::GLES_TextureDataManager::GetTextureBuffer(std::string imageName)
{
	if (m_mapTextureBuffer.find(imageName) != m_mapTextureBuffer.end())
	{
		return m_mapTextureBuffer[imageName];
	}
	
	GLuint TextureBuffer = 0;
	glGenTextures(1, &TextureBuffer);
	m_mapTextureBuffer[imageName] = TextureBuffer;
	return TextureBuffer;
}


E3DEngine::TextureData * E3DEngine::GLES_TextureDataManager::GetTextureDataFromFile(std::string imageName)
{
	E3DEngine::TextureData * imgData = new E3DEngine::TextureData();
	int width, height, bpp;
	char *bits = (char*)stbi_load(imageName.c_str(), &width, &height, &bpp, 0);
	char * outByte = nullptr;

	if (bpp == PixelFormat::R8G8B8)
	{
		imgData->rgbModule = GL_RGB;
		outByte = (char*)malloc(width * height * 3);
		memcpy(outByte, bits, width*height * 3);
	}
	else if (bpp == PixelFormat::R8G8B8A8)
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
