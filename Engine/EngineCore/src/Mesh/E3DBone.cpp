//
//  FBXBone.cpp
//
//  Created by 潘庆云 on 2017/3/17.
//

#include "E3DBone.hpp"

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
		Transform->SetPosition(position);
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
		if (Childs.find(pBone->Name) != Childs.end())
		{
			return;
		}
		Childs[pBone->Name] = pBone;
		Transform->AddChild(pBone->ID, pBone->Transform);
	}
}
