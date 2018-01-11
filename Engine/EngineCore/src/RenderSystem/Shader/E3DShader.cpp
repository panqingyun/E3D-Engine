//
//  Shader.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DShader.hpp"
#include "src/Object/E3DTransform.hpp"
#include "../Material/E3DMaterial.hpp"
#include "src/Source/E3DDebug.h"

namespace E3DEngine
{
	Shader::~Shader()
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

	void Shader::UpdateFloatValue(std::string name, float value)
	{
		if (float1UniformList.find(name) == float1UniformList.end())
		{
			return;
		}

		float1UniformList[name].Value = value;
	}

	void Shader::UpdateFloatValue(std::string name, float value1, float value2)
	{
		if (float2UniformList.find(name) == float2UniformList.end())
		{
			return;
		}

		float2UniformList[name].Value1 = value1;
		float2UniformList[name].Value2 = value2;

	}


	void Shader::UpdateFloatValue(std::string name, float value1, float value2, float value3)
	{
		if (float3UniformList.find(name) == float3UniformList.end())
		{
			return;
		}

		float3UniformList[name].Value1 = value1;
		float3UniformList[name].Value2 = value2;
		float3UniformList[name].Value3 = value3;
	}

	void Shader::UpdateFloatValue(std::string name, float value1, float value2, float value3, float value4)
	{
		if (float4UniformList.find(name) == float4UniformList.end())
		{
			return;
		}

		float4UniformList[name].Value1 = value1;
		float4UniformList[name].Value2 = value2;
		float4UniformList[name].Value3 = value3;
		float4UniformList[name].Value4 = value4;
	}

	void Shader::UpdateIntValue(std::string name, int value)
	{
		if (int1UniformList.find(name) == int1UniformList.end())
		{
			return;
		}

		int1UniformList[name].Value = value;
	}

	void Shader::UpdateMatrix2Value(std::string name, const  float * data)
	{
		if (matrix2UniformList.find(name) == matrix2UniformList.end())
		{
			return;
		}

		matrix2UniformList[name].Data = data;
		matrix2UniformList[name].Transpos = 0;
	}

	void Shader::UpdateMatrix3Value(std::string name, const  float * data)
	{
		if (matrix3UniformList.find(name) == matrix3UniformList.end())
		{
			return;
		}

		matrix3UniformList[name].Data = data;
		matrix3UniformList[name].Transpos = 0;
	}

	void Shader::UpdateMatrix4Value(std::string name,const float * data)
	{
		if (matrix4UniformList.find(name) == matrix4UniformList.end())
		{
			return;
		}

		matrix4UniformList[name].Data = data;
		matrix4UniformList[name].Transpos = 0;
	}


	void Shader::createInt1Uniform(std::string varName, std::string defValueFormat)
	{
		int1Uniform uni;
		uni.VarName = varName;
		int1UniformList[varName] = uni;
	}

	void Shader::createFloat1Uniform(std::string varName, std::string defValueFormat)
	{
		float1Uniform uni;
		uni.VarName = varName;
		float1UniformList[varName] = uni;
	}

	void Shader::createFloat2Uniform(std::string varName, std::string defValueFormat)
	{
		float2Uniform uni;
		uni.VarName = varName;
		float2UniformList[varName] = uni;
	}

	void Shader::createFloat3Uniform(std::string varName, std::string defValueFormat)
	{
		float3Uniform uni;
		uni.VarName = varName;
		float3UniformList[varName] = uni;
	}

	void Shader::createFloat4Uniform(std::string varName, std::string defValueFormat)
	{
		float4Uniform uni;
		uni.VarName = varName;
		float4UniformList[varName] = uni;
	}

	void Shader::createMatrix2Uniform(std::string varName, std::string defValueFormat)
	{
		matrixUniform matrix;
		matrix.Count = 1;
		matrix.VarName = varName;
		matrix2UniformList[varName] = matrix;
	}

	void Shader::createMatrix3Uniform(std::string varName, std::string defValueFormat)
	{
		matrixUniform matrix;
		matrix.Count = 1;
		matrix.VarName = varName;
		matrix3UniformList[varName] = matrix;
	}

	void Shader::createMatrix4Uniform(std::string varName, std::string defValueFormat)
	{
		matrixUniform matrix;
		matrix.Count = 1;
		matrix.VarName = varName;
		matrix4UniformList[varName] = matrix;
	}

	void Shader::createSamplerUniform(std::string varName, std::string defValue)
	{
		samplerNameValue[varName] = defValue;
	}

	void Shader::createAttribute(std::string typeName, int StartPosition, uint VarType, BOOL Normalized, uint VertexStructSize, uint AttributeSize, uint BindLocation, std::string attrType)
	{
		Attribute attribute;
		attribute.AttributeSize = AttributeSize;
		attribute.BindLocation = BindLocation;
		attribute.Normalized = Normalized;
		attribute.StartPosition = StartPosition;
		attribute.VarName = "";
		attribute.VarType = VarType;
		attribute.AttribType = attrType;

		attribute.VertexStructSize = VertexStructSize;
		attributeMap[typeName] = attribute;
	}

	void Shader::CreateShaderUniform(std::string varName)
	{
		if (varToTypeMap.find(varName) == varToTypeMap.end())
		{
			return;
		}
		std::string typeName = varToTypeMap[varName];
		(this->*uniformSetFunc[typeName])(varName.c_str(), "");
	}

	void Shader::processUniformVar(ShaderConfig * cfg)
	{

	}


	std::string Shader::GetFileRelativeFolder()
	{
		return filePath;
	}


	void Shader::SetFileRelativeFolder(std::string path)
	{
		filePath = path;
	}

	std::map<std::string, std::string> & Shader::GetSamplerNameValue()
	{
		return samplerNameValue;
	}

	void Shader::processAttribVar(ShaderConfig * cfg)
	{
		std::vector<std::string> attribVar = StringBuilder::Split(cfg->AttribVariable, ";");
		for (auto &attrib : attribVar)
		{
			std::string attribKeyValue = StringBuilder::Trim(attrib);
			if (attrib == empty_string)
			{
				continue;
			}
			std::vector<std::string> attribKey = StringBuilder::Split(attribKeyValue, ":");
			if (attribKey.size() != 2)
			{
				Debug::Log(ell_Error, "attribute varible format is wrong!");
				assert(false);
			}

			std::string attribTypeName = attribKey[0];
			std::string attribVarName = attribKey[1];

			if (attributeMap.find(attribTypeName) == attributeMap.end())
			{
				Debug::Log(ell_Error, "attribute varible type is wrong!");
				assert(false);
			}
			int typeSize = attributeMap[attribTypeName].AttributeSize;
			Attribute attr = attributeMap[attribTypeName];
			attributeMap[attribTypeName].VarName = attribVarName;
			attr.VarName = attribVarName;
			attr.TypeName = attribTypeName;
			AttributeList.emplace_back(attr);
		}
	}
}
