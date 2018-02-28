//
//  E3DVertexBuffer.hpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#ifndef E3DVertexBuffer_hpp
#define E3DVertexBuffer_hpp

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DComponent.hpp"

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
		Mesh(std::string filePath, int cfgID);
		virtual void SetMaterial(Material *material) override;
		virtual void SetActive(bool isActive) override;
		void Destory();
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

	protected:
		virtual void CreateBehaviour() override;

	public:	
		vector<mat4f*>				VecBoneMatrix;
		map<string,Bone*>			BoneMapping;
		uint						NumBones;
	};
}

#endif /* E3DVertexBuffer_hpp */
