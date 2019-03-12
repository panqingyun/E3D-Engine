
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-17 PanQingyun. All rights reserved. *************************//

#include "E3DBone.hpp"

#ifndef __IGNORED_INCLUDE__
#include <assimp/mesh.h> 
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#endif

namespace E3DEngine
{

	Bone* Bone::GetChild(std::string name)
	{
		if (Childs.find(name) == Childs.end())
		{
			return nullptr;
		}
		return Childs[name];
	}
	
	void Bone::Move(vec3f position)
	{
		Transform->SetLocalPosition(position);
	}
	
	void Bone::Update(float deltaTime)
	{
		Transform->Update();
	}
	
	void Bone::SetAiBone(aiBone *bone)
	{
		data = bone;
		//KeyP.Pos = vec4f(-bone->mOffsetMatrix.a4, -bone->mOffsetMatrix.b4, -bone->mOffsetMatrix.c4, bone->mOffsetMatrix.d4);
	}

	void Bone::AddVertexAndWeight(int vertexID, float weight)
	{
		VerterIndex.push_back(vertexID);
		VertexWeight.push_back(weight);
	}
	
	Bone::Bone()
	{
		
	}

	Bone::Bone(Bone * other)
	{
		VerterIndex = other->VerterIndex;
		VertexWeight = other->VertexWeight;
		BoneIndex = other->BoneIndex;
		if (Transform == nullptr)
		{
			Transform = new CTransform;
		}
		for (std::map<std::string, Bone*>::iterator it = Childs.begin(); it != Childs.end(); ++it)
		{
			Childs[it->first] = new Bone(it->second);
		}
	}

	Bone::~Bone()
	{
		for (std::map<std::string, Bone*>::iterator it = Childs.begin(); it != Childs.end(); ++it)
		{
			Transform->RemoveChild(it->second->ID);
			SAFE_DELETE(it->second);
		}
		Childs.clear();
		SAFE_DELETE(Transform);
	}

	void Bone::SetMetadata(aiMetadata *data)
	{
		Metadata  = data;
	}
	
	void Bone::AddChild(Bone *pBone)
	{
		if (Childs.find(pBone->mName) != Childs.end())
		{
			return;
		}
		Childs[pBone->mName] = pBone;
		Transform->AddChild(pBone->ID, pBone->Transform);
	}
}
