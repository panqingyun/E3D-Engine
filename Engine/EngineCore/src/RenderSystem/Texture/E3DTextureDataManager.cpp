//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DTextureDataManager.hpp"
#include "src/Source/EngineDelegate.h"
#include "3rd/header/Helpers.h"

void E3DEngine::TextureDataManager::Init()
{
	DEFAULT_TEXTURE_FILE = Application::ResourcePath + "/defaultTexture.png";
}

unsigned int E3DEngine::TextureDataManager::CreateTextureBuffer(std::string imageName, TextureData &tData)
{
	return 0;
}

E3DEngine::stImageData * E3DEngine::TextureDataManager::CreateTextureData(std::string imageName)
{
	return nullptr;
}

void E3DEngine::TextureDataManager::Cleanup()
{
	
}
