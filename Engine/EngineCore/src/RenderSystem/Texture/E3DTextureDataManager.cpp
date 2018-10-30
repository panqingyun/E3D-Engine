//
//  TextureDataManager.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DTextureDataManager.hpp"
#include "src/Source/EngineDelegate.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

unsigned int E3DEngine::TextureDataManager::GetTextureBuffer(std::string imageName)
{
	return 0;
}

E3DEngine::TextureData * E3DEngine::TextureDataManager::GetTextureDataFromFile(std::string imageName)
{
	E3DEngine::TextureData * imgData = new E3DEngine::TextureData();
	int width, height, bpp;
	char *bits = (char*)stbi_load(imageName.c_str(), &width, &height, &bpp, 0);
	char * outByte = nullptr;

	imgData->rgbModule = bpp;
	if (bpp == PixelFormat::R8G8B8)
	{
		outByte = (char*)malloc(width * height * 3);
		memcpy(outByte, bits, width*height * 3);
	}
	else if (bpp == PixelFormat::R8G8B8A8)
	{
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

void E3DEngine::TextureDataManager::Cleanup()
{
	
}
