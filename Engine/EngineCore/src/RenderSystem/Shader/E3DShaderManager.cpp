//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2018-7-12 PanQingyun. All rights reserved. *************************//

#include "E3DShaderManager.h"
#include "E3DShader.hpp"
#include "../../Config/Table.h"
#include "../../Source/E3DDebug.h"

E3DEngine::Shader * E3DEngine::ShaderManager::GetShader(ShaderConfig * sCfg, std::string materailPath)
{
	/*std::string key = sCfg->VertexShader + sCfg->FragmentShader;
	if (mShadersMap.find(key) != mShadersMap.end())
	{
		return mShadersMap[key];
	}*/
	Shader * shader = createShader(materailPath + sCfg->ShaderPath, sCfg->UniformVariable);
	//mShadersMap[key] = shader;
	return shader;
}

void E3DEngine::ShaderManager::Cleanup()
{
	mShadersMap.clear();
}

E3DEngine::Shader* E3DEngine::ShaderManager::createShader(std::string shaderPath, std::string unifVar)
{
	return nullptr;
}

void E3DEngine::ShaderManager::parseShaderConfig(ShaderConfig *cfg)
{
	
}

void E3DEngine::ShaderManager::initShaderAttributeVar()
{

}

