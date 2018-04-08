//
//  ParticleEffector.hpp
//
//  Created by 潘庆云 on 2017/1/17.
//

#ifndef ParticleEffector_hpp
#define ParticleEffector_hpp

#include <stdio.h>
#include "../Config/TableBase.h"
#include "../Source/Interface.h"

typedef enum // 定义效果器枚举
{
	eParticleAffectorNone = 0,
	eParticleAffectorLinnerForce = 1, //线性外力效果器
	eParticleAffectorRandomForce = 2, //线性外力效果器
	eParticleAffectorMoveToFiringPointForce = 3,
	eParticleAffectorRotateForce = 4, //旋转外力效果器
} eParticleAffector;

namespace E3DEngine
{
	// ---------------------------------------------------------------------------------------
	// 效果器基类
	// ----------------------------------------------------------------------------------------
	/* 粒子效果器，动态改变粒子的属性
	*/
	class ParticleGroup;
	class Particle;

	class ParticleAffector : public Ref
	{
		DECLARE_CLASS(ParticleAffector);
	public:
		ParticleAffector()
		{
			m_pParticleGroup = nullptr;
		}
		virtual void Initilize(ParticleGroup *pParent);
		virtual ~ParticleAffector();
		virtual void Update(float deltaTime);
		virtual void InitParticle(Particle *p) { }              // 新粒子发射时调用此函数初始化粒子属性
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle){ } // 每帧调用此函数影响粒子属性（需要子类具体实现）

		virtual void Clone(ParticleAffector *pe) { }
		virtual void ParseConfig(E3DEngine::TableBase * pConfig)
		{
		}
		virtual void RotateParticleByMat(mat4f rotateMatrix);
	public:
		ParticleGroup *m_pParticleGroup;
		eParticleAffector m_Type;
		mat4f m_matrixRotate;
		uint	particleGroupID;
	};

	/* 随机外力效果器
		随机方向 即四面八方
	*/

	class RandomForceAffector extends ParticleAffector
	{
		DECLARE_CLASS(RandomForceAffector)
	public:
		RandomForceAffector();
		virtual void InitParticle(Particle *p) override {}
		virtual void Clone(ParticleAffector *pe) override {}
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
		virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
	private:
		int m_ID;
		vec3f m_vForceDirection;
		vec3f m_vConfigDirection;
		bool  m_bRotateByDir;
        bool  m_bRotateByOrbit;
		float m_fSpeed;
		float m_RandomSpeed[2];
		float m_xRandomRange[2];
		float m_yRandomRange[2];
		float m_zRandomRange[2];
		float m_fStartTime;
		float m_fEndTime;
	};

	/* 线性外力效果器
		匀速直线运动

	*/

	class LinerForceAffector : public ParticleAffector
	{
		DECLARE_CLASS(LinerForceAffector);
	public:
		LinerForceAffector();
		virtual void InitParticle(Particle *p) override {}
		virtual void Clone(ParticleAffector *pe) override {}
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
		virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
	private:
		vec3f m_vForceDirection;
		float m_fForceRandomRange;
		float m_fSpeed;
	};
    
    /* 向心力影响器
      向中心运动
     */
    
    class MoveToFiringPointForceAffector : public ParticleAffector
    {
        DECLARE_CLASS(MoveToFiringPointForceAffector);
    public:
        MoveToFiringPointForceAffector();
        virtual void InitParticle(Particle *p) override {}
        virtual void Clone(ParticleAffector *pe) override {}
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
        virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
    private:
        //vec3f m_TargetPosition;
        float m_fForceRandomRange;
        float m_fSpeed;
        float m_fRotateWithEmitterAngle;
    };
    
	/* 旋转外力影响器
		
	*/
    class RotateForceAffector : public ParticleAffector
    {
        DECLARE_CLASS(RotateForceAffector);
    public:
        RotateForceAffector();
        virtual void InitParticle(Particle *p) override;
        virtual void Clone(ParticleAffector *pe) override;
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
        virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
    private:
        //vec3f m_TargetPosition;
        float m_fForceRandomRange;
        float m_fSpeed;
        vec3f m_vAxis;
    };

	// 缩放影响器
	class ScaleAffector : public ParticleAffector
	{
		DECLARE_CLASS(ScaleAffector);
	public:
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
		virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
	private:
		float m_fStartScale;  //
		float m_fEndScale;  //
		float m_fStartTime;
		float m_fEndTime;
	};
    
    

	// 颜色渐变影响器
	class LinnerColorAffector : public ParticleAffector
	{
		DECLARE_CLASS(LinnerColorAffector);
	public:
		LinnerColorAffector();

		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
		virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
	private:
		long genColor(float * color);
	private:
		vec4f m_nStartColor; //
		vec4f m_nEndColor; //
		float m_fStartTime; //
		float m_fEndTime;

		float rChange;
		float gChange;
		float bChange;
		float aChange;

		int m_UseSrcAlpha;
	};

	// 粒子团整体旋转
	class GroupRotationAffector  : public ParticleAffector
	{
		DECLARE_CLASS(GroupRotationAffector);
	public:
		GroupRotationAffector();

		virtual void InitParticle(Particle *p) override {}
		virtual void Clone(ParticleAffector *pe) override {}
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
		virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
	private:
		long genColor(float * color);
	private:
		float m_fRotateSpeed; // 旋转量
		vec3f m_RotateAxis; // 旋转轴
	};

	// 粒子自旋
	class RotateAffector : public ParticleAffector
	{
		DECLARE_CLASS(RotateAffector);
	public:
		virtual void AffectParticle(float fElapsedTime, share_pointer<Particle> particle) override;
		virtual void ParseConfig(E3DEngine::TableBase * pConfig) override;
	private:
        bool  m_bStartRandom;
		float m_fAngle;  // 旋转角速度 角度值
		float m_fSpeed;
		vec2f m_vSpeedRange;
		vec3f m_vAxis;
	};

}
#endif /* ParticleAffector_hpp */
