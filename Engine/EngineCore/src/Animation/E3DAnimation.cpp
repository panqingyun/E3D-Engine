//
//  E3DAnimation.cpp
//  Created by 潘庆云 on 2017/3/27.
//

#include "E3DAnimation.hpp"
#include "../Mesh/E3DMesh.hpp"
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
		mCurrnetPlayAnimation = m_mapAnimations[name];
	}
	
	void Animation::Update(float deltaTime)
	{
		if (m_bIsPlay)
		{
			m_fhasPlayTimeLong += deltaTime;
			if (mCurrnetPlayAnimation && mCurrnetPlayAnimation->mDuration > 0.0)
			{
				if (m_bIsRepeat == true)
				{
					double tps = mCurrnetPlayAnimation->mTicksPerSecond ? mCurrnetPlayAnimation->mTicksPerSecond : 25.f;
					m_fhasPlayTimeLong = fmod(m_fhasPlayTimeLong, mCurrnetPlayAnimation->mDuration / tps);
					if(!AnimationPlayEndEvent.empty())
					{
						EventArgs * args = new EventArgs();
						args->_handled = true;
						AnimationPlayEndEvent(this, args);
						delete args;
					}
				}
				else
				{
					m_fhasPlayTimeLong = 0;
					m_bIsPlay = false;
				}
			}
			BoneTransform( m_fhasPlayTimeLong);
		}
	}
	
	bool Animation::IsPlay()
	{
		return m_bIsPlay;
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
		std::string NodeName(pNode->mName.data);

		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
		
		if (pNodeAnim)
		{
			int sPos = NodeName.find("_$");
			std::string boneName = NodeName;
			if (sPos != std::string::npos)
			{
				boneName = NodeName.substr(0, sPos);
			}
			std::map<std::string, Bone *>::iterator it = m_BoneMapping->find(boneName);
			if (it != m_BoneMapping->end())
			{
				// 插值缩放
				aiVector3D Scaling;
				calcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
			
				// 插值旋转
				aiQuaternion RotationQ;
				calcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
				Quatf q(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z);
			
				// 插值位移
				aiVector3D Translation;
				calcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);			
			
				// 骨骼变换
				Bone* pBone = it->second;
				pBone->Transform->SetLocalPosition(Translation.x, Translation.y, Translation.z);
				pBone->Transform->SetLocalRotation(q);
				pBone->Transform->SetLocalScale(Scaling.x, Scaling.y, Scaling.z);
			}
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
	
	void Animation::BoneTransform(float TimeInSeconds)
	{
		if (mCurrnetPlayAnimation == nullptr)
		{
			return;
		}
		mat4f Identity;
		Identity.identity();
		float TicksPerSecond	= (float)(mCurrnetPlayAnimation->mTicksPerSecond != 0 ? mCurrnetPlayAnimation->mTicksPerSecond : 25.0f);
		float TimeInTicks		= TimeInSeconds * TicksPerSecond;
		float AnimationTime		= fmod(TimeInTicks, (float)mCurrnetPlayAnimation->mDuration);
		
		readNodeHeirarchy(AnimationTime, m_pScene->mRootNode, mCurrnetPlayAnimation);
		
	}
	
	aiNodeAnim* Animation::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName) const
	{
		for (uint i = 0 ; i < pAnimation->mNumChannels ; i++)
		{
			aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
			
			if (std::string(pNodeAnim->mNodeName.data) == NodeName)
			{
				return pNodeAnim;
			}
		}
		
		return nullptr;
	}

}
