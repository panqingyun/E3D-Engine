//
//  E3DMaterialManager.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DMaterialManager.hpp"
#include "src/Source/ClassFactory.h"
#include "src/Source/EngineDelegate.h"
#include "src/Config/Table.h"
#include "src/Config/TableRegister.h"
#include "3rd/header/Helpers.h"

namespace E3DEngine
{
	Material * MaterialManager::GetMaterial(int id)
	{
		return nullptr;
	}

	Material* MaterialManager::CreateMaterial(std::string path)
	{
		return nullptr;
	}
	
	void MaterialManager::Cleanup()
	{
		for (auto it : m_mapIDMaterials)
		{			
			it.second->Destory();
			SAFE_DELETE(it.second);
		}
		m_mapIDMaterials.clear();
	}

}
