//
//  Shader.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DShader.hpp"
#include "../../Object/E3DTransform.hpp"
#include "../Material/E3DMaterial.hpp"
#include "../../Source/E3DDebug.h"
#include "../../Source/E3DVertex.h"
#include "../../Config/Table.h"

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
		StaticAttributeList.clear();
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


	void Shader::UpdataFloat1ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float1UniformArrayList.find(name) == float1UniformArrayList.end())
		{
			return;
		}
		float1UniformArrayList[name].Value = value;
	}

	void Shader::UpdataFloat2ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float2UniformArrayList.find(name) == float2UniformArrayList.end())
		{
			return;
		}
		float2UniformArrayList[name].Value = value;
	}

	void Shader::UpdataFloat3ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float3UniformArrayList.find(name) == float3UniformArrayList.end())
		{
			return;
		}
		float3UniformArrayList[name].Value = value;
	}

	void Shader::UpdataFloat4ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float4UniformArrayList.find(name) == float4UniformArrayList.end())
		{
			return;
		}
		float4UniformArrayList[name].Value = value;
	}

	void Shader::createInt1Uniform(std::string varName, std::string defValueFormat, int count)
	{
		int1Uniform uni;
		uni.VarName = varName;
		int1UniformList[varName] = uni;
	}

	void Shader::createFloat1Uniform(std::string varName, std::string defValueFormat, int count)
	{
		float1Uniform uni;
		uni.VarName = varName;
		float1UniformList[varName] = uni;
	}

	void Shader::createFloat2Uniform(std::string varName, std::string defValueFormat, int count)
	{
		float2Uniform uni;
		uni.VarName = varName;
		float2UniformList[varName] = uni;
	}

	void Shader::createFloat3Uniform(std::string varName, std::string defValueFormat, int count)
	{
		float3Uniform uni;
		uni.VarName = varName;
		float3UniformList[varName] = uni;
	}

	void Shader::createFloat4Uniform(std::string varName, std::string defValueFormat, int count)
	{
		float4Uniform uni;
		uni.VarName = varName;
		float4UniformList[varName] = uni;
	}

	void Shader::createMatrix2Uniform(std::string varName, std::string defValueFormat, int count)
	{
		matrixUniform matrix;
		matrix.Count = count;
		matrix.VarName = varName;
		matrix2UniformList[varName] = matrix;
	}

	void Shader::createMatrix3Uniform(std::string varName, std::string defValueFormat, int count)
	{
		matrixUniform matrix;
		matrix.Count = count;
		matrix.VarName = varName;
		matrix3UniformList[varName] = matrix;
	}

	void Shader::createMatrix4Uniform(std::string varName, std::string defValueFormat, int count)
	{
		matrixUniform matrix;
		matrix.Count = count;
		matrix.VarName = varName;
		matrix4UniformList[varName] = matrix;
	}

	void Shader::createSamplerUniform(std::string varName, std::string defValue, int count)
	{
		samplerNameValue[varName] = defValue;
	}


	void Shader::createFloat1ArrayUniform(std::string varName, std::string defValueFormat, int count)
	{
		floatUniformArray uni;
		uni.Count = count;
		uni.VarName = varName;
		float1UniformArrayList[varName] = uni;
	}

	void Shader::createFloat2ArrayUniform(std::string varName, std::string defValueFormat, int count)
	{
		floatUniformArray uni;
		uni.Count = count;
		uni.VarName = varName;
		float2UniformArrayList[varName] = uni;
	}

	void Shader::createFloat3ArrayUniform(std::string varName, std::string defValueFormat, int count)
	{
		floatUniformArray uni;
		uni.Count = count;
		uni.VarName = varName;
		float3UniformArrayList[varName] = uni;
	}

	void Shader::createFloat4ArrayUniform(std::string varName, std::string defValueFormat, int count)
	{
		floatUniformArray uni;
		uni.Count = count;
		uni.VarName = varName;
		float4UniformArrayList[varName] = uni;
	}

	void Shader::createAttribute(std::string typeName, int StartPosition, uint VarType, BOOL Normalized, uint VertexStructSize, uint AttributeSize, uint BindLocation, std::string attrType, uint type)
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
		if (type == DYNAMIC_VERTEX)
		{
			dynamicAttributeMap[typeName] = attribute;
		}
		else
		{
			staticAttributeMap[typeName] = attribute;
		}
	}


	void Shader::processUniformVar(string uniformVariable)
	{

	}


	std::string Shader::GetFileRelativeFolder()
	{
		return mFilePath;
	}


	void Shader::SetFileRelativeFolder(std::string path)
	{
		mFilePath = path;
	}

	std::map<std::string, std::string> & Shader::GetSamplerNameValue()
	{
		return samplerNameValue;
	}

	void Shader::processAttribVar(string attribVariable)
	{
		std::vector<std::string> attribVar = StringBuilder::Split(attribVariable, ";");
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

			if (staticAttributeMap.find(attribTypeName) != staticAttributeMap.end())
			{
				int typeSize = staticAttributeMap[attribTypeName].AttributeSize;
				Attribute attr = staticAttributeMap[attribTypeName];
				staticAttributeMap[attribTypeName].VarName = attribVarName;
				attr.VarName = attribVarName;
				attr.TypeName = attribTypeName;
				StaticAttributeList.emplace_back(attr);
			}
			else if (dynamicAttributeMap.find(attribTypeName) != dynamicAttributeMap.end())
			{
				int typeSize = dynamicAttributeMap[attribTypeName].AttributeSize;
				Attribute attr = dynamicAttributeMap[attribTypeName];
				dynamicAttributeMap[attribTypeName].VarName = attribVarName;
				attr.VarName = attribVarName;
				attr.TypeName = attribTypeName;
				DynamicAttributeList.emplace_back(attr);
			}
			else
			{
				Debug::Log(ell_Error, "attribute varible type is wrong!");
				assert(false);
			}
		}
	}
}
