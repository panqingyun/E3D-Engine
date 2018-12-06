//
//  Material.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "../Material/E3DMaterial.hpp"
#include "src/Source/EngineDelegate.h"
#include "src/Config/Table.h"
#include "../../Config/TableRegister.h"

namespace E3DEngine
{
	const std::string stringType	= "string";
	const std::string intType		= "int";
	const std::string floatType		= "float";
	const std::string doubleType	= "double";
	const std::string boolType		= "bool";
	const std::string sampler2DType	  = "sampler2D";
	const std::string samplerCubeType = "samplerCube";

	Material::Material()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Material);
		Object::setBehaviourDefaultValue();
		enablewriteDepth = true;
		mColor = vec4f(1, 1, 1, 1);
	}
	
	void Material::Destory()
	{
		SAFE_DELETE(mMaterialTableManager);
		SAFE_DELETE(mShader);
	}

	void Material::CreateMaterial(MaterialConfig * config)
	{
		mMaterialConfig = config;
		if (mMaterialConfig != nullptr)
		{
			ShaderConfig * sCfg = mMaterialTableManager->Select<ShaderConfig>(config->ShaderID);
			if (sCfg == nullptr)
			{
				return;
			}
			mShader = GetRenderSystem()->GetShaderManager()->CreateShader(sCfg, mFilePath);
			if (config->Color != empty_string)
			{
				mColor = Convert::ToColorRGBA(config->Color);
			}
			initUniformValue(sCfg, config);

		}
	}

	void Material::SetEnableDepthWrite(bool bEnable)
	{
		enablewriteDepth = bEnable;
	}

	MonoBehaviour * Material::GetBehaviour()
	{
		return mBehaviour;
	}


	void Material::SetColor(Color4 color)
	{
		mColor.r *= color.r;
		mColor.g *= color.g;
		mColor.b *= color.b;
		mColor.a *= color.a;
	}

	void Material::SetBlendType(DWORD src, DWORD dst)
	{
		srcBlendFactor = src; dstBlendFactor = dst;
	}

	void Material::SetEnableDepthTest(bool enable)
	{
		enableDepthTest = enable;
	}


	void Material::SetEnableCullFace(bool enable)
	{
		enableDoubleSide = enable;
	}


	E3DEngine::Shader * Material::GetShader()
	{
		return mShader;
	}

	void Material::CreateShader(ShaderConfig *cfg)
	{
		
	}

	void Material::initUniformValue(ShaderConfig * sCfg, MaterialConfig * config)
	{
		std::string &uniformVarDefault = sCfg->UniformVariable;
		std::vector<std::string> uniformVarDefaultValue = StringBuilder::Split(uniformVarDefault, ";");

		for (auto& sp : uniformVarDefaultValue)
		{
			std::vector<std::string> varValues = StringBuilder::Split(sp, "=");
			if (varValues.empty())
			{
				continue;
			}
			std::string uniformType = mShader->GetUniformType(varValues[0]);
			if (uniformType == sampler2DType) // create texture
			{
				createSampler2D(varValues, config);
			}
			else if (uniformType == samplerCubeType)
			{				
				createCubeTexture(varValues);
			}
			else if (uniformType == intType)
			{
				mShader->UpdateIntValue(varValues[0], Convert::ToFloat(varValues[1]));
			}
			else if (uniformType == floatType)
			{
				mShader->UpdateFloatValue(varValues[0], Convert::ToFloat(varValues[1]));
			}
		}
	}

	void Material::createCubeTexture(std::vector<std::string> &varValues)
	{
		std::vector<std::string> vec = StringBuilder::Split(varValues[1], ":");
		if (vec.empty())
		{
			return;
		}
		TextureData data;
		data.configID = Convert::ToInt(vec[1]);
		data.fileName = Application::AppDataPath + vec[0];
		CubeMapTexture * texture = (CubeMapTexture *)GetRenderSystem()->GetTextureDataManager()->GetTexture(TextureType::eCUBMAP_TEXTURE, &data);
		mShader->UpdateSamplerCube(varValues[0], texture, textureCount);
		textureCount++;
	}

	Render2Texture *Material::GetRenderTexture()
	{
		return Rtt;
	}

	void Material::createRtt(std::vector<std::string>& varValues)
	{
		std::vector<std::string> vec = StringBuilder::Split(varValues[1], ":");
		if (vec.empty())
		{
			return;
		}
		std::string fName = vec[0];
		std::string _path = Application::AppDataPath + fName;

		if (varValues[1][0] == '.' && varValues[1][0] == varValues[1][1])
		{ // 相对目录， 相程序运行目录
			_path = fName;
		}
		TableManager * rttTabMgr = TableRegister::GetTableManager(_path.c_str());

		int &&Id = Convert::ToInt(vec[1]);

		RenderTextureConfig* rttCfg = rttTabMgr->Select<RenderTextureConfig>(Id);
		if (rttCfg != nullptr)
		{
			TextureData tData;
			tData.width = rttCfg->Width;
			tData.height = rttCfg->Height;
			tData.fileName = fName;
			tData.configID = Id;
			tData.target = rttCfg->Target;
			std::string v1 = varValues[0];
			Render2Texture *rtt = nullptr;
			if (GetRenderSystem()->getIsMutilThreadRender())
			{
				rtt = GetRenderSystem()->GetTextureDataManager()->CreateRender2Texture(&tData);
			}
			else
			{
				rtt = GetRenderSystem()->GetTextureDataManager()->CreateRender2TextureSingleThread(&tData);
			}
			mShader->UpdateSampler2D(v1, rtt, textureCount);
			textureCount++;
			Rtt = rtt;
		}
	}

	void Material::createSampler2D(std::vector<std::string> &varValues, MaterialConfig * config)
	{
		std::string name = varValues[1];
		std::string uniName = varValues[0];
		size_t pointPos = name.find_last_of('.');
		std::string extention = name.substr(pointPos);
		if (extention.find(".renderTexture") != std::string::npos)
		{
			createRtt(varValues);
		}
		else
		{
			TextureData tData;
			tData.clampType = (CLAMP_TYPE)config->TextureClampType;
			tData.filterType = (FILTER_TYPE)config->TextureFilterType;
			tData.fileName = Application::AppDataPath + name;
			tData.uniformName = uniName;
			Texture * texture = GetRenderSystem()->GetTextureDataManager()->GetTexture(TextureType::eTEXTURE_2D, &tData);
			mShader->UpdateSampler2D(uniName, texture, textureCount);
			textureCount++;
		}
	}

	int Material::GetTextureCount()
	{
		return textureCount;
	}

}
