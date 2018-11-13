//
//  Shader.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef __E3D_SHADER_HPP__
#define __E3D_SHADER_HPP__

#include "../../Source/Interface.h"

#define IF_AVAILABLE(value) if((int)value != -1)

namespace E3DEngine
{
#define  MODEL_MATRIX "_e3d_matModel"
#define  PROJ_MATRIX "_e3d_matProj"
#define  VIEW_MATRIX "_e3d_matView"
#define  ROTATION_VEC "_e3d_Rotation"
#define  CAMERA_POS  "_e3d_CameraPos"
#define  LIGHT_COLOR "_e3d_WorldSpaceLightColor"
#define  LIGHT_DIR "_e3d_WorldSpaceLightDirection"
#define  LIGHT_DEPTH_TEX "_e3d_lightDepthTex"
#define  LIGHT_PROJ_MAT "_e3d_lightMatProj"
#define  LIGHT_VIEW_MAT "_e3d_lightMatView"
#define  POINT_LIGHT_POS "_e3d_PointLightPos"
#define	 POINT_LIGHT_COLOR "_e3d_PointLightColor"
#define	 POINT_LIGHT_RANGE "_e3d_PointLightRange"
#define  USING_DIRECTIONAL_LIGHT "USING_DIRECTIONAL_LIGHT"
#define  USING_POINT_LIGHT "USING_POINT_LIGHT"
#define  _e3d_PointLightCount "_e3d_PointLightCount"
#define  _Time "_Time"

	class Texture;
	class CubeMapTexture;

	struct Uniform
	{
		std::string  VarName;
		int		 UniformLocation;
	};

	struct int1Uniform : Uniform
	{
		int Value;
	};

	struct float1Uniform : Uniform
	{
		float Value;
	};

	struct float2Uniform : Uniform 
	{
		float Value1;
		float Value2;
	};

	struct float3Uniform : Uniform
	{
		float Value1;
		float Value2;
		float Value3;
	};
	
	struct float4Uniform : Uniform
	{
		float Value1;
		float Value2;
		float Value3;
		float Value4;
	};

	struct floatUniformArray : Uniform
	{
		int Count;
		std::vector<float> Value;
	};

	struct matrixUniform : Uniform
	{
		const float *	Data;
		int				Count;
		UINT			Transpos;
		matrixUniform()
		{
			Data = nullptr;
		}
	};

	struct sampler2DUniform : Uniform 
	{
		int TextureIndex;
		Texture * texture;
	};

	struct samplerCubeUniform : Uniform
	{
		int TextureIndex;
		CubeMapTexture * texture;
	};

	struct VertexData
	{
		float * Data;
		int size;
	};

	class ShaderConfig;

	class E3D_EXPORT_DLL Shader : public IObject
	{
		using setShaderValueFunc = void(Shader::*)(std::string varName, std::string defValueFormat, int count);
	public:
		Shader()
		{

		}
		virtual ~Shader();
		void UpdateFloatValue(std::string name, float value);
		void UpdateFloatValue(std::string name, float value1, float value2);
		void UpdateFloatValue(std::string name, float value1, float value2, float value3);
		void UpdateFloatValue(std::string name, float value1, float value2, float value3, float value4);
		void UpdateIntValue(std::string name, int value);
		void UpdateMatrix2Value(std::string name, const float * data);
		void UpdateMatrix3Value(std::string name, const  float * data);
		void UpdateMatrix4Value(std::string name, const  float * data);
		void UpdataFloat1ArrayUniform(std::string name, std::vector<float> value);
		void UpdataFloat2ArrayUniform(std::string name, std::vector<float> value);
		void UpdataFloat3ArrayUniform(std::string name, std::vector<float> value);
		void UpdataFloat4ArrayUniform(std::string name, std::vector<float> value);
		void RunUniformFunc(std::string uniformType, std::string uniformName, std::string defaultVale, int size);
		void UpdateSampler2D(std::string name, Texture *texture, int index);
		void UpdateSamplerCube(std::string name, CubeMapTexture *texture, int index);

		virtual unsigned int GetUniformLocation(std::string uniformName);
	public:
		virtual void	DeleteShader() { }
		std::map<std::string, std::string> &GetSamplerNameValue();
		std::string GetUniformType(std::string uniformName);

	public:
		void createInt1Uniform(std::string varName, std::string defValueFormat, int count);
		void createFloat1Uniform(std::string varName, std::string defValueFormat, int count);
		void createFloat2Uniform(std::string varName, std::string defValueFormat, int count);
		void createFloat3Uniform(std::string varName, std::string defValueFormat, int count);
		void createFloat4Uniform(std::string varName, std::string defValueFormat, int count);
		void createMatrix2Uniform(std::string varName, std::string defValueFormat, int count);
		void createMatrix3Uniform(std::string varName, std::string defValueFormat, int count);
		void createMatrix4Uniform(std::string varName, std::string defValueFormat, int count);
		void createSampler2DUniform(std::string varName, std::string defValueFormat, int count);
		void createSamplerCubeUniform(std::string varName, std::string defValueFormat, int count);
		void createFloat1ArrayUniform(std::string varName, std::string defValueFormat, int count);
		void createFloat2ArrayUniform(std::string varName, std::string defValueFormat, int count);
		void createFloat3ArrayUniform(std::string varName, std::string defValueFormat, int count);
		void createFloat4ArrayUniform(std::string varName, std::string defValueFormat, int count);

	protected:
		virtual void processUniformVar(std::string uniformVariable);

	protected:
		std::map<std::string, setShaderValueFunc> uniformSetFunc;
		std::map<std::string, float1Uniform> float1UniformList;
		std::map<std::string, float2Uniform> float2UniformList;
		std::map<std::string, float3Uniform> float3UniformList;
		std::map<std::string, float4Uniform> float4UniformList;
		std::map<std::string, matrixUniform> matrix4UniformList;
		std::map<std::string, matrixUniform> matrix3UniformList;
		std::map<std::string, matrixUniform> matrix2UniformList;
		std::map<std::string, sampler2DUniform> sampler2DUniformList;
		std::map<std::string, samplerCubeUniform> samplerCubeUniformList;
		std::map<std::string, int1Uniform> int1UniformList;
		std::map<std::string, floatUniformArray> float1UniformArrayList;
		std::map<std::string, floatUniformArray> float2UniformArrayList;
		std::map<std::string, floatUniformArray> float3UniformArrayList;
		std::map<std::string, floatUniformArray> float4UniformArrayList;

		std::map<std::string, std::string> uniformTypeMap;
		std::map<std::string, unsigned int> uniformLocationMap;
	};
}

#endif /* Shader_hpp */
