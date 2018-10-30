//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLESTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>

#include "E3DGLESRender2Texture.h"

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


E3DEngine::Render2Texture* E3DEngine::GLES_TextureDataManager::CreateRender2Texture(float width, float height)
{
	GLES_Render2Texture *rtt = new GLES_Render2Texture;
	rtt->CreateRenderTarget(width, height);
	return rtt;
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
