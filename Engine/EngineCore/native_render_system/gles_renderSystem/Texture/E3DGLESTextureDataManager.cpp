//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLESTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>

void E3DEngine::GLES_TextureDataManager::Init()
{
	DEFAULT_TEXTURE_FILE = "Resource/Material/texture/common.png";
}

E3DEngine::stImageData * FIBitmap2GLBitmap(const char * imageName, unsigned int &rgb_mode)
{
	E3DEngine::stImageData * imgData = new E3DEngine::stImageData();
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imageName, 0);
	FIBITMAP *dib = FreeImage_Load(fifmt, imageName, 0);
	//dib = FreeImage_ConvertTo32Bits(dib);
	FreeImage_FlipVertical(dib);
	char *bits = (char*)FreeImage_GetBits(dib);
	char * data = nullptr;
	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);
	int bpp = FreeImage_GetBPP(dib);
	int pitch = FreeImage_GetPitch(dib);
	char * outByte = nullptr;
	if (bpp == 24)
	{
		for (size_t i = 0; i < width*height * 3; i += 3)
		{
			BYTE temp = bits[i];
			bits[i] = bits[i + 2];
			bits[i + 2] = temp;
		}
		rgb_mode = GL_RGB;
		outByte = (char*)malloc(width * height * 3);
		memcpy(outByte, bits, width*height * 3);
	}
	else if (bpp == 32)
	{
		for (size_t i = 0; i < width*height * 4; i += 4)
		{
			BYTE temp = bits[i];
			bits[i] = bits[i + 2];
			bits[i + 2] = temp;
		}
		rgb_mode = GL_RGBA;
		outByte = (char*)malloc(width * height * 4);
		memcpy(outByte, bits, width*height * 4);
	}

	imgData->data = outByte;
	imgData->height = height;
	imgData->width = width;
	FreeImage_Unload(dib);
	return imgData;
}

GLuint E3DEngine::GLES_TextureDataManager::CreateTextureBuffer(std::string imageName)
{
	if (m_mapTextureBuffer.find(imageName) != m_mapTextureBuffer.end())
	{
		return m_mapTextureBuffer[imageName];
	}
	
	GLuint TextureBuffer = 0;
	glGenTextures(1, &TextureBuffer);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer);
	unsigned int COLOR_TYPE = GL_RGBA;
	
	stImageData * imgData = FIBitmap2GLBitmap(imageName.c_str(), COLOR_TYPE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, COLOR_TYPE, imgData->width, imgData->height, 0, COLOR_TYPE, GL_UNSIGNED_BYTE, imgData->data);
	m_mapTextureBuffer[imageName] = TextureBuffer;
	glBindTexture(GL_TEXTURE_2D, 0);
	SAFE_DELETE(imgData);
	return TextureBuffer;
}

E3DEngine::stImageData * E3DEngine::GLES_TextureDataManager::CreateTextureData(std::string imageName)
{
	if (m_mapTextureData.find(imageName) != m_mapTextureData.end())
	{
		return m_mapTextureData[imageName];
	}

	unsigned int COLOR_TYPE = GL_RGBA;
	stImageData *data = FIBitmap2GLBitmap(imageName.c_str(), COLOR_TYPE);

	m_mapTextureData[imageName] = data;
	return data;
}

void E3DEngine::GLES_TextureDataManager::Cleanup()
{
	for (auto &imageData : m_mapTextureData)
	{
		SAFE_DELETE(imageData.second);
	}
	m_mapTextureData.clear();
	for (std::map<std::string, GLuint>::iterator it = m_mapTextureBuffer.begin();
		it != m_mapTextureBuffer.end(); ++it)
	{
		glDeleteTextures(1, &it->second);
	}
	m_mapTextureBuffer.clear();
}
