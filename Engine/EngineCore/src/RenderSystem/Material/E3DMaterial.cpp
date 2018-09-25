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
		Textures.clear();
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Material);
		Object::setBehaviourDefaultValue();
		enablewriteDepth = true;
	}
	
	void Material::Destory()
	{
		SAFE_DELETE(MaterialTableManager);
		for (std::map<UINT, Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		Textures.clear();
		SAFE_DELETE(pShader);
	}

	void Material::CreateMaterial(MaterialConfig * config, ShaderConfig * sCfg)
	{
		mMaterialConfig = config;
		if (mMaterialConfig != nullptr)
		{
			if (sCfg == nullptr)
			{
				return;
			}
			CreateShader(sCfg);
			
			for (auto& sp : mShader->GetSamplerNameValue())
			{
				TextureData* tData = GetRenderSystem()->GetTextureDataManager()->GetTextureDataFromFile(mFilePath + sp.second);
				tData->clampType = (CLAMP_TYPE)config->TextureClampType;
				tData->filterType = (FILTER_TYPE)config->TextureFilterType;
				tData->fileName = sp.second;
				tData->uniformName = sp.first;
				createTexture(*tData);
				SAFE_DELETE(tData);
			}
		}
	}

	void Material::SetTexture(Texture * texture, int index)
	{
		
	}

	void Material::createTexture(TextureData& data)
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

}
