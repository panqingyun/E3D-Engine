#ifndef __GL_SHADER_MANAGER_H__
#define __GL_SHADER_MANAGER_H__

#include  <src/RenderSystem/Shader/E3DShaderManager.h>
#include "E3DGLShader.hpp"

namespace E3DEngine
{
	using namespace GLRenderSystem;
	class GL_ShaderManager : public ShaderManager
	{
	public: 
		GL_ShaderManager();

	protected:
		virtual Shader * createShader(std::string shaderPath) override;
		virtual void initShaderAttributeVar() override;

	protected:
		std::string processVS(); 
		void processUniformVar(GL_Shader *shader, std::string& shaderContent);
		void processAttributeVar(GL_Shader *shader, std::string attri, std::string &shaderContent);
		void processEngineDefineUniform(GL_Shader *shader);
		std::string preProcessShader(GL_Shader *shader, std::string shaderFileName, std::string &vs_content, std::string &fs_content);

		void appendInclude(std::string &strLine,  std::string folder);
		std::string getCommonString(std::string &str);
		void getVertex(GL_Shader *shader, std::string &str, std::string folder, std::string &vs_content);
		void getFragment(GL_Shader *shader, std::string &str, std::string folder, std::string &fs_content);
		virtual void createAttribute(std::string	typeName, int StartPosition, uint VarType, BOOL Normalized, uint VertexStructSize, uint AttributeSize, uint	BindLocation, std::string attrType, uint type);

	private:
		std::map<std::string, Attribute> staticAttributeMap;
		std::map<std::string, Attribute> dynamicAttributeMap;
	};
}

#endif // !__GLES_SHADER_MANAGER_H__
