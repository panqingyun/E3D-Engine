
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-5-24 PanQingyun. All rights reserved. *************************//

#ifndef E3DVertexBuffer_hpp
#define E3DVertexBuffer_hpp

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Component/E3DComponent.hpp"
#include "../Animation/E3DAnimation.hpp"

#ifndef __IGNORED_INCLUDE__
#include <assimp/mesh.h> 
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#endif
#include "../Source/ClassFactory.h"
#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
#ifndef __IGNORED_INCLUDE__
	mat4f ConvertAiMatrix4x42Mat4f(aiMatrix4x4 mat);
#endif
	struct MeshEntity
	{
		MeshEntity();
		
		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};
	class E3D_EXPORT_DLL Mesh : public Component
	{
		DECLARE_CLASS(Mesh)
	public:
		Mesh();
		virtual void Awake() override;
		virtual void Destory() override;
		virtual void Update(float deltaTime) override;
	public:
#ifndef __IGNORED_INCLUDE__
		Assimp::Importer			pImporter;
		const aiScene*				pScene;
		vector<MeshEntity>			Entries;
		bool						m_bIsBufferData;		
		
	private:
		bool	initFromScene(const aiScene* pScene, const string& Filename);
		void	initMesh(uint MeshIndex, const aiMesh* paiMesh, std::vector<Vertex> &vecVertex, std::vector<UINT> &vecIndex);
		void	loadBones(uint MeshIndex, const aiMesh* paiMesh);
		void	createBoneTree(aiNode * pNode);
		void	createAnimation();
	public:
		static void SetFilePath(void *cp, object value);
		static object GetFilePath(void *cp);
		virtual void registProperty() override
		{
			SAVE_PROPERTY(FilePath, FT_STRING)
		}
	protected:
		bool m_bIsSkinMesh;
		std::string FilePath;
#endif
	public:	
		vector<mat4f*>				VecBoneMatrix;
		map<string, Bone*>			BoneMapping;
		map<string, Bone*>			BoneTree;
		uint						NumBones;
		Animation *					mAnimation;
	};
}

#endif /* E3DVertexBuffer_hpp */
