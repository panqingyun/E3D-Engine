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

}
