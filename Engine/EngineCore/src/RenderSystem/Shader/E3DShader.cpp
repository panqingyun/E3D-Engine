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
#include "../E3DRenderSystem.hpp"
#include "../Texture/E3DTexture2D.hpp"
#include "../Texture/E3DTexture.hpp"

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
	}

	void Shader::UpdateFloatValue(std::string name, float value)
	{
		if (float1UniformList.find(name) == float1UniformList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}

		float1UniformList[name].Value = value;
	}

	void Shader::UpdateFloatValue(std::string name, float value1, float value2)
	{
		if (float2UniformList.find(name) == float2UniformList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}

		float2UniformList[name].Value1 = value1;
		float2UniformList[name].Value2 = value2;

	}


	void Shader::UpdateFloatValue(std::string name, float value1, float value2, float value3)
	{
		if (float3UniformList.find(name) == float3UniformList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
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
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
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
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}

		int1UniformList[name].Value = value;
	}

	void Shader::UpdateMatrix2Value(std::string name, const  float * data)
	{
		if (matrix2UniformList.find(name) == matrix2UniformList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}

		matrix2UniformList[name].Data = data;
		matrix2UniformList[name].Transpos = 0;
	}

	void Shader::UpdateMatrix3Value(std::string name, const  float * data)
	{
		if (matrix3UniformList.find(name) == matrix3UniformList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}

		matrix3UniformList[name].Data = data;
		matrix3UniformList[name].Transpos = 0;
	}

	void Shader::UpdateMatrix4Value(std::string name,const float * data)
	{
		if (matrix4UniformList.find(name) == matrix4UniformList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}

		matrix4UniformList[name].Data = data;
		matrix4UniformList[name].Transpos = 0;
	}


	void Shader::UpdataFloat1ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float1UniformArrayList.find(name) == float1UniformArrayList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}
		float1UniformArrayList[name].Value = value;
	}

	void Shader::UpdataFloat2ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float2UniformArrayList.find(name) == float2UniformArrayList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}
		float2UniformArrayList[name].Value = value;
	}

	void Shader::UpdataFloat3ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float3UniformArrayList.find(name) == float3UniformArrayList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}
		float3UniformArrayList[name].Value = value;
	}

	void Shader::UpdataFloat4ArrayUniform(std::string name, std::vector<float> value)
	{
		if (float4UniformArrayList.find(name) == float4UniformArrayList.end())
		{
			Debug::Log(ell_Error, "uniform not defined %s", name.c_str());
			return;
		}
		float4UniformArrayList[name].Value = value;
	}


	void Shader::RunUniformFunc(std::string uniformType, std::string uniformName, std::string defaultVale, int size)
	{
		(this->*uniformSetFunc[uniformType])(uniformName.c_str(), defaultVale, size);
		uniformTypeMap[uniformName] = uniformType;
	}

	void Shader::UpdateSampler2D(std::string name, Texture *texture, int index)
	{
		if (sampler2DUniformList.find(name) == sampler2DUniformList.end())
		{
			return;
		}

		sampler2DUniformList[name].texture = texture;
		sampler2DUniformList[name].TextureIndex = index;
	}


	void Shader::UpdateSamplerCube(std::string name, CubeMapTexture *texture, int index)
	{
		if (samplerCubeUniformList.find(name) == samplerCubeUniformList.end())
		{
			return;
		}
		samplerCubeUniformList[name].texture = texture;
		samplerCubeUniformList[name].TextureIndex = index;
	}

	unsigned int Shader::GetUniformLocation(std::string uniformName)
	{
		if (uniformLocationMap.find(uniformName) == uniformLocationMap.end())
		{
			return 0;
		}
		return uniformLocationMap[uniformName];
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

	void Shader::createSampler2DUniform(std::string varName, std::string defValue, int count)
	{
		sampler2DUniform uni;
		uni.VarName = varName;
		sampler2DUniformList[varName] = uni;
	}


	void Shader::createSamplerCubeUniform(std::string varName, std::string defValue, int count)
	{
		samplerCubeUniform uni;
		uni.VarName = varName;
		samplerCubeUniformList[varName] = uni;
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

	void Shader::processUniformVar(string uniformVariable)
	{

	}

	std::string Shader::GetUniformType(std::string uniformName)
	{
		if (uniformTypeMap.find(uniformName) == uniformTypeMap.end())
		{
			return empty_string;
		}
		return uniformTypeMap[uniformName];
	}

	void Shader::SetFileName(std::string name)
	{
		mFileName = name;
	}
}
