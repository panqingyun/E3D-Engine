//
//  CBone.hpp
//
//  Created by 潘庆云 on 2017/3/17.
//

#ifndef FBXBone_hpp
#define FBXBone_hpp

#include "../Object/E3DGameObject.h"
#include "../Object/E3DTransform.hpp"

using namespace vvision;
namespace E3DEngine
{
	// 骨骼
	class Bone : public GameObject
	{
	public:
		Bone();
		Bone(Bone * other);
		~Bone();

	public:
		void SetMetadata(aiMetadata * data);
		void SetAiBone(aiBone * bone);
		void Move(vec3f position);
		void Transformation(mat4f matrix);
		
		virtual void Update(float deltaTime);
	public:
		mat4f		BoneOffset;
		aiBone *	data;
		int			BoneIndex;
		std::vector<uint>				VerterIndex;
		std::vector<float>				VertexWeight;
		std::map<std::string ,Bone*>    Childs;
		aiMetadata *					Metadata;
		std::map<const char* ,object>   mapMetadatas;

	public:
		Bone*		GetChild(std::string name);
		void		AddVertexAndWeight(int vertexID, float weight);
		void		AddChild(Bone *pBone);
	};
}
#endif /* FBXBone_hpp */
