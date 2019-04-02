
//********************************** Effective 3D Engine **************************************************//
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
		Shader * GetShader(std::string shaderFullPath);
		Shader * CreateShader(ShaderConfig * sCfg, std::string materailPath);
		void Cleanup();

	protected:
		std::string getShaderWithExtName(std::string &path); // 拼接扩展名
		virtual Shader* createShader(std::string shaderPath)	= 0;
		virtual void initShaderAttributeVar()										= 0;
	protected:
		std::map<std::string, Shader*> mShadersMap;
	};
}

#endif
