//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DTextureDataManager.hpp"
#include "src/Source/EngineDelegate.h"

void E3DEngine::TextureDataManager::Init()
{
	DEFAULT_TEXTURE_FILE = Application::ResourcePath + "/defaultTexture.png";
}

unsigned int E3DEngine::TextureDataManager::GetTextureBuffer(std::string imageName)
{
	return 0;
}

E3DEngine::TextureData * E3DEngine::TextureDataManager::GetTextureDataFromFile(std::string imageName)
{
	return nullptr;
}

void E3DEngine::TextureDataManager::Cleanup()
{
	
}
