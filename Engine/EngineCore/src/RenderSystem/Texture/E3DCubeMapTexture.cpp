//
//  E3DCubeMapTexture.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DCubeMapTexture.hpp"
#include "../E3DRenderSystem.hpp"
#include "../../Config/Table.h"
#include "../../Source/Application.h"
#include "../../Config/TableRegister.h"

namespace E3DEngine
{	

	void CubeMapTexture::Create(std::string fileName, int selectID)
	{
		TableManager *tblMgr = TableRegister::GetTableManager((fileName).c_str());
		if (tblMgr == nullptr)
		{
			return;
		}
		CubeMapTextureConfig *config = tblMgr->Select<CubeMapTextureConfig>(selectID);
		if (config == nullptr)
		{
			return;
		}

		createTexture(config);
	}

	void CubeMapTexture::createTexture(CubeMapTextureConfig *cubeMap)
	{
		TextureData * up_data = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + cubeMap->Top);
		TextureData * down_data = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + cubeMap->Down);
		TextureData * left_data = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + cubeMap->Left);
		TextureData * right_data = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + cubeMap->Right);
		TextureData * front_data = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + cubeMap->Front);
		TextureData * back_data = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + cubeMap->Back);
		createCubeMap(up_data, down_data, left_data, right_data, front_data, back_data);
		delete up_data;
		delete down_data;
		delete left_data;
		delete right_data;
		delete front_data;
		delete back_data;
	}
	
	void CubeMapTexture::createCubeMap(TextureData *up, TextureData *down, TextureData *left, TextureData *right, TextureData *front, TextureData *back)
	{

	}

}
