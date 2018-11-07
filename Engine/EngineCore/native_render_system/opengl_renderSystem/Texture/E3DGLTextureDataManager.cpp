//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>
#include "E3DGLRender2Texture.h"
#include "E3DGLTexture2D.hpp"
#include "E3DGLCubeMapTexture.hpp"

E3DEngine::Render2Texture* E3DEngine::GL_TextureDataManager::createRender2Texture()
{
	GL_Render2Texture *rtt = new GL_Render2Texture;
	return rtt;
}

E3DEngine::Texture * E3DEngine::GL_TextureDataManager::createTexture2D(TextureData *data)
{
	GL_Texture2D * texture = new GL_Texture2D();
	texture->Create(data);
	return texture;
}

E3DEngine::Texture * E3DEngine::GL_TextureDataManager::createCubeTexture(std::string filePath, int selectID)
{
	GL_CubeMapTexture * texture = new GL_CubeMapTexture;
	texture->Create(filePath, selectID);
	return texture;
}
