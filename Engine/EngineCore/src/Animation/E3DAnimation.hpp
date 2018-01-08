//
//  E3DAnimation.hpp
//  Created by 潘庆云 on 2017/3/27.
//

#ifndef FBXSceneAnimator_hpp
#define FBXSceneAnimator_hpp

#include "../Object/E3DComponent.hpp"
#include "../Animation/E3DAnimationClip.hpp"
#include "../Source/E3DDelegate.h"
#include "../Mesh/E3DBone.hpp"

namespace E3DEngine
{
	class Animation : public Component
	{
	public:
		Animation();
		
	public:
		bool	HasLoaded;
		event EventDelegates AnimationPlayEndEvent;
		
		std::map<std::string, Bone*> *	m_BoneMapping;
	protected:
		const aiScene *			m_pScene;
		mat4f					m_GlobalInverseTransform;
		float					m_fhasPlayTimeLong;
		bool					m_bIsPlay;
		bool					m_bIsRepeat;
		std::string				m_strCurrentPlayAnimationName;

		std::map<std::string, AnimationClip*>	m_mapAnimationClip;
		std::map<std::string ,aiAnimation*>		m_mapAnimations;
		
	public:
		virtual void Play(std::string name = "", bool isRepeat = false);
		
		virtual void SetScene(const aiScene * pScene);
		virtual void LoadAnimations();
		virtual void SetBones(std::map<std::string, Bone *> *p_MapBones);
	public:
		virtual void Start() override
		{
		}
		virtual void Update(float deltaTime) override;
		virtual void Destory() override
		{
		}
		
	public:
		bool	IsPlay()
		{
			return m_bIsPlay;
		}
	protected:
		void			BoneTransform(std::string name, float TimeInSeconds);
		aiNodeAnim  *	FindNodeAnim(const aiAnimation* pAnimation, const string NodeName) const;
		void			TransformBone(const char * name, mat4f trans);
		aiAnimation *	FindAnimationInScene(const char * aniName) const;
		
	protected:
		void	calcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void	calcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void	calcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		uint	findScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
		uint	findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
		uint	findPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
		void	readNodeHeirarchy(float AnimationTime, const aiNode* pNode, aiAnimation *pAnimation);
	};
}

#endif /* FBXSceneAnimator_hpp */
