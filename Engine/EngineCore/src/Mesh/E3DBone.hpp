
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-17 PanQingyun. All rights reserved. *************************//

#ifndef FBXBone_hpp
#define FBXBone_hpp

#include "../Object/E3DGameObject.h"
#include "../Object/E3DTransform.hpp"

using namespace vvision;

class aiBone;
class aiMetadata;
namespace E3DEngine
{
	// 骨骼
	class E3D_EXPORT_DLL Bone : public GameObject
	{
	public:
		Bone();
		Bone(Bone * other);
		~Bone();

	public:

#ifndef __IGNORED_INCLUDE__
		void SetMetadata(aiMetadata * data);
		void SetAiBone(aiBone * bone);
#endif
		void Move(vec3f position);
		void Transformation(mat4f matrix);
		
		virtual void Update(float deltaTime);
	public:
		mat4f		BoneOffset;

#ifndef __IGNORED_INCLUDE__
		aiBone *	data;
		aiMetadata *					Metadata;
#endif
		int			BoneIndex;
		std::vector<uint>				VerterIndex;
		std::vector<float>				VertexWeight;
		std::map<std::string ,Bone*>    Childs;
		std::map<const char* ,object>   mapMetadatas;

	public:
		Bone*		GetChild(std::string name);
		void		AddVertexAndWeight(int vertexID, float weight);
		void		AddChild(Bone *pBone);
	};
}
#endif /* FBXBone_hpp */
