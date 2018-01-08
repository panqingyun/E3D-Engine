//
//  SkinAnimation.cpp
//  Created by 潘庆云 on 2017/3/28.
//

#include "E3DSkinAnimation.hpp"

namespace E3DEngine
{
	void SkinAnimation::Start()
	{
		m_pMesh = (MeshRender*)gameObject;
		SetScene(m_pMesh->pScene);
		SetBones(&m_pMesh->BoneMapping);
		LoadAnimations();
	}
	
	void SkinAnimation::Destory()
	{
		
	}
}
