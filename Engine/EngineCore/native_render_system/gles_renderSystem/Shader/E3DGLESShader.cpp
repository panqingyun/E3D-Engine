//
//  Shader.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DGLESShader.hpp"
#include "src/Source/E3DDebug.h"

namespace E3DEngine
{
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
