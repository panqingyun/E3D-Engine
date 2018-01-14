//
//  Shader.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <src/Utils/E3DUtil.hpp>
#include "../../Config/Table.h"

#define IF_AVAILABLE(value) if((int)value != -1)

namespace E3DEngine
{
#define  MODEL_MATRIX "_e3d_matModel"
#define  PROJ_MATRIX "_e3d_matProj"
#define  VIEW_MATRIX "_e3d_matView"
#define  ROTATION_VEC "_e3d_Rotation"
#define  CAMERA_POS  "_e3d_cameraPos"
#define  LIGHT_COLOR "_e3d_WorldSpaceLightColor"
#define  LIGHT_POS "_e3d_WorldSpaceLightPos"

	struct Uniform
	{
		std::string  VarName;
		int		 UniformName;
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

	struct Attribute  
	{
		std::string  AttribType;		// 如 vec3
		std::string  TypeName;			// 语义 如 POSITION 代表这个属性是用来做什么的
		std::string  VarName;			// Shader里面的变量名
		uint		 AttributeName;		// 变量的位置，使用glGetAttribLocation获取到的值
		int			 StartPosition;		// 在顶点数据结构中的起始位置
		uint		 VarType;			// 数据类型，如 GL_FLOAT
		uint		 Normalized;		// 是否归一化
		uint		 VertexStructSize;	// 顶点结构大小
		uint		 AttributeSize;		// 该属性的大小
		uint		 BindLocation;		// 绑定到Shader中的位置
	};

	struct VertexData
	{
		float * Data;
		int size;
	};

	class Shader 
	{
		using setShaderValueFunc = void(Shader::*)(std::string varName, std::string defValueFormat);
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

	protected:
		std::map<std::string , float1Uniform> float1UniformList;
		std::map<std::string , float2Uniform> float2UniformList;
		std::map<std::string , float3Uniform> float3UniformList;
		std::map<std::string , float4Uniform> float4UniformList;
		std::map<std::string , matrixUniform> matrix4UniformList;
		std::map<std::string , matrixUniform> matrix3UniformList;
		std::map<std::string, matrixUniform> matrix2UniformList;
		std::map<std::string, int1Uniform> int1UniformList;

		std::vector<Attribute> AttributeList;

	public:
		virtual void	DeleteShader() { }

		std::string GetFileRelativeFolder();
		void SetFileRelativeFolder(std::string path);
		std::map<std::string, std::string> &GetSamplerNameValue();
	public:
		void createInt1Uniform(std::string varName, std::string defValueFormat);
		void createFloat1Uniform(std::string varName, std::string defValueFormat);
		void createFloat2Uniform(std::string varName, std::string defValueFormat);
		void createFloat3Uniform(std::string varName, std::string defValueFormat);
		void createFloat4Uniform(std::string varName, std::string defValueFormat);
		void createMatrix2Uniform(std::string varName, std::string defValueFormat);
		void createMatrix3Uniform(std::string varName, std::string defValueFormat);
		void createMatrix4Uniform(std::string varName, std::string defValueFormat);
		void createSamplerUniform(std::string varName, std::string defValueFormat);

		virtual void createAttribute(std::string		typeName,
			int		StartPosition,
			uint		VarType,
			BOOL		Normalized,
			uint		VertexStructSize,
			uint		AttributeSize,
			uint		BindLocation,
			std::string attrType);
		virtual void CreateShaderUniform(std::string varName);

	protected:
		virtual void processAttribVar(ShaderConfig * cfg);
		virtual void processUniformVar(ShaderConfig * cfg);

	protected:
		std::map<std::string, Attribute> attributeMap;
		std::map<std::string, setShaderValueFunc> uniformSetFunc;
		std::map<std::string, std::string> varToTypeMap;
		std::map<std::string, std::string> samplerNameValue;

		std::string filePath;
	};
}

#endif /* Shader_hpp */
