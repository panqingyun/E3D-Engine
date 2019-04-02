//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2018-7-12 PanQingyun. All rights reserved. *************************//

#include "E3DShaderManager.h"
#include "E3DShader.hpp"
#include "../../Config/Table.h"
#include "../../Source/E3DDebug.h"

E3DEngine::Shader * E3DEngine::ShaderManager::CreateShader(ShaderConfig * sCfg, std::string materailPath)
{
	std::string key = materailPath + sCfg->ShaderPath;
	if (mShadersMap.find(key) != mShadersMap.end())
	{
		return mShadersMap[key];
	}
	Shader * shader = createShader(getShaderWithExtName(materailPath + sCfg->ShaderPath));
	
	return shader;
}

E3DEngine::Shader * E3DEngine::ShaderManager::GetShader(std::string shaderFullPath)
{ 
	if (mShadersMap.find(shaderFullPath) != mShadersMap.end())
	{
		return mShadersMap[shaderFullPath];
	}
	Shader * shader = createShader(getShaderWithExtName(shaderFullPath));
	mShadersMap[shaderFullPath] = shader;
	return shader;
}

void E3DEngine::ShaderManager::Cleanup()
{
	mShadersMap.clear();
}

std::string E3DEngine::ShaderManager::getShaderWithExtName(std::string & path)
{
	return path + ".glsl";
}


