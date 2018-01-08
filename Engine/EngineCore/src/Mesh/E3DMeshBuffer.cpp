//
//  E3DVertexBuffer.cpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#include "E3DMeshBuffer.hpp"
namespace E3DEngine
{
	MeshBuffer::MeshBuffer(const char * filePath, const char * filename, bool& bCreateSuccess)
	{
		NumBones = 0;
		m_bIsBufferData = false;
		//Transform->IsTransPosFirst = true;
		char  fullPath[1024];
		sprintf(fullPath, "%s/%s", filePath, filename);
		bool Ret	= false;
		pScene		= pImporter.ReadFile(fullPath, ASSIMP_LOAD_FLAGS);
		if (pScene)
		{
			Ret = initFromScene(pScene, fullPath);
			bCreateSuccess = true;
		}
		else
		{
			printf("Error parsing '%s': '%s'\n", fullPath, pImporter.GetErrorString());
			bCreateSuccess = false;
		}
		setVBOs();
		// 构建骨骼树
		aiNode *rootNode = pScene->mRootNode;
		for (int i = 0; i < rootNode->mNumChildren; i ++)
		{
			createBoneTree(rootNode->mChildren[i]);
		}
	}
	
	
	bool MeshBuffer::initFromScene(const aiScene *pScene, const string &Filename)
	{
		Entries.resize(pScene->mNumMeshes);
		
		uint NumVertices = 0;
		uint NumIndices = 0;
		
		for (uint i = 0 ; i < pScene->mNumMeshes ; i++)
		{
			Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
			Entries[i].NumIndices    = pScene->mMeshes[i]->mNumFaces * 3;
			Entries[i].BaseVertex    = NumVertices;
			Entries[i].BaseIndex     = NumIndices;
			NumVertices += pScene->mMeshes[i]->mNumVertices;
			NumIndices  += Entries[i].NumIndices;
		}
		for (uint i = 0 ; i < Entries.size() ; i++)
		{
			const aiMesh* paiMesh = pScene->mMeshes[i];
			initMesh(i, paiMesh);
		}
		
		return true;
	}
	
	void MeshBuffer::createBoneTree(aiNode * pNode)
	{
		if (BoneMapping.find(pNode->mName.data) == BoneMapping.end())
		{
			for (int i = 0; i < pNode->mNumChildren; ++i)
			{
				createBoneTree(pNode->mChildren[i]);
			}
			return;
		}
		// 根据Node结构创建骨骼树
		Bone *pBone = BoneMapping[pNode->mName.data];
		//transform->AddChild(pBone->Name, pBone->Transform);
		pBone->SetMetadata(pNode->mMetaData);
		float scaleX		= 0;
		float scaleY		= 0;
		float impointValue	= 0;
		float indexValue	= 0;
		pNode->mMetaData->Get<float>(PROPERTY_IS_IMPOINT, impointValue);
		pNode->mMetaData->Get<float>(PROPERTY_INDEX_IMPOINT, indexValue);
		pNode->mMetaData->Get<float>(PROPERTY_TRANSFORMSCALEX, scaleX);
		pNode->mMetaData->Get<float>(PROPERTY_TRANSFORMSCALEY, scaleY);
		impointValue == 1 ? pBone->IsImpoint = true : pBone->IsImpoint = false;
		pBone->KeyP.KeyIndex = indexValue;
		pBone->tranScaleX	 = scaleX;
		pBone->tranScaleY	 = scaleY;
		for (int i = 0; i < pNode->mNumChildren; ++i)
		{
			if (BoneMapping.find(pNode->mChildren[i]->mName.data) != BoneMapping.end())
			{// 找到一个节点和Bone重名 这个Bone在子节点中，所以是子骨骼
				pBone->AddChild(BoneMapping[pNode->mChildren[i]->mName.data]);
			}
			createBoneTree(pNode->mChildren[i]);
		}
		
	}
	
	void MeshBuffer::initMesh(uint MeshIndex, const aiMesh* paiMesh)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		const aiColor4D Default4D(1.0f,1.0f, 1.0f, 1.0f);
		for (uint i = 0 ; i < paiMesh->mNumVertices ; i++)
		{
			const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i])	: &Zero3D;
			const aiColor4D * pColor	= paiMesh->HasVertexColors(0)  ? &(paiMesh->mColors[0][i])			: &Default4D;
			const aiVector3D* pTangent	= paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mTangents[i])	: &Zero3D;
			
			aiColor4D realColor = aiColor4D(pColor->r ,pColor->g ,pColor->b ,pColor->a);
			Vertex vertex;
			vertex.SetPosition(pPos->x, pPos->y, pPos->z);
			vertex.SettextureCoord(pTexCoord->x,pTexCoord->y);
			vertex.SetNormal(pNormal->x, pNormal->y, pNormal->z);
			vertex.SetColor(realColor.r,realColor.g,realColor.b, realColor.a);
			vertex.SetTangent(pTangent->x, pTangent->y, pTangent->z);
			Vertices.push_back(vertex);
		}
		
		loadBones(MeshIndex, paiMesh);
		
		for (uint i = 0 ; i < paiMesh->mNumFaces ; i++)
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			Indices.push_back(Face.mIndices[0] + Entries[MeshIndex].BaseVertex);
			Indices.push_back(Face.mIndices[1] + Entries[MeshIndex].BaseVertex);
			Indices.push_back(Face.mIndices[2] + Entries[MeshIndex].BaseVertex);
		}
	}
	
	void MeshBuffer::loadBones(uint MeshIndex, const aiMesh* pMesh)
	{
		for (uint i = 0 ; i < pMesh->mNumBones ; i++)
		{
			Bone * bone = nullptr;
			string BoneName(pMesh->mBones[i]->mName.data);
			if (BoneMapping.find(BoneName) == BoneMapping.end())
			{
				bone = new Bone();
				bone->BoneOffset		= ConvertAiMatrix4x42Mat4f(pMesh->mBones[i]->mOffsetMatrix);
				bone->ID				= NumBones;
				bone->Name				= BoneName;
				
				VecBoneMatrix.push_back(&bone->Transform->WorldMatrix);
				
				bone->SetAiBone(pMesh->mBones[i]);
				BoneMapping[BoneName] = bone;
				NumBones++;
			}
			else
			{
				bone = BoneMapping[BoneName];
			}
			
			for (uint j = 0 ; j < pMesh->mBones[i]->mNumWeights ; j++)
			{
				uint VertexID = Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
				float Weight  = pMesh->mBones[i]->mWeights[j].mWeight;
				bone->AddVertexAndWeight(VertexID, Weight);
				Vertices[VertexID].SetBoneIndexWeight(bone->ID, Weight);
			}
		}
	}
	
	void MeshBuffer::setVBOs()
	{
		/*glGenBuffers(1, &VertexBuffer);
		glGenBuffers(1, &IndexBuffer);*/
	}

	void MeshBuffer::BindBufferData()
	{
		//glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
		//if ( !m_bIsBufferData )
		//{
		//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
		//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Indices.size(), Indices.data(), GL_STATIC_DRAW);
		//	//m_bIsBufferData = true;
		//}
	}

	void MeshBuffer::Destory()
	{
		/*glDeleteBuffers(1, &VertexBuffer);
		glDeleteBuffers(1, &IndexBuffer);*/
		aiDetachAllLogStreams();
		Vertices.clear();
		Indices.clear();
		VecBoneMatrix.clear();
		BoneMapping.clear();
	}

	MeshEntry::MeshEntry()
	{
		NumIndices = 0;
		BaseVertex = 0;
		BaseIndex = 0;
	}

}
