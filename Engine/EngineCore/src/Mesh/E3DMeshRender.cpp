/*
 * Create 2017 PanQingyun.
 *
 */

#include "E3DMeshRender.h"
#include "Helpers.h"
#include <cstdlib>
#include "../Animation/E3DAnimation.hpp"
#include "E3DMesh.hpp"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{
	/*void MeshRender::initBoneMatrix()
	{
		VecBoneMatrix.resize( m_pMeshBuffer->VecBoneMatrix.size());
		for (map<string, Bone*>::iterator it = m_pMeshBuffer->BoneMapping.begin(); it != m_pMeshBuffer->BoneMapping.end(); ++it)
		{
			Bone * bone = new Bone(it->second);
			BoneMapping[it->first] = bone;
			
			VecBoneMatrix[it->second->ID] = &bone->Transform->WorldMatrix;
		}
	}*/


	MeshRender::~MeshRender()
	{
	}

	void MeshRender::SetAiScene(const aiScene* scene)
	{
		pScene = scene;
	}


	void MeshRender::SetBoneVector(vector<mat4f*> vecBones)
	{
		VecBoneMatrix = vecBones;
	}


	const aiScene * MeshRender::GetAiScene() const
	{
		return pScene;
	}


	std::vector<mat4f*> & MeshRender::GetBoneMatrixs()
	{
		return VecBoneMatrix;
	}

}
