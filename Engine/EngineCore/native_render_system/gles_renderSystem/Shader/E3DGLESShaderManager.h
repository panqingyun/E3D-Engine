#ifndef __GLES_SHADER_MANAGER_H__
#define __GLES_SHADER_MANAGER_H__

#include  <src/RenderSystem/Shader/E3DShaderManager.h>
#include "E3DGLESShader.hpp"

namespace E3DEngine
{
	class GLES_ShaderManager : public ShaderManager
	{
	public: 
		GLES_ShaderManager();

	protected:
		virtual Shader * createShader(std::string shaderPath) override;
		virtual void initShaderAttributeVar() override;

	protected:
		std::string processVS(); 
		void processUniformVar(GLES_Shader *shader, std::string& shaderContent);
		void processAttributeVar(GLES_Shader *shader, std::string attri, std::string &shaderContent);
		void processEngineDefineUniform(GLES_Shader *shader);
		std::string preProcessShader(GLES_Shader *shader, std::string shaderFileName, std::string &vs_content, std::string &fs_content);

		std::string getCommonString(std::string &str);
		void appendInclude(std::string &strLine,  std::string folder);
		void getVertex(GLES_Shader *shader, std::string &str, std::string folder, std::string &vs_content);
		void getFragment(GLES_Shader *shader, std::string &str, std::string folder, std::string &fs_content);
		virtual void createAttribute(std::string	typeName, int StartPosition, uint VarType, BOOL Normalized, uint VertexStructSize, uint AttributeSize, uint	BindLocation, std::string attrType, uint type);

	private:
		std::map<std::string, Attribute> staticAttributeMap;
		std::map<std::string, Attribute> dynamicAttributeMap;
	};
}

#endif // !__GLES_SHADER_MANAGER_H__
