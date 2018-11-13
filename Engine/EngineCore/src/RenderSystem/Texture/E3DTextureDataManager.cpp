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
#include "../../Config/Table.h"

unsigned int E3DEngine::TextureDataManager::GetTextureBuffer(std::string imageName)
{
	return 0;
}


E3DEngine::Render2Texture* E3DEngine::TextureDataManager::CreateRender2Texture(TextureData *tData)
{
	string texture_key = tData->fileName + Convert::ToString(tData->configID);
	if (m_mapTextures.find(texture_key) != m_mapTextures.end())
	{
		return (E3DEngine::Render2Texture*)m_mapTextures[texture_key];
	}
	Render2Texture *rtt = createRender2Texture();
	m_mapTextures[texture_key] = rtt;
	vec2f *size = new vec2f(tData->width, tData->height);
	auto f = [](void *param1, void* param2)
	{
		Render2Texture * rt = (Render2Texture *)param1;
		vec2f *size = (vec2f*)param2;

		rt->CreateRenderTarget(size->x, size->y);
	};

	ThreadTool::GetInstance().AddInvoke(LOGIC_THREAD_ID, RENDER_THREAD_ID, f, rtt, size);
	return rtt;
	
}


E3DEngine::Render2Texture* E3DEngine::TextureDataManager::CreateRender2TextureSingleThread(TextureData *tData)
{
	string texture_key = tData->fileName + Convert::ToString(tData->configID);
	if (m_mapTextures.find(texture_key) != m_mapTextures.end())
	{
		return (E3DEngine::Render2Texture*)m_mapTextures[texture_key];
	}
	Render2Texture *rtt = createRender2Texture();
	if (tData->target == RENDER_TO_TEXTURE)
	{
		rtt->CreateRenderTarget(tData->width, tData->height);
	}
	else if (tData->target == RENDER_DEPTH)
	{
		rtt->CreateDepthTarget(tData->width, tData->height);
	}
	m_mapTextures[texture_key] = rtt;

	return rtt;
}

E3DEngine::TextureData * E3DEngine::TextureDataManager::GetTextureDataFromFile(std::string imageName, TextureData * InData)
{
	E3DEngine::TextureData * imgData = InData;
	if (InData == nullptr)
	{
		imgData = new E3DEngine::TextureData();
	} 
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


E3DEngine::Texture * E3DEngine::TextureDataManager::GetTexture(TextureType type, TextureData* tData)
{
	string texture_key = tData->fileName + Convert::ToString(tData->configID);
	Texture * texture = nullptr;
	if (m_mapTextures.find(texture_key) == m_mapTextures.end())
	{
		switch (type)
		{
		case E3DEngine::eTEXTURE_2D:
			GetTextureDataFromFile(tData->fileName, tData);
			texture = createTexture2D(tData);
			break;
		case E3DEngine::eCUBMAP_TEXTURE:
			texture = createCubeTexture(tData->fileName, tData->configID);
			break;
		default:
			break;
		}
	}
	else
	{
		texture = m_mapTextures[texture_key];
	}
	return texture;
}

void E3DEngine::TextureDataManager::Cleanup()
{
	for (auto &textureKV : m_mapTextures)
	{
		SAFE_DELETE(textureKV.second);
	}
	m_mapTextures.clear();
}

Texture * E3DEngine::TextureDataManager::createCubeTexture(std::string filePath, int selectID)
{
	return nullptr;
}
