//
//  Shader.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DGLESShader.hpp"
#include <src/Source/E3DDebug.h>
#include <src/Config/Table.h>
#include <src/Source/Application.h>
#include <src/RenderSystem/Material/E3DMaterial.hpp>
#include <3rd/header/Helpers.h>
#include <src/Source/E3DVertex.h>
#include <src/Scene/E3DSceneManager.hpp>

namespace E3DEngine
{

	std::string GLES_Shader::processVS()
	{
#ifdef __IOS__
		std::string priveVs = "#define __IOS__\n";
#endif
#ifdef __ANDROID__
		std::string priveVs = "#define __ANDROID__\n";
#endif
#ifdef WIN32
		std::string priveVs = "#define __WIN32__\n";
#endif
		if (SceneManager::GetInstance().GetCurrentScene()->GetDirectionalLight() != nullptr)
		{
			priveVs.append("#define USING_DIRECTIONAL_LIGHT  \n");
			priveVs.append("uniform vec3 ").append(LIGHT_DIR).append(";\n");
			priveVs.append("uniform vec4 ").append(LIGHT_COLOR).append(";\n");
		}
		std::map<UINT, Light*>& pointLights = SceneManager::GetInstance().GetCurrentScene()->GetPointLights();
		if (pointLights.size() != 0)
		{
			std::string lightCount = Convert::ToString((int)pointLights.size());
			priveVs.append("#define USING_POINT_LIGHT  \n");
			priveVs.append("const int _e3d_PointLightCount = ").append(lightCount).append(";\n");
			priveVs.append("uniform vec3 ").append(POINT_LIGHT_POS).append("[").append(lightCount).append("];\n");
			priveVs.append("uniform float ").append(POINT_LIGHT_RANGE).append("[").append(lightCount).append("];\n");
			priveVs.append("uniform vec4 ").append(POINT_LIGHT_COLOR).append("[").append(lightCount).append("];\n");
		}
		priveVs.append("uniform mat4 ").append(VIEW_MATRIX).append(";\nuniform mat4 ").append(MODEL_MATRIX).append(";\nuniform mat4 ").append(PROJ_MATRIX).append(";\nuniform vec3 ").append(CAMERA_POS).append(";\n");
		priveVs.append("uniform vec3 ").append(ROTATION_VEC).append(";\n");
		priveVs.append("mat4 _e3d_getMVPMatrix()\n");
		priveVs.append("{\n");
		priveVs.append("\treturn ").append(PROJ_MATRIX).append(" * ").append(VIEW_MATRIX).append(" * ").append(MODEL_MATRIX).append(";\n");
		priveVs.append("}\n");
		for (auto &attri : attributeMap)
		{
			if (attri.second.VarName == "")
			{
				continue;
			}
			priveVs.append("attribute ").append(attri.second.AttribType).append(" ").append(attri.second.VarName).append(";\n");
		}
		return priveVs;
	}

	std::string preProcessShader(std::string shaderFileName)
	{
		std::ifstream infile;
		infile.open(shaderFileName.data());   //将文件流对象与文件连接起来 
		std::string strLine;
		std::string shaderContent = "";
		std::string folder, fileName;
		StringManipulator::SplitFileName(shaderFileName, folder, fileName);
		while (getline(infile, strLine))
		{
			if (strLine.find("#include") != std::string::npos)
			{
				int startPos = strLine.find_first_of("\"");
				int endPos = strLine.find_last_of("\"");
				if (startPos == std::string::npos)
				{
					assert(false);
				}
				std::string file = strLine.substr(startPos + 1, endPos - startPos - 1);
				shaderContent.append(vvision::getContentFromPath(folder + "/" + file)).append("\n");
			}
			else
			{
				shaderContent.append(strLine).append("\n");
			}
		}
		return shaderContent;
	}

	void GLES_Shader::LoadShader(ShaderConfig *cfg)
	{
		if (cfg == nullptr)
		{
			Debug::Log(ell_Error, "shader config is null");
			return;
		}

		processUniformVar(cfg);
		processAttribVar(cfg);

		std::string path = filePath;
		std::string shaderContent = preProcessShader(path +  cfg->VertexShader);
		std::string vertexShaderString = processVS().append(shaderContent);
		std::string fragmentShaderString = preProcessShader(path + cfg->FragmentShader);

		LoadShader(vertexShaderString.c_str(), fragmentShaderString.c_str());
	}

	void GLES_Shader::InitShaderVar()
	{
		createAttribute("POSITION", 0, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_VERTEX, "vec3");
		createAttribute("NORMAL", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_NORMAL, "vec3");
		createAttribute("COLOR", 6, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_COLOR, "vec4");
		createAttribute("TEXTURECOORD", 10, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE0, "vec2");
		createAttribute("TANGENT", 12, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TANGENT, "vec3");
		createAttribute("BONEINDEX", 15, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_INDICES, "vec4");
		createAttribute("BONEWEIGHT", 19, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_WEIGHTS, "vec4");
		createAttribute("TRANSPOSITION", 23, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_POSITION, "vec3");
		createAttribute("TRANSSCALE", 26, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_SCALE, "vec3");
		createAttribute("TRANSROTATE", 29, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_ROTETION, "vec3");
		createAttribute("SHADERINDEX", 32, GL_FLOAT, GL_FALSE, sizeof(Vertex), 1, LOCATION_ATTRIB_FRAGMENT_INDEX, "float");
		uniformSetFunc["float"] = &Shader::createFloat1Uniform;
		uniformSetFunc["float[]"] = &Shader::createFloat1ArrayUniform;
		uniformSetFunc["vec2"] = &Shader::createFloat2Uniform;
		uniformSetFunc["vec3"] = &Shader::createFloat3Uniform;
		uniformSetFunc["vec4"] = &Shader::createFloat4Uniform;
		uniformSetFunc["vec2[]"] = &Shader::createFloat2ArrayUniform;
		uniformSetFunc["vec3[]"] = &Shader::createFloat3ArrayUniform;
		uniformSetFunc["vec4[]"] = &Shader::createFloat4ArrayUniform;
		uniformSetFunc["mat2"] = &Shader::createMatrix2Uniform;
		uniformSetFunc["mat3"] = &Shader::createMatrix3Uniform;
		uniformSetFunc["mat4"] = &Shader::createMatrix4Uniform;
		uniformSetFunc["int"] = &Shader::createInt1Uniform;
		uniformSetFunc["sampler2D"] = &Shader::createSamplerUniform;
	}


	void GLES_Shader::processUniformVar(ShaderConfig * cfg)
	{
		std::vector<std::string> uniformVar = StringBuilder::Split(cfg->UniformVariable, ";");
		for (auto &uniform : uniformVar)
		{
			std::string uniformKeyValue = StringBuilder::Trim(uniform);
			if (uniformKeyValue == empty_string)
			{
				continue;
			}
			bool hasDefaultVale = true;
			int size = 1;
			// 临时只处理一下sampler2D
			if (uniformKeyValue.find("-") != std::string::npos)
			{
				hasDefaultVale = true;
			}
			else
			{
				hasDefaultVale = false;

			}
			std::vector<std::string> uniformKey = StringBuilder::Split(uniformKeyValue, ":");
			std::string uniformValue = "";
			std::string defaultVale = "";
			if (uniformKey[0].find("[") != std::string::npos) //数组
			{
				std::vector<std::string> values = StringBuilder::Split(uniformKey[0], "[");
				uniformKey[0] = values[0] + "[]";

				size_t pos = values[1].find("]");
				if (pos != std::string::npos)
				{
					size = Convert::ToInt(values[1].substr(0, pos));
				}
			}
			if (hasDefaultVale)
			{
				std::vector<std::string> values = StringBuilder::Split(uniformKey[1], "-");
				uniformValue = values[0];
				defaultVale = values[1];
			}
			else
			{
				uniformValue = uniformKey[1];
			}
			(this->*uniformSetFunc[uniformKey[0]])(uniformValue.c_str(), defaultVale, size);

		}
		processEngineDefineUniform();

	}

	void GLES_Shader::processEngineDefineUniform()
	{
		(this->*uniformSetFunc["mat4"])(PROJ_MATRIX, "", 1);
		(this->*uniformSetFunc["mat4"])(VIEW_MATRIX, "", 1);
		(this->*uniformSetFunc["mat4"])(MODEL_MATRIX, "", 1);
		(this->*uniformSetFunc["vec3"])(CAMERA_POS, "", 1);
		(this->*uniformSetFunc["vec3"])(ROTATION_VEC, "", 1);
		if (SceneManager::GetInstance().GetCurrentScene()->GetDirectionalLight() != nullptr)
		{
			(this->*uniformSetFunc["vec4"])(LIGHT_COLOR, "", 1);
			(this->*uniformSetFunc["vec3"])(LIGHT_DIR, "", 1);
		}
		std::map<UINT, Light*>& pointLights = SceneManager::GetInstance().GetCurrentScene()->GetPointLights();
		if (pointLights.size() != 0)
		{
			(this->*uniformSetFunc["vec4[]"])(POINT_LIGHT_COLOR, "", pointLights.size());
			(this->*uniformSetFunc["vec3[]"])(POINT_LIGHT_POS, "", pointLights.size());
			(this->*uniformSetFunc["float[]"])(POINT_LIGHT_RANGE, "", pointLights.size());
		}
	}

	void GLES_Shader::LoadShader(const char *vertexShader, const char *fragmentShader)
	{
		ShaderProgram = glCreateProgram();
		GLuint vertexShaderHandle = compileShader(vertexShader, GL_VERTEX_SHADER);
		GLuint fragmentShaderHandle = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

		glAttachShader(ShaderProgram, vertexShaderHandle);
		glAttachShader(ShaderProgram, fragmentShaderHandle);
		bindAttribLoaction();
		glLinkProgram(ShaderProgram);
		GLint linkSuccess;
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &linkSuccess);
		if (linkSuccess != GL_TRUE)
		{
			GLint logLength;
			glGetShaderiv(ShaderProgram, GL_INFO_LOG_LENGTH, &logLength);
			if (logLength > 0)
			{
				GLchar *log = (GLchar *)malloc(logLength);
				glGetShaderInfoLog(ShaderProgram, logLength, &logLength, log);
				Debug::Log(ell_Error, "Shader: LINK ERROR shader link log: %s" , log);
			}
			glDeleteShader(ShaderProgram);
		}
		
		if (vertexShaderHandle != 0)
		{
			glDeleteShader(vertexShaderHandle);
		}
		if (fragmentShaderHandle != 0)
		{
			glDeleteShader(fragmentShaderHandle);
		}
		loadUniformLocation();
		loadAttribLocation();
	}


	GLuint GLES_Shader::compileShader(const char* shaderContent, GLenum shaderType)
	{
		if (shaderContent == nullptr)
		{
			return 0;
		}
		int shaderStringLength = (int)strlen(shaderContent);
		GLuint shaderHandle = glCreateShader(shaderType);
		glShaderSource(shaderHandle, 1, &shaderContent, &shaderStringLength);
		glCompileShader(shaderHandle);

		GLint status;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLint logLength;
			glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
			if (logLength > 0)
			{
				GLchar *log = (GLchar *)malloc(logLength);
				glGetShaderInfoLog(shaderHandle, logLength, &logLength, log);
				Debug::Log(ell_Error, "Shader: [ERROR] shader compile log: %s", log); 
			}
			glDeleteShader(shaderHandle);
		}

		return shaderHandle;
	}


	void GLES_Shader::compileShaders()
	{

	}

	void GLES_Shader::UseProgram()
	{
		glUseProgram(ShaderProgram);
	}

	void GLES_Shader::UseNullProgram()
	{
		glUseProgram(NULL_SHADER);
	}

	void GLES_Shader::UpdateProgramUniformValue()
	{		
		for (auto & uniformKeyValue : int1UniformList)
		{
			glUniform1i(uniformKeyValue.second.UniformName, uniformKeyValue.second.Value);
		}

		for (auto & uniformKeyValue : float1UniformList)
		{
			glUniform1f(uniformKeyValue.second.UniformName, uniformKeyValue.second.Value);
		}

		for (auto & uniformKeyValue : float2UniformList)
		{
			glUniform2f(uniformKeyValue.second.UniformName, uniformKeyValue.second.Value1, uniformKeyValue.second.Value2);
		}

		for (auto & uniformKeyValue : float1UniformArrayList)
		{
			glUniform1fv(uniformKeyValue.second.UniformName, uniformKeyValue.second.Count, uniformKeyValue.second.Value.data());
		}

		for (auto & uniformKeyValue : float2UniformArrayList)
		{
			glUniform2fv(uniformKeyValue.second.UniformName,uniformKeyValue.second.Count,uniformKeyValue.second.Value.data());
		}

		for (auto & uniformKeyValue : float3UniformArrayList)
		{
			glUniform3fv(uniformKeyValue.second.UniformName, uniformKeyValue.second.Count, uniformKeyValue.second.Value.data());
		}

		for (auto & uniformKeyValue : float4UniformArrayList)
		{
			glUniform4fv(uniformKeyValue.second.UniformName, uniformKeyValue.second.Count, uniformKeyValue.second.Value.data());
		}

		for (auto & uniformKeyValue : float3UniformList)
		{
			glUniform3f(uniformKeyValue.second.UniformName, uniformKeyValue.second.Value1, uniformKeyValue.second.Value2, uniformKeyValue.second.Value3);
		}

		for (auto & uniformKeyValue : float4UniformList)
		{
			glUniform4f(uniformKeyValue.second.UniformName, uniformKeyValue.second.Value1, uniformKeyValue.second.Value2, uniformKeyValue.second.Value3, uniformKeyValue.second.Value4);
		}

		for (auto & uniformKeyValue : matrix4UniformList)
		{
			if (uniformKeyValue.second.Data == nullptr)
			{
				break;
			}
			glUniformMatrix4fv(uniformKeyValue.second.UniformName, uniformKeyValue.second.Count, uniformKeyValue.second.Transpos, uniformKeyValue.second.Data);
		}

		for (auto & uniformKeyValue : matrix3UniformList)
		{
			if (uniformKeyValue.second.Data == nullptr)
			{
				break;
			}
			glUniformMatrix3fv(uniformKeyValue.second.UniformName, uniformKeyValue.second.Count, uniformKeyValue.second.Transpos, uniformKeyValue.second.Data);
		}

		for (auto & uniformKeyValue : matrix2UniformList)
		{
			if (uniformKeyValue.second.Data == nullptr)
			{
				break;
			}
			glUniformMatrix2fv(uniformKeyValue.second.UniformName, uniformKeyValue.second.Count, uniformKeyValue.second.Transpos, uniformKeyValue.second.Data);
		}
	}

	void GLES_Shader::UpdateAttribPointerValue()
	{
		EnableVertexAttribArray();

		for (auto & attrib : AttributeList)
		{
			glVertexAttribPointer(attrib.AttributeName, attrib.AttributeSize, attrib.VarType, attrib.Normalized, attrib.VertexStructSize, (GLfloat*)nullptr + attrib.StartPosition);
		}
	}

	void GLES_Shader::DeleteShader()
	{
		glDeleteShader(ShaderProgram);
	}

	void GLES_Shader::EnableVertexAttribArray()
	{
		for (auto & attrib : AttributeList)
		{
			glEnableVertexAttribArray(attrib.AttributeName);
		}
		
	}

	void GLES_Shader::bindAttribLoaction()
	{
		for (auto & attrib : AttributeList)
		{
			glBindAttribLocation(ShaderProgram, attrib.BindLocation, attrib.VarName.c_str());
		}
	}

	void GLES_Shader::loadAttribLocation()
	{
		for (auto & attrib : AttributeList)
		{
			attrib.AttributeName = LoadSelfDefAttribuate(attrib.VarName);
		}
	}

	void GLES_Shader::loadUniformLocation()
	{
		for (auto & uniformKeyValue : int1UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float1UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float2UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float3UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float4UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : matrix2UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : matrix3UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : matrix4UniformList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float1UniformArrayList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float2UniformArrayList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float3UniformArrayList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}

		for (auto & uniformKeyValue : float4UniformArrayList)
		{
			uniformKeyValue.second.UniformName = LoadSelfDefUniform(uniformKeyValue.first);
		}
	}


	GLES_Shader::~GLES_Shader()
	{
		DeleteShader();
		float1UniformList.clear();
		float2UniformList.clear();
		float3UniformList.clear();
		float4UniformList.clear();
		matrix4UniformList.clear();
		matrix3UniformList.clear();
		matrix2UniformList.clear();
		int1UniformList.clear();
		AttributeList.clear();
	}

	GLint GLES_Shader::LoadSelfDefUniform(std::string name)
	{
		return glGetUniformLocation(ShaderProgram, name.c_str());
	}

	GLuint GLES_Shader::LoadSelfDefAttribuate(std::string name)
	{
		GLuint attr = glGetAttribLocation(ShaderProgram, name.c_str());
		int err = glGetError();
		//glEnableVertexAttribArray(attr);
		return attr;
	}
}
