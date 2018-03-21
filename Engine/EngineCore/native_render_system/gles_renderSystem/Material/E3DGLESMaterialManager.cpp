//
//  E3DMaterialManager.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DGLESMaterialManager.hpp"
#include "src/Config/Table.h"
#include "src/Config/TableRegister.h"
#include "3rd/header/Helpers.h"
#include "E3DGLESMaterial.hpp"

namespace E3DEngine
{
	Material * GLES_MaterialManager::GetMaterial(int id)
	{
		if (m_mapIDMaterials.find(id) == m_mapIDMaterials.end())
		{
			return nullptr;
		}
		return m_mapIDMaterials[id];
	}

	Material* GLES_MaterialManager::CreateMaterial(std::string path, int id)
	{
		TableManager* tblManager = TableRegister::RegisterAllTable(path.c_str());
		if (tblManager == nullptr)
		{
			return nullptr;
		}

		MaterialConfig * materialConfig = tblManager->Select<MaterialConfig>(id);
		if (materialConfig is nullptr)
		{
			SAFE_DELETE(tblManager);
			return nullptr;
		}
		std::string folder, file;
		StringManipulator::SplitFileName(path, folder, file);
		MaterialConfig *config = materialConfig;
		GLES_Material * material = new GLES_Material;
		material->SetBlendType((BLEND_TYPE)config->BlendType);
		material->SetEnableDepthTest(config->EnableDepthTest == 1);
		material->SetEnableCullFace(config->CullFace == 0);
		material->filePath = folder + "/";
		ShaderConfig * sCfg = tblManager->Select<ShaderConfig>(config->ShaderID);
		material->MaterialTableManager = tblManager;
		material->CreateMaterial(config, sCfg);
		m_mapIDMaterials[material->ID] = material;
		return material;
	}
}
