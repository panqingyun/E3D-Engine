
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-5-24 PanQingyun. All rights reserved. *************************//

#ifndef E3DVertexBuffer_hpp
#define E3DVertexBuffer_hpp

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DComponent.hpp"
#include "../Animation/E3DAnimation.hpp"

using namespace std;

namespace E3DEngine
{
	struct MeshEntity
	{
		MeshEntity();
		
		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};
	class Mesh : public GameObject
	{
	public:
		static Mesh* Create(string path, int configID);
		Mesh(std::string filePath, int cfgID);
		virtual void SetMaterial(Material *material);
		virtual void SetActive(bool isActive) override;
		void Destory();
		virtual void Update(float deltaTime) override;
	public:
		Assimp::Importer			pImporter;
		const aiScene*				pScene;
		vector<MeshEntity>			Entries;
		bool						m_bIsBufferData;		
		
	private:
		bool	initFromScene(const aiScene* pScene, const string& Filename);
		void	initMesh(uint MeshIndex, const aiMesh* paiMesh);
		void	loadBones(uint MeshIndex, const aiMesh* paiMesh);
		void	createBoneTree(aiNode * pNode);
		void	createAnimation();

	protected:
		virtual void CreateBehaviour() override;

		bool m_bIsSkinMesh;

	public:	
		vector<mat4f*>				VecBoneMatrix;
		map<string, Bone*>			BoneMapping;
		map<string, Bone*>			BoneTree;
		uint						NumBones;
		Animation *					mAnimation;
	};
}

#endif /* E3DVertexBuffer_hpp */
