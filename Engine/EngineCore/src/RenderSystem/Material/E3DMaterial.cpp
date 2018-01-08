//
//  Material.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "../Material/E3DMaterial.hpp"
#include "src/Source/EngineDelegate.h"

namespace E3DEngine
{
	Material::Material()
	{
		Color = 0xffffffff;
		Textures.clear();
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Material);
		Object::setBehaviourDefaultValue();
	}
	
	void Material::Destory()
	{
		for (std::map<UINT, Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		Textures.clear();
	}

	void Material::CreateMaterial(MaterialConfig * config, ShaderConfig * sCfg)
	{
		pMaterialConfig = config;
		if (pMaterialConfig != nullptr)
		{
			if (sCfg == nullptr)
			{
				return;
			}
			Color = Convert::_16To10(pMaterialConfig->Color);
			CreateShader(sCfg);
			
			for (auto& sp : samplerNameValue)
			{
				createTexture(sp.second, sp.first);
			}
		}
	}

	void Material::SetTexture(Texture * texture, int index)
	{
		
	}

	void Material::createTexture(std::string textureName, std::string textureUniform)
	{
		
	}

	void Material::createTexture(Texture *texture, std::string textureUniform)
	{
		
	}

	void Material::BindTexture()
	{
		for (auto & it : Textures)
		{
			if (it.second == nullptr)
			{
				continue;
			}
			it.second->ActiveBindTexture();
		}
	}

	void Material::CreateCubeTexture(std::string dirPath, std::string xPName, std::string xNName, std::string yPName, std::string yNName, std::string zPName, std::string ZNName)
	{

	}


	MonoBehaviour * Material::GetBehaviour()
	{
		return m_pBehaviour;
	}

	void Material::UseMaterial()
	{
		
	}
    
	void Material::InvalidMaterial()
	{
		
	}

    void Material::beforeUpdate()
    {
  
    }

	void Material::afterUpdate()
	{

	}

	void Material::parseShaderConfig(ShaderConfig *cfg)
	{

	}

    void Material::enableStencil()
    {
        
    }
    
	void Material::createInt1Uniform(std::string varName, std::string defValueFormat)
	{
		int1Uniform uni;
		uni.VarName = varName;
		pShader->int1UniformList[varName] = uni;
	}

	void Material::createFloat1Uniform(std::string varName, std::string defValueFormat)
	{
		float1Uniform uni;
		uni.VarName = varName;
		pShader->float1UniformList[varName] = uni;
	}

	void Material::createFloat2Uniform(std::string varName, std::string defValueFormat)
	{
		float2Uniform uni;
		uni.VarName = varName;
		pShader->float2UniformList[varName] = uni;
	}

	void Material::createFloat3Uniform(std::string varName, std::string defValueFormat)
	{
		float3Uniform uni;
		uni.VarName = varName;
		pShader->float3UniformList[varName] = uni;
	}

	void Material::createFloat4Uniform(std::string varName, std::string defValueFormat)
	{
		float4Uniform uni;
		uni.VarName = varName;
		pShader->float4UniformList[varName] = uni;
	}

	void Material::createMatrix2Uniform(std::string varName, std::string defValueFormat)
	{
		matrixUniform matrix;
		matrix.Count		= 1;
		matrix.VarName		= varName;
		pShader->matrix2UniformList[varName] = matrix;
	}

	void Material::createMatrix3Uniform(std::string varName, std::string defValueFormat)
	{
		matrixUniform matrix;
		matrix.Count	= 1;
		matrix.VarName	= varName;
		pShader->matrix3UniformList[varName] = matrix;
	}

	void Material::createMatrix4Uniform(std::string varName, std::string defValueFormat)
	{
		matrixUniform matrix;
		matrix.Count = 1;
		matrix.VarName = varName;
		pShader->matrix4UniformList[varName] = matrix;
	}

	void Material::createSamplerUniform(std::string varName, std::string defValue)
	{
		samplerNameValue[varName] = defValue;
	}

	void Material::createAttribute(std::string typeName,int StartPosition, uint VarType, BOOL Normalized, uint VertexStructSize, uint AttributeSize, uint BindLocation)
	{
		Attribute attribute;
		attribute.AttributeSize = AttributeSize;
		attribute.BindLocation	= BindLocation;
		attribute.Normalized	= Normalized;
		attribute.StartPosition = StartPosition;
		attribute.VarName		= "";
		attribute.VarType		= VarType;

		attribute.VertexStructSize = VertexStructSize;
		attributeMap[typeName] = attribute;
	}

	void Material::CreateShaderUniform(std::string varName)
	{
		if (varToTypeMap.find(varName) == varToTypeMap.end())
		{
			return;
		}
		std::string typeName = varToTypeMap[varName];
		(this->*uniformSetFunc[typeName])(varName.c_str(), "");
	}

	void Material::processUniformVar(ShaderConfig * cfg)
	{
		
	}

	void Material::processAttribVar(ShaderConfig * cfg)
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
			attr.VarName = attribVarName.c_str();
			attr.TypeName = attribTypeName;
			pShader->AttributeList.emplace_back(attr);
		}
	}

}
