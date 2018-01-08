//
//  E3DAnimation.cpp
//  Created by 潘庆云 on 2017/3/27.
//

#include "E3DAnimation.hpp"
namespace E3DEngine
{
	void Animation::SetScene(const aiScene *pScene)
	{
		m_pScene = pScene;
		if (!pScene)
		{
			return;
		}
		m_GlobalInverseTransform = ConvertAiMatrix4x42Mat4f(m_pScene->mRootNode->mTransformation);
		m_GlobalInverseTransform.inverse();
	}
	
	void Animation::SetBones(std::map<std::string, Bone *> *p_MapBones)
	{
		m_BoneMapping = p_MapBones;
	}
	
	Animation::Animation()
	{
		HasLoaded = false;
		m_BoneMapping = nullptr;
		m_pScene = nullptr;
		m_fhasPlayTimeLong = 0;
		m_bIsPlay = false;
		m_bIsRepeat = false;

		m_strCurrentPlayAnimationName = "";
	}

	void Animation::Play(std::string name, bool isRepeat)
	{
		m_bIsRepeat = isRepeat;
		m_bIsPlay	= true;
		m_strCurrentPlayAnimationName = name;
	}
	
	void Animation::Update(float deltaTime)
	{
		if (m_bIsPlay)
		{
			m_fhasPlayTimeLong += deltaTime;
			BoneTransform(m_strCurrentPlayAnimationName, m_fhasPlayTimeLong);
			if (m_fhasPlayTimeLong >= m_mapAnimations[m_strCurrentPlayAnimationName]->mDuration)
			{ // 播放到结尾了
				if (m_bIsRepeat == true)
				{
					m_fhasPlayTimeLong = 0;
					if(!AnimationPlayEndEvent.empty())
					{
						EventArgs * args = new EventArgs();
						args->_handled = true;
						AnimationPlayEndEvent(this, args);
					}
				}
				else
				{
					m_fhasPlayTimeLong = 0;
					m_bIsPlay = false;
				}
			}
		}
	}
	
	void Animation::LoadAnimations()
	{
		if (m_pScene == nullptr)
		{
			return;
		}
		for (int i = 0; i < m_pScene->mNumAnimations; i++)
		{
			m_mapAnimations[m_pScene->mAnimations[i]->mName.data] = m_pScene->mAnimations[i];
		}
	}
	
	uint Animation::findPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		for (uint i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
			{
				return i;
			}
		}
		
		return 0;
	}
	
	
	uint Animation::findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumRotationKeys > 0);
		
		for (uint i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
			{
				return i;
			}
		}
		
		return 0;
	}
	
	
	uint Animation::findScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumScalingKeys > 0);
		
		for (uint i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
			{
				return i;
			}
		}
		
		return 0;
	}
	
	
	void Animation::calcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumPositionKeys == 1)
		{
			Out = pNodeAnim->mPositionKeys[0].mValue;
			return;
		}
		
		uint PositionIndex = findPosition(AnimationTime, pNodeAnim);
		uint NextPositionIndex = (PositionIndex + 1);
		assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
		float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
		const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}
	
	
	void Animation::calcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		// we need at least two values to interpolate...
		if (pNodeAnim->mNumRotationKeys == 1)
		{
			Out = pNodeAnim->mRotationKeys[0].mValue;
			return;
		}
		
		uint RotationIndex = findRotation(AnimationTime, pNodeAnim);
		uint NextRotationIndex = (RotationIndex + 1);
		assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
		float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
		const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
		aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
		Out = Out.Normalize();
	}
	
	
	void Animation::calcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumScalingKeys == 1)
		{
			Out = pNodeAnim->mScalingKeys[0].mValue;
			return;
		}
		
		uint ScalingIndex		= findScaling(AnimationTime, pNodeAnim);
		uint NextScalingIndex	= (ScalingIndex + 1);
		assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
		float DeltaTime			= (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
		float Factor			= (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
		const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
		aiVector3D Delta		= End - Start;
		Out						= Start + Factor * Delta;
	}
	
	
	void Animation::readNodeHeirarchy(float AnimationTime,
									   const aiNode* pNode,
									   aiAnimation *pAnimation)
	{
		if (pAnimation == nullptr)
		{
			return;
		}
		string NodeName(pNode->mName.data);
		mat4f NodeTransformation;
		NodeTransformation.identity();
		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
		
		if (pNodeAnim)
		{
			// 插值缩放
			aiVector3D Scaling;
			calcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
			mat4f ScalingM;
			ScalingM.setTranslation(vec3f(Scaling.x, Scaling.y, Scaling.z));
			
			// 插值旋转
			aiQuaternion RotationQ;
			calcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
			Quatf q(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z);
			mat4f RotationM = q.transform();
			
			// 插值位移
			aiVector3D Translation;
			calcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
			mat4f TranslationM;
			TranslationM.setTranslation(vec3f(Translation.x, Translation.y, Translation.z));
			
			// 矩阵乘积
			NodeTransformation = TranslationM * RotationM * ScalingM;
		}
		
		std::map<std::string , Bone *>::iterator it = m_BoneMapping->find(NodeName);
		if (it != m_BoneMapping->end())
		{
			// 骨骼变换
			Bone* pBone = it->second;
			pBone->Transform->WorldMatrix = m_GlobalInverseTransform * NodeTransformation;
		}
		
		for (uint i = 0 ; i < pNode->mNumChildren ; i++)
		{
			readNodeHeirarchy(AnimationTime, pNode->mChildren[i], pAnimation);
		}
	}
	
	aiAnimation * Animation::FindAnimationInScene(const char *aniName) const
	{
		aiAnimation * ani = nullptr;
		for (int i = 0; i < m_pScene->mNumAnimations; i++)
		{
			if(strcmp( m_pScene->mAnimations[i]->mName.data, aniName) == 0)
			{
				ani = m_pScene->mAnimations[i];
				break;
			}
		}
		
		return ani;
	}
	
	void Animation::BoneTransform(std::string name, float TimeInSeconds)
	{
		aiAnimation * animation = nullptr;
		if (m_mapAnimations.find(name) == m_mapAnimations.end())
		{
			animation = m_pScene->mAnimations[0];
		}
		else
		{
			animation = m_mapAnimations[name];
		}
		if (animation == nullptr)
		{
			return;
		}
		mat4f Identity;
		Identity.identity();
		float TicksPerSecond	= (float)(animation->mTicksPerSecond != 0 ? animation->mTicksPerSecond : 25.0f);
		float TimeInTicks		= TimeInSeconds * TicksPerSecond;
		float AnimationTime		= fmod(TimeInTicks, (float)animation->mDuration);
		
		readNodeHeirarchy(AnimationTime, m_pScene->mRootNode, animation);
		
	}
	
	aiNodeAnim* Animation::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName) const
	{
		for (uint i = 0 ; i < pAnimation->mNumChannels ; i++)
		{
			aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
			
			if (string(pNodeAnim->mNodeName.data) == NodeName)
			{
				return pNodeAnim;
			}
		}
		
		return nullptr;
	}

}
