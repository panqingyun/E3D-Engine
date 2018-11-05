//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>
#include "E3DGLRender2Texture.h"


GLuint E3DEngine::GL_TextureDataManager::GetTextureBuffer(std::string imageName)
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

void E3DEngine::GL_TextureDataManager::Cleanup()
{
	for (std::map<std::string, GLuint>::iterator it = m_mapTextureBuffer.begin();
		it != m_mapTextureBuffer.end(); ++it)
	{
		glDeleteTextures(1, &it->second);
	}
	m_mapTextureBuffer.clear();
}

E3DEngine::Render2Texture* E3DEngine::GL_TextureDataManager::createRender2Texture()
{
	GL_Render2Texture *rtt = new GL_Render2Texture;
	return rtt;
}
