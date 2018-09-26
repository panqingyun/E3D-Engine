
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2018-7-12 PanQingyun. All rights reserved. *************************//

#ifndef __E3D_SHADER_MANAGER_H__
#define __E3D_SHADER_MANAGER_H__

#include "../../Source/Interface.h"

namespace E3DEngine
{
	class Shader;
	class E3D_EXPORT_DLL ShaderManager : public IManager
	{
	public: 
		virtual Shader * GetShaderContentByPath(std::string shaderPath);
		virtual void Cleanup() { }
	protected:
		std::map<std::string, std::string> mShadersMap;
	};
}

#endif
