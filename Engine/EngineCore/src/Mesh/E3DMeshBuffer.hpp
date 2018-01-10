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
	struct MeshEntry
	{
		MeshEntry();
		
		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};
	class MeshBuffer extends Ref
	{
	public:
		MeshBuffer(const char * filePath, const char * filename, bool& bCreateSuccess);
		void BindBufferData();
		void UnBindBuffder();
		void Destory();
	public:
		Assimp::Importer			pImporter;
		const aiScene*				pScene;
		vector<MeshEntry>			Entries;
		bool						m_bIsBufferData;		
		
	private:
		bool	initFromScene(const aiScene* pScene, const string& Filename);
		void	initMesh(uint MeshIndex, const aiMesh* paiMesh);
		void	loadBones(uint MeshIndex, const aiMesh* paiMesh);
		void	createBoneTree(aiNode * pNode);

		virtual void setVBOs();

	public:
		uint		VertexBuffer;
		uint		IndexBuffer;
		
		std::vector<Vertex>			Vertices;
		std::vector<uint>			Indices;		
		vector<mat4f*>				VecBoneMatrix;
		map<string,Bone*>			BoneMapping;
		uint						NumBones;
	};
}

#endif /* E3DVertexBuffer_hpp */
