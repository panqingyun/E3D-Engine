//
//  Texture2D.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//
#include "src/Source/EngineDelegate.h"
#include "E3DTexture2D.hpp"
namespace E3DEngine
{

	Texture2D::~Texture2D()
	{
		
	}

	void Texture2D::Create(string fileName)
	{
	}
	
	void Texture2D::SetTextureData(TextureData &tData)
	{
		
	}

	void Texture2D::Create(TextureData &tData)
	{
		
	}

	void Texture2D::SetTextureEnum(uint enumNumber)
	{
		m_nTextureEnum = enumNumber;
	}
	
	void Texture2D::ActiveBindTexture()
	{
		
	}

	void Texture2D::InvalidTexture()
	{
		
	}

	Texture2D::Texture2D()
	{
		CreateBehaviour();
	}

	void Texture2D::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Texture2D);
		setBehaviourDefaultValue();
	}

}
