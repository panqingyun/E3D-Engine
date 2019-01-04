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

	void Texture2D::SetTextureData(Texture2dData *tData)
	{
		if (m_bIsReadWrite)
		{
			m_pTextureData = new Texture2dData;
			*m_pTextureData = *tData;
		}
	}

	void Texture2D::Create(Texture2dData *tData)
	{
		if (m_bIsReadWrite)
		{
			m_pTextureData = new Texture2dData;
			*m_pTextureData = *tData;
		}
	}

	Texture2D::Texture2D()
	{
		m_pTextureData = nullptr;
		m_bIsReadWrite = false;
		CreateBehaviour();
	}

	void Texture2D::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Texture2D);
		setBehaviourDefaultValue();
	}

	E3DEngine::Texture2dData * Texture2D::GetTextureData()
	{
		return m_pTextureData;
	}


	void Texture2D::SetIsReadWrite(bool bReadWrite)
	{
		m_bIsReadWrite = bReadWrite;
	}

}
