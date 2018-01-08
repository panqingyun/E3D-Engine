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
	struct KeyPoint
	{
		int		KeyIndex;//自身的关键点序号，匹配二维人脸
		vec4f   Pos;
	};
	
	// 骨骼
	class Bone extends GameObject
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
		int			ID;
		std::string Name;
		mat4f		BoneOffset;
		aiBone *	data;
		
		std::vector<uint>				VerterIndex;
		std::vector<float>				VertexWeight;
		std::map<std::string ,Bone*>    Childs;
		aiMetadata *					Metadata;
		std::map<const char* ,object>   mapMetadatas;
	public:
		//是否是关键点
		int			BoneIndex;
		bool		IsImpoint;
		KeyPoint	KeyP;
		float		tranScaleX;
		float		tranScaleY;
	public:
		Bone*		GetChild(std::string name);
		void		AddVertexAndWeight(int vertexID, float weight);
		void		AddChild(Bone *pBone);
	};
}
#endif /* FBXBone_hpp */
