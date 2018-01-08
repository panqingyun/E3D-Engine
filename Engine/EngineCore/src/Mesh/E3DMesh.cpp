/*
 * Create 2017 PanQingyun.
 *
 */

#include "../Mesh/E3DMesh.h"
#include "Helpers.h"
#include <cstdlib>
#include "../Animation/E3DAnimation.hpp"
#include "../Mesh/E3DMeshBuffer.hpp"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{
	void MeshRender::initBoneMatrix()
	{
		VecBoneMatrix.resize( m_pMeshBuffer->VecBoneMatrix.size());
		for (map<string, Bone*>::iterator it = m_pMeshBuffer->BoneMapping.begin(); it != m_pMeshBuffer->BoneMapping.end(); ++it)
		{
			Bone * bone = new Bone(it->second);
			BoneMapping[it->first] = bone;
			
			VecBoneMatrix[it->second->ID] = &bone->Transform->WorldMatrix;
		}
	}

	Bone * MeshRender::HasBoneWithKeyP(int imPointIndex)
	{
		for (map<string, Bone*>::iterator it = BoneMapping.begin(); it != BoneMapping.end(); ++it)
		{
			if(it->second->IsImpoint && it->second->KeyP.KeyIndex == imPointIndex)
			{
				return it->second;
			}
		}
		
		return nullptr;
	}
	
	MeshRender::MeshRender(MeshBuffer * buffer)
	{
		m_pMeshBuffer	= buffer;
		pScene			= buffer->pScene;
		m_nIndexSize	= (DWORD)buffer->Indices.size();
		initBoneMatrix();
		//setDrawModule(GL_TRIANGLES);
		NodeType = eT_Mesh;
	}

	MeshRender::~MeshRender()
	{
		BoneMapping.clear();
		VecBoneMatrix.clear();
	}

	void MeshRender::prepareRender(float deltaTime)
	{
		m_pMeshBuffer->BindBufferData();
	}
	
	void MeshRender::SetDontDestory(bool dontDestory)
	{
		for (map<string,Bone*>::iterator it = BoneMapping.begin(); it != BoneMapping.end(); ++it)
		{
			EngineDelegate::GetInstance().AddDonotDestory(it->second);
		}
	}
}
