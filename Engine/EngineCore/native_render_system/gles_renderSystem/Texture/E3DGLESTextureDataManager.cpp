//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLESTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>

void E3DEngine::GLES_TextureDataManager::Init()
{
	DEFAULT_TEXTURE_FILE = "Resource/defaultTexture.png";
}

GLuint E3DEngine::GLES_TextureDataManager::CreateTextureBuffer(std::string imageName)
{
	if (m_mapTextureBuffer.find(imageName) != m_mapTextureBuffer.end())
	{
		return m_mapTextureBuffer[imageName];
	}
	stImageData *data = new stImageData();
#ifdef __IOS__
	data->data = vvision::LoadImage(imageName, &data->width, &data->height);
#else
	data->data = vvision::LoadImageW(imageName, &data->width, &data->height);
#endif
	if (data->data == nullptr)
	{		
		Debug::Log(ell_Error, "texture data is null");
		return 0;// CreateTextureBuffer(DEFAULT_TEXTURE_FILE);
	}
	GLuint TextureBuffer = 0;
	glGenTextures(1, &TextureBuffer);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#ifdef __ANDROID__
	// TODO ETC
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->data);
	m_mapTextureBuffer[imageName] = TextureBuffer;
	glBindTexture(GL_TEXTURE_2D, 0);
	SAFE_DELETE(data);
	return TextureBuffer;
}

E3DEngine::stImageData * E3DEngine::GLES_TextureDataManager::CreateTextureData(std::string imageName)
{
	if (m_mapTextureData.find(imageName) != m_mapTextureData.end())
	{
		return m_mapTextureData[imageName];
	}

	stImageData *data = new stImageData();
#ifdef __IOS__
	data->data = vvision::LoadImage(imageName, &data->width, &data->height);
#else
	data->data = vvision::LoadImageW(imageName, &data->width, &data->height);
#endif
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
