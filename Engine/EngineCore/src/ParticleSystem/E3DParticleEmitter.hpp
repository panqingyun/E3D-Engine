//
//  ParticleEmitter.hpp
//  Obj
//  粒子发射器
//  Created by 潘庆云 on 2017/1/17.
//  Copyright © 2017年 潘庆云. All rights reserved.
//

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp

#include <stdio.h>
#include "../Config/TableBase.h"
#include "../Source/Interface.h"
#include "../Source/E3DDelegate.h"

typedef enum // 定义发射器枚举
{
	eParticleEmitterNone = 0,
	eParticleEmitterArea = 1, // 区域发射器
	eParticleEmitterBall = 2, // 球形发射器
	eParticleEmitterPoint = 3, // 点发射器
} eParticleEmitter;

namespace E3DEngine
{
    
    class Particle;
    class ParticleGroup;
    class TableBase;
    // ----------------------------------------------------------------------------------------
    /* 粒子发射器基类，决定粒子的初始属性
     @remarks
     发射器的抽象类，定义了大部分发射器的共有属性和抽象接口。不同的
     发射器类提供不同的实现。
     */
    // ----------------------------------------------------------------------------------------
    class ParticleEmitter : public Ref
    {
        DECLARE_CLASS(ParticleEmitter);
    public:
        ParticleEmitter()
        {
            bIsFirstCreate = true;
            m_fBronInterval = 0.0;
            m_fLiveRandom = 0.0;
            m_fBronDeltaTime = 0.0f;
        }
        
        void CreateParticleEx();        
        bool CheckLiveTime(float time);
        
        virtual void Initilize(ParticleGroup *p);
        virtual void Update(float deltaTime);
        virtual ~ParticleEmitter();
        virtual void ParseConfig(TableBase *pConfigTable) { m_pConfigTable = pConfigTable; }
        // 初始化提供粒子对象的属性
        virtual void InitParticle( Particle *p ){ }
        virtual void SetEmitterPosition(vec3f position);
        virtual vec3f GetEmitterPosition()  { return m_EmitterPosition; }
        virtual void SetEnable(bool isEnable) { m_bEnable = isEnable; }
        virtual void InitCompleted();
		// 在发射器指定的范围内产生粒子位置
	protected:
        virtual void _GenEmissionPosition( ) { }
        virtual void _CreateParticle();
    public:
        // 粒子团在本地空间中的位置
        vec3f			m_vPosition;
        // 粒子团在本地空间中的方向
        vec3f			m_vDirection;
        // 是否启用
        bool			m_bEnable;
        // 归属哪个粒子团
        ParticleGroup *	m_pParticleGroup;

        float		m_fBlankTime;		//间歇时间
        float		m_fHasBlankTime;	// 已经间歇时长
        float		m_fBronInterval;  //粒子出生间隔时间
        float		m_fBronDeltaTime;
        bool		m_bIsBlank;
        
        UINT		m_CurrentParticleNumer; // 本次已经发射了多少粒子
        UINT		m_TotalParticleNumber; // 一共需要发射的粒子数
		UINT		m_MaxParticleNumber;
        UINT		m_CurrentCreateNumber;  // 本次生成的粒子数
        float		m_LiveTime;
        float		m_fLiveRandom;
        Vector2		m_v2ParticleSize;
        vec2f		m_SizeScaleRange;
        vec2f		m_AlphaRange;
        float		m_fParticleColor;
        int			m_nEffectID;
        bool		m_bIsLoop;
        event		EventDelegates StopEmitterHandle;
        bool		m_bIsBillboard;
        vec3f		m_EmitterPosition;
        bool		bIsFirstCreate;
        bool		m_bLockMove;
		uint		particleGroupID;

		eParticleEmitter		m_Type;
		E3DEngine::TableBase *	m_pConfigTable;
    };
    
    class PointEmitter : public ParticleEmitter
    {
        DECLARE_CLASS(PointEmitter);
    public:
        PointEmitter();
        virtual void Initilize(ParticleGroup *p) override;
        virtual void _GenEmissionPosition() override;
        virtual ~PointEmitter() override = default;
        virtual void ParseConfig(TableBase *pConfigTable) override;
    private:
        vec3f m_vPointPosition;
    };
    
    // 区域发射器
    class AreaEmitter : public ParticleEmitter
    {
        DECLARE_CLASS(AreaEmitter)
    public:
        AreaEmitter();
        virtual void Initilize(ParticleGroup *p) override;
        virtual void _GenEmissionPosition() override;
        virtual ~AreaEmitter() override = default;
        virtual void ParseConfig(TableBase *pConfigTable) override;
    private:
        vec3i	m_vAreaRange;
        int		areaXPos;
        int		areaYPos;
        int		areaZPos;
    };
    
    //球面发射器
    class BallEmitter : public ParticleEmitter
    {
        DECLARE_CLASS(BallEmitter)
    public:
        BallEmitter();
        virtual void Initilize(ParticleGroup *p) override;
        virtual ~BallEmitter() override = default;
        virtual void _GenEmissionPosition() override;
        virtual void ParseConfig(E3DEngine::TableBase *pConfigTable) override;
    private:
        float Radius;
        
    };
    
    // 环发射器
    
    // 空心椭圆发射器
    
    // 椭圆发射器
    
    // 盒子发射器
    
    // 线形发射器
}
#endif
