//
//  E3DMaterialManager.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DGLESMaterialManager.hpp"
#include "src/Config/Table.h"
#include "src/Config/TableRegister.h"
#include "src/Source/Helpers.h"
#include "E3DGLESMaterial.hpp"

namespace E3DEngine
{
	std::map<std::string, DWORD> g_BlendFactorMap;


	GLES_MaterialManager::GLES_MaterialManager()
	{
		g_BlendFactorMap["ZERO"] = GL_ZERO;
		g_BlendFactorMap["ONE"] = GL_ONE;
		g_BlendFactorMap["SRC_COLOR"] = GL_SRC_COLOR;
		g_BlendFactorMap["ONE_MINUS_SRC_COLOR"] = GL_ONE_MINUS_SRC_COLOR;
		g_BlendFactorMap["SRC_ALPHA"] = GL_SRC_ALPHA;
		g_BlendFactorMap["ONE_MINUS_SRC_ALPHA"] = GL_ONE_MINUS_SRC_ALPHA;
		g_BlendFactorMap["DST_ALPHA"] = GL_DST_ALPHA;
		g_BlendFactorMap["ONE_MINUS_DST_ALPHA"] = GL_ONE_MINUS_DST_ALPHA;
		g_BlendFactorMap["DST_COLOR"] = GL_DST_COLOR;
		g_BlendFactorMap["ONE_MINUS_DST_COLOR"] = GL_ONE_MINUS_DST_COLOR;
	}

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
		GLES_Material * material = new GLES_Material;
		DWORD srcFactor = GL_NONE, dstFactor = GL_NONE;
		std::map<std::string, DWORD>::iterator srcItr = g_BlendFactorMap.find(config->SrcBlendFactor);
		std::map<std::string, DWORD>::iterator dstItr = g_BlendFactorMap.find(config->DstBlendFactor);
		srcFactor = srcItr != g_BlendFactorMap.end() ? srcItr->second : GL_NONE;
		dstFactor = dstItr != g_BlendFactorMap.end() ? dstItr->second : GL_ONE;
		material->SetBlendType(srcFactor, dstFactor);
		material->SetEnableDepthTest(config->EnableDepthTest == 1);
		material->SetEnableDepthWrite(config->EnableWriteDepth == 1);
		material->SetEnableCullFace(config->CullFace == 0);
		material->mFilePath = folder + "/";
		ShaderConfig * sCfg = tblManager->Select<ShaderConfig>(config->ShaderID);
		material->mMaterialTableManager = tblManager;
		material->CreateMaterial(config, sCfg);
		m_mapIDMaterials[material->ID] = material;
		return material;
	}
}
