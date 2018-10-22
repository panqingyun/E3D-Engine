//
//  Texture.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//
#include "src/Source/EngineDelegate.h"
#include "E3DTexture.hpp"
namespace E3DEngine
{

	Texture::~Texture()
	{
		
	}

	void Texture::Create(string fileName)
	{
	}
	
	void Texture::SetTextureData(TextureData &tData)
	{
		
	}

	void Texture::Create(TextureData &tData)
	{
		
	}

	void Texture::SetTextureEnum(uint enumNumber)
	{
		m_nTextureEnum = enumNumber;
	}
	
	std::string Texture::GetUniformName()
	{
		return m_strTextureUniformName;
	}

	void Texture::ActiveBindTexture()
	{
		
	}

	void Texture::InvalidTexture()
	{
		
	}

	Texture::Texture()
	{
		CreateBehaviour();
	}

	void Texture::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Texture);
		setBehaviourDefaultValue();
	}

	void Texture::SetTextureUniformName(std::string name)
	{
		m_strTextureUniformName = name;
	}

}
