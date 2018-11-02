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
#include "src/Source/Helpers.h"

namespace E3DEngine
{

	MaterialManager::MaterialManager()
	{
		
	}

	Material * MaterialManager::GetMaterial(int id)
	{
		if (m_mapIDMaterials.find(id) == m_mapIDMaterials.end())
		{
			return nullptr;
		}
		return m_mapIDMaterials[id];
	}

	Material* MaterialManager::CreateMaterial(std::string path, int id)
	{
		GetRenderSystem()->UseShareContext();
		if (m_mapConfigMaterial.find(path) != m_mapConfigMaterial.end())
		{
			if (m_mapConfigMaterial[path].find(id) != m_mapConfigMaterial[path].end())
			{
				return m_mapConfigMaterial[path][id];
			}
		}
		TableManager* tblManager = TableRegister::GetTableManager(path.c_str());
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
		Material * material = createMatrerial();
		std::map<int, DWORD>::iterator srcItr = m_BlendFactorMap.find(config->SrcBlendFactor);
		std::map<int, DWORD>::iterator dstItr = m_BlendFactorMap.find(config->DstBlendFactor);

		DWORD srcFactor = 0, dstFactor = 0;
		srcFactor = srcItr != m_BlendFactorMap.end() ? srcItr->second : 0;
		dstFactor = dstItr != m_BlendFactorMap.end() ? dstItr->second : 0;
		material->SetBlendType(srcFactor, dstFactor);
		material->SetEnableDepthTest(config->EnableDepthTest == 1);
		material->SetEnableDepthWrite(config->EnableWriteDepth == 1);
		material->SetEnableCullFace(config->CullFace == 0);
		material->mFilePath = folder + "/";
		material->mMaterialTableManager = tblManager;
		material->CreateMaterial(config);
		m_mapIDMaterials[material->ID] = material;
		m_mapConfigMaterial[path][id] = material;
		GetRenderSystem()->UseRenderContext();
		return material;
	}
	
	void MaterialManager::Cleanup()
	{
		for (auto it : m_mapIDMaterials)
		{			
			it.second->Destory();
			SAFE_DELETE(it.second);
		}
		m_mapIDMaterials.clear();
		m_mapConfigMaterial.clear();
	}


	E3DEngine::Material * MaterialManager::createMatrerial()
	{
		return nullptr;
	}

}
