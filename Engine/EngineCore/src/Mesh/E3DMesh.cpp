
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-5-24 PanQingyun. All rights reserved. *************************//

#include "E3DMesh.hpp"
#include "E3DMeshRender.h"
#include "../Scene/E3DSceneManager.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Config/TableRegister.h"
#include "../Source/Application.h"
#include "../Source/FilePath.h"
#include "../Source/E3DDebug.h"

namespace E3DEngine
{
#ifndef __EDITOR__
	mat4f ConvertAiMatrix4x42Mat4f(aiMatrix4x4 aiMat)
	{
		mat4f mat4;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mat4.at(i, j) = aiMat[i][j];
			}
		}
		return mat4;
	}
#endif

	Mesh *Mesh::Create(string path, int configID)
	{
		Mesh * mesh = new Mesh(path, configID);
		return mesh;
	}

	Mesh::Mesh(std::string filePath, int cfgID)
	{
		NumBones = 0;
		m_bIsBufferData = false;
		m_bIsSkinMesh = false;
		mAnimation = nullptr;
		CreateBehaviour();
		TableManager *tbMgr = TableRegister::GetTableManager(filePath.c_str());
		if (tbMgr == nullptr)
		{
			Debug::Log(ell_Error, "Error parsing '%s': 'read table wrong'", filePath.c_str());
			return;
		}
		MeshConfig * modelCfg = tbMgr->Select<MeshConfig>(cfgID);
		if (modelCfg == nullptr)
		{
			Debug::Log(ell_Error, "Error parsing '%s': select table wrong", filePath.c_str());
			return;
		}
		std::string   fbxPath = GetFolder(filePath) + "/" + modelCfg->ModelFilePath;

		bool Ret	= false;
		pScene		= pImporter.ReadFile(fbxPath, ASSIMP_LOAD_FLAGS);
		if (pScene)
		{
			Ret = initFromScene(pScene, fbxPath);
		}
		else
		{
			Debug::Log(ell_Error, "Error parsing '%s': '%s'\n", filePath.c_str(), pImporter.GetErrorString());
			return;
		}

		if (m_bIsSkinMesh)
		{
			// 构建骨骼树
			BoneTree = BoneMapping;
			aiNode *rootNode = pScene->mRootNode;
			for (int i = 0; i < rootNode->mNumChildren; i++)
			{
				createBoneTree(rootNode->mChildren[i]);
			}
			for (auto &bone : BoneTree)
			{
				Transform->AddChild(bone.second->ID, bone.second->Transform);
			}
			createAnimation();
		}

		std::string materialPath = modelCfg->Materials;
		std::vector<std::string> materialCfg = StringBuilder::Split(materialPath, ":");
		if (materialCfg.size() != 2)
		{
			Debug::Log(ell_Error, "Error parsing '%s': split config wrong", filePath.c_str());
			return;
		}
		std::string folder = GetFolder(filePath);
		Material * material = GetRenderSystem()->GetMaterialManager()->CreateMaterial(folder + "/" + materialCfg[0], Convert::ToInt(materialCfg[1]));
		SetMaterial(material);
		SAFE_DELETE(tbMgr);
	}

	void Mesh::SetMaterial(Material *material)
	{
		m_pRenderer = GetRenderSystem()->GetRenderManager()->GetRenderer(material->ID, MESH);
		m_pRenderer->SetMaterial(material);
//		static_cast<MeshRender*>(m_pRenderer)->SetAiScene(pScene);
		static_cast<MeshRender*>(m_pRenderer)->SetBoneVector(VecBoneMatrix);
		if (m_pRenderer->RenderIndex != eRI_None && m_pRenderer->RenderIndex != RenderIndex)
		{
			// TODO 同样的材质，不同渲染层级，需要重新创建一个Renderer
			//m_pRenderer = GetRenderSystem()->GetRenderManager()->CreateVertexRender(material->mMaterialID);
		}
		m_pRenderer->IsStaticDraw = false;
		m_pRenderer->SetTransform(Transform);
		GameObject::TransferRender();
		IsActive = false;
		SetActive(true);
	}

	void Mesh::SetActive(bool isActive)
	{
		if (isActive == IsActive)
		{
			return;
		}
		GameObject::SetActive(isActive);
		Renderer* mRenderer = static_cast<Renderer*>(m_pRenderer);
		if (isActive)
		{
			mRenderer->FillBegin(ID);
			for (int i = 0; i < m_vecVertex.size(); i++)
			{
				mRenderer->FillVertex(m_vecVertex[i]);
			}

			for (int i = 0; i < m_vecIndex.size(); i++)
			{
				mRenderer->FillIndex(m_vecIndex[i]);
			}
			mRenderer->FillEnd(ID, m_vecVertex.size(), m_vecIndex.size());
		}
		else
		{
			mRenderer->RemoveInRenderer(ID);
		}
		m_pRenderer->TransformChange();
	}

	bool Mesh::initFromScene(const aiScene *pScene, const string &Filename)
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
	
	void Mesh::createBoneTree(aiNode * pNode)
	{
		std::string boneName = pNode->mName.data;
		int sPos = boneName.find("_$");
		if (sPos != std::string::npos)
		{
			boneName = boneName.substr(0, sPos);
		}
		if (BoneMapping.find(boneName) == BoneMapping.end())
		{
			for (int i = 0; i < pNode->mNumChildren; ++i)
			{
				createBoneTree(pNode->mChildren[i]);
			}
			return;
		}
		// 根据Node结构创建骨骼树
		Bone *pBone = BoneMapping[boneName];
		//transform->AddChild(pBone->Name, pBone->Transform);
		pBone->SetMetadata(pNode->mMetaData);
		
		for (int i = 0; i < pNode->mNumChildren; ++i)
		{
			boneName = pNode->mChildren[i]->mName.data;
			sPos = boneName.find("_$");
			if (sPos != std::string::npos)
			{
				boneName = boneName.substr(0, sPos);
			}
			if (BoneTree.find(boneName) != BoneTree.end())
			{// 找到一个节点和Bone重名 这个Bone在子节点中，所以是子骨骼
				pBone->AddChild(BoneTree[boneName]);
				BoneTree.erase(boneName);
			}
			createBoneTree(pNode->mChildren[i]);
		}
		
	}
	
	void Mesh::createAnimation()
	{
		if (pScene->HasAnimations())
		{
			mAnimation = new Animation();
			mAnimation->SetBones(&BoneMapping);
			mAnimation->SetScene(pScene);
			mAnimation->LoadAnimations();
			mAnimation->Play("Take 001", true);
		}
	}

	void Mesh::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Mesh);
		setBehaviourDefaultValue();
	}

	void Mesh::initMesh(uint MeshIndex, const aiMesh* paiMesh)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		const aiColor4D Default4D(1.0f,1.0f, 1.0f, 1.0f);
		for (uint i = 0 ; i < paiMesh->mNumVertices ; i++)
		{
			const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord1 = paiMesh->HasTextureCoords(0)			? &(paiMesh->mTextureCoords[0][i])	: &Zero3D;
			const aiVector3D* pTexCoord2 = paiMesh->HasTextureCoords(1)			? &(paiMesh->mTextureCoords[1][i])	: &Zero3D;
			const aiVector3D* pTexCoord3 = paiMesh->HasTextureCoords(2)			? &(paiMesh->mTextureCoords[2][i])	: &Zero3D;
			const aiVector3D* pTexCoord4 = paiMesh->HasTextureCoords(3)			? &(paiMesh->mTextureCoords[3][i])	: &Zero3D;
			const aiVector3D* pTexCoord5 = paiMesh->HasTextureCoords(4)			? &(paiMesh->mTextureCoords[4][i])	: &Zero3D;
			const aiVector3D* pTexCoord6 = paiMesh->HasTextureCoords(5)			? &(paiMesh->mTextureCoords[5][i])	: &Zero3D;
			const aiVector3D* pTexCoord7 = paiMesh->HasTextureCoords(6)			? &(paiMesh->mTextureCoords[6][i])	: &Zero3D;
			const aiVector3D* pTexCoord8 = paiMesh->HasTextureCoords(7)			? &(paiMesh->mTextureCoords[7][i])	: &Zero3D;
			const aiColor4D * pColor	 = paiMesh->HasVertexColors(0)			? &(paiMesh->mColors[0][i])			: &Default4D;
			const aiVector3D* pTangent	 = paiMesh->HasTangentsAndBitangents()	? &(paiMesh->mTangents[i])			: &Zero3D;
			
			Vertex vertex;
			vertex.SetPosition(pPos->x, pPos->y, pPos->z);
			vertex.SettextureCoord1(pTexCoord1->x, pTexCoord1->y);
			vertex.SettextureCoord2(pTexCoord2->x, pTexCoord2->y);
			vertex.SettextureCoord3(pTexCoord3->x, pTexCoord3->y);
			vertex.SettextureCoord4(pTexCoord4->x, pTexCoord4->y);
			vertex.SettextureCoord5(pTexCoord5->x, pTexCoord5->y);
			vertex.SettextureCoord6(pTexCoord6->x, pTexCoord6->y);
			vertex.SettextureCoord7(pTexCoord7->x, pTexCoord7->y);
			vertex.SettextureCoord8(pTexCoord8->x, pTexCoord8->y);
			vertex.SetNormal(pNormal->x, pNormal->y, pNormal->z);
			vertex.SetColor(pColor->r, pColor->g, pColor->b, pColor->a);
			vertex.SetTangent(pTangent->x, pTangent->y, pTangent->z);
			m_vecVertex.push_back(vertex);
		}
		
		loadBones(MeshIndex, paiMesh);
		
		for (uint i = 0 ; i < paiMesh->mNumFaces ; i++)
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			m_vecIndex.push_back(Face.mIndices[0] + Entries[MeshIndex].BaseVertex);
			m_vecIndex.push_back(Face.mIndices[1] + Entries[MeshIndex].BaseVertex);
			m_vecIndex.push_back(Face.mIndices[2] + Entries[MeshIndex].BaseVertex);
		}
	}
	
	void Mesh::loadBones(uint MeshIndex, const aiMesh* pMesh)
	{
		if (!pMesh->HasBones())
		{
			return;
		}
		m_bIsSkinMesh = true;
		for (uint i = 0 ; i < pMesh->mNumBones ; i++)
		{
			Bone * bone = nullptr;
			string BoneName(pMesh->mBones[i]->mName.data);
			if (BoneMapping.find(BoneName) == BoneMapping.end())
			{
				bone = new Bone();
				bone->BoneOffset		= ConvertAiMatrix4x42Mat4f(pMesh->mBones[i]->mOffsetMatrix);
				bone->BoneIndex			= NumBones;
				bone->mName				= BoneName;
				
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
				m_vecVertex[VertexID].SetBoneIndexWeight(bone->BoneIndex, Weight);
			}
		}
	}

	void Mesh::Destory()
	{
		aiDetachAllLogStreams();
		m_vecVertex.clear();
		m_vecIndex.clear();
		VecBoneMatrix.clear();
		BoneMapping.clear();
	}


	void Mesh::Update(float deltaTime)
	{
		if (mAnimation != nullptr)
		{
			mAnimation->Update(deltaTime);
		}
		for (auto & bone : BoneTree)
		{
			bone.second->Update(deltaTime);
		}
		GameObject::Update(deltaTime);
	}

	MeshEntity::MeshEntity()
	{
		NumIndices = 0;
		BaseVertex = 0;
		BaseIndex = 0;
	}

}
