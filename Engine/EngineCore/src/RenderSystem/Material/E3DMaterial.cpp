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
	Material::Material()
	{
		Textures.clear();
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Material);
		Object::setBehaviourDefaultValue();
		enablewriteDepth = true;
		mColor = vec4f(1, 1, 1, 1);
	}
	
	void Material::Destory()
	{
		SAFE_DELETE(mMaterialTableManager);
		Textures.clear();
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
			mShader = GetRenderSystem()->GetShaderManager()->GetShader(sCfg, mFilePath);
			if (config->Color != empty_string)
			{
				mColor = Convert::ToColorRGBA(config->Color);
			}
			initUniformValue(sCfg, config);

		}
	}

	void Material::SetTexture(Texture * texture, int index)
	{
		
	}

	void Material::createTexture2D(TextureData& data)
	{
		
	}

	void Material::createCubeTexture(std::string filePath, int selectID, std::string uniformName)
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


	void Material::SetEnableDepthWrite(bool bEnable)
	{
		enablewriteDepth = bEnable;
	}

	void Material::CreateCubeTexture(std::string dirPath, std::string xPName, std::string xNName, std::string yPName, std::string yNName, std::string zPName, std::string ZNName)
	{

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


	void Material::CreateShader(ShaderConfig *cfg)
	{
		
	}

	void Material::initUniformValue(ShaderConfig * sCfg, MaterialConfig * config)
	{
		std::string &uniformVarDefault = sCfg->UniformVariable;
		std::vector<std::string> uniformVarDefaultValue = StringBuilder::Split(uniformVarDefault, ";");

		for (auto& sp : uniformVarDefaultValue)
		{
			std::vector<std::string> varValues = StringBuilder::Split(sp, "-");
			if (varValues.empty())
			{
				continue;
			}

			if (mShader->GetUniformType(varValues[0]) == "sampler2D") // create texture
			{
				createSampler2D(varValues, config);
			}
			else if (mShader->GetUniformType(varValues[0]) == "samplerCube")
			{
				std::vector<std::string> vec = StringBuilder::Split(varValues[1], ":");
				if (vec.empty())
				{
					return;
				}
				std::string fName = vec[0];
				std::string _path = Application::AppDataPath + fName;
				int selectID = Convert::ToInt(vec[1]);
				createCubeTexture(_path, selectID, varValues[0]);
			}
		}
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
			Render2Texture *rtt = GetRenderSystem()->GetTextureDataManager()->CreateRender2Texture(rttCfg->Width, rttCfg->Height);
			rtt->SetTextureUniformName(varValues[0]);
			SetTexture(rtt);
			Rtt = rtt;
		}
	}

	void Material::createSampler2D(std::vector<std::string> &varValues, MaterialConfig * config)
	{
		size_t pointPos = varValues[1].find_last_of('.');
		std::string extention = varValues[1].substr(pointPos);
		if (extention.find(".renderTexture") != std::string::npos)
		{
			createRtt(varValues);
		}
		else
		{
			TextureData* tData = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(Application::AppDataPath + varValues[1]);
			tData->clampType = (CLAMP_TYPE)config->TextureClampType;
			tData->filterType = (FILTER_TYPE)config->TextureFilterType;
			tData->fileName = varValues[1];
			tData->uniformName = varValues[0];
			createTexture2D(*tData);
			SAFE_DELETE(tData);
		}
	}

}
