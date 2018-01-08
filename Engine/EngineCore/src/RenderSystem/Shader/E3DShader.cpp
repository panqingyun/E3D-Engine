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
}
