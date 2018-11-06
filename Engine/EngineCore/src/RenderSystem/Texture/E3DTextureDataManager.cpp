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


E3DEngine::Render2Texture* E3DEngine::TextureDataManager::CreateRender2Texture(float width, float height)
{
	Render2Texture *rtt = createRender2Texture();
	vec2f *size = new vec2f(width, height);
	auto f = [](void *param1, void* param2)
	{
		Render2Texture * rt = (Render2Texture *)param1;
		vec2f *size = (vec2f*)param2;

		rt->CreateRenderTarget(size->x, size->y);
	};

	ThreadTool::GetInstance().AddInvoke(LOGIC_THREAD_ID, RENDER_THREAD_ID, f, rtt, size);
	return rtt;
	
}


E3DEngine::Render2Texture* E3DEngine::TextureDataManager::CreateRender2TextureSingleThread(float width, float height)
{
	Render2Texture *rtt = createRender2Texture();
	rtt->CreateRenderTarget(width, height);
	return rtt;
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
	else if (bpp == PixelFormat::L8A8)
	{
		outByte = (char*)malloc(width * height * 2);
		memcpy(outByte, bits, width*height * 2);
	}
	else if (bpp == PixelFormat::L8)
	{
		outByte = (char*)malloc(width * height);
		memcpy(outByte, bits, width*height);
	}
	else
	{
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
