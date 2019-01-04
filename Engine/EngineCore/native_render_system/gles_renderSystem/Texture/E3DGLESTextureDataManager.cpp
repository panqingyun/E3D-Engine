//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DGLESTextureDataManager.hpp"
#include <src/Source/E3DDebug.h>

#include "E3DGLESRender2Texture.h"
#include "E3DGLESTexture2D.hpp"
#include "E3DGLESCubeMapTexture.hpp"

E3DEngine::Render2Texture* E3DEngine::GLES_TextureDataManager::createRender2Texture()
{
	GLES_Render2Texture *rtt = new GLES_Render2Texture;
	return rtt;
}


E3DEngine::Texture * E3DEngine::GLES_TextureDataManager::createTexture2D(Texture2dData *data)
{
	GLES_Texture2D * texture = new GLES_Texture2D();
	texture->Create(data);
	return texture;
}


E3DEngine::Texture * E3DEngine::GLES_TextureDataManager::createCubeTexture(std::string filePath, int selectID)
{
	GLES_CubeMapTexture * texture = new GLES_CubeMapTexture;
	texture->Create(filePath, selectID);
	return texture;
}
