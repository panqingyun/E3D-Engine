
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-5-24 PanQingyun. All rights reserved. *************************//

#include "E3DMeshRender.h"
#include <cstdlib>
#include "../Animation/E3DAnimation.hpp"
#include "E3DMesh.hpp"
#include "../Source/EngineDelegate.h"
#include <assimp/mesh.h> 
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

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

	/*void MeshRender::SetAiScene(const aiScene* scene)
	{
		pScene = scene;
	}
*/

	void MeshRender::SetBoneVector(vector<mat4f*> vecBones)
	{
		VecBoneMatrix = vecBones;
	}


	/*const aiScene * MeshRender::GetAiScene() const
	{
		return pScene;
	}*/


	std::vector<mat4f*> & MeshRender::GetBoneMatrixs()
	{
		return VecBoneMatrix;
	}

}
