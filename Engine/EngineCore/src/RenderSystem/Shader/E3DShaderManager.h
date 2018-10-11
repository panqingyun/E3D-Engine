﻿
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2018-7-12 PanQingyun. All rights reserved. *************************//

#ifndef __E3D_SHADER_MANAGER_H__
#define __E3D_SHADER_MANAGER_H__

#include "../../Source/Interface.h"
#include "E3DShader.hpp"

namespace E3DEngine
{
	class Shader;
	class ShaderConfig;
	class E3D_EXPORT_DLL ShaderManager : public IManager
	{
	public: 
		virtual Shader * GetShader(ShaderConfig * sCfg, std::string materailPath);
		virtual void Cleanup();

	protected:
		virtual Shader* createShader(std::string shaderPath, std::string unifVar);
		virtual void parseShaderConfig(ShaderConfig *cfg);
		virtual void initShaderAttributeVar();
	protected:
		std::map<std::string, Shader*> mShadersMap;
	};
}

#endif
