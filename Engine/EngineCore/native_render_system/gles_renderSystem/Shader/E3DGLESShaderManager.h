#ifndef __GLES_SHADER_MANAGER_H__
#define __GLES_SHADER_MANAGER_H__

#include  <src/RenderSystem/Shader/E3DShaderManager.h>

namespace E3DEngine
{
	class GLES_ShaderManager : public ShaderManager
	{

	public:
		virtual Shader * GetShaderContentByPath(std::string shaderPath) override;
	};
}

#endif // !__GLES_SHADER_MANAGER_H__
