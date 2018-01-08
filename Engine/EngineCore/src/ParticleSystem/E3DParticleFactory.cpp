//
//  ParticleSystemFactory.cpp
//  ParticleSystem
//
//  Created by 潘庆云 on 2017/1/18.
//

#include "E3DParticleFactory.hpp"
#include "E3DParticle.h"
namespace E3DEngine
{

    ParticleFactory::ParticleFactory()
    {
        ImplmentParticle();
    }

    ParticleFactory::~ParticleFactory() = default;

	ParticleGroup* ParticleFactory::CreateParticle()
    {
		// 创建粒子团
		ParticleGroup *p = new ParticleGroup();
        return p;
    }

	void ParticleFactory::ResumParticleGroup(std::string name, ParticleGroup * p)
	{
		if (m_ParticleGroupPool.find(name) != m_ParticleGroupPool.end())
		{
			return;
		}
		
		m_ParticleGroupPool[name] = p;
	}

	void ParticleFactory::DeleteParticleGroupFromPool(std::string name)
	{
		if (m_ParticleGroupPool.find(name) == m_ParticleGroupPool.end())
		{
			return;
		}

		m_ParticleGroupPool.erase(name);
	}

	void ParticleFactory::Update(float deltaTime)
    {
        
    }
    
    ParticleEmitter * ParticleFactory::CreateParticleEmitter(E3DEngine::ParticleGroup *p, std::string name)
    {
		std::string type_name = ClassFactory::GetInstance().getTypeNameByClassName(name);
        ParticleEmitter * emitter = (ParticleEmitter *)ClassFactory::GetInstance().CreateClass(type_name);
        emitter->Initilize(p);
        return emitter;
    }
    
    ParticleAffector * ParticleFactory::CreateParticleAffector(E3DEngine::ParticleGroup *p, std::string name)
	{
		std::string type_name = ClassFactory::GetInstance().getTypeNameByClassName(name);
        ParticleAffector * affector = (ParticleAffector *)ClassFactory::GetInstance().CreateClass(type_name);
        affector->Initilize(p);
        return affector;
    }
    
    void ParticleFactory::Initilize()
    {
        
    }
    
    void ParticleFactory::Destory()
    {
        
    }
	
	DECLARE_CLASS_NAME(ParticleEmitter)
	DECLARE_CLASS_NAME(BallEmitter)
	DECLARE_CLASS_NAME(AreaEmitter)
	DECLARE_CLASS_NAME(PointEmitter)
	DECLARE_CLASS_NAME(LinerForceAffector)
	DECLARE_CLASS_NAME(RandomForceAffector)
    DECLARE_CLASS_NAME(MoveToFiringPointForceAffector)
    DECLARE_CLASS_NAME(RotateForceAffector)
	DECLARE_CLASS_NAME(LinnerColorAffector)
	DECLARE_CLASS_NAME(GroupRotationAffector)
	DECLARE_CLASS_NAME(RotateAffector)
	DECLARE_CLASS_NAME(ScaleAffector)
	
    void ImplmentParticle()
    {
        REGIST_CLASS(ParticleEmitter);
        REGIST_CLASS(BallEmitter);
        REGIST_CLASS(AreaEmitter);
        REGIST_CLASS(PointEmitter);
        REGIST_CLASS(LinerForceAffector);
        REGIST_CLASS(RandomForceAffector);
        REGIST_CLASS(MoveToFiringPointForceAffector);
        REGIST_CLASS(RotateForceAffector);
        REGIST_CLASS(LinnerColorAffector);
        REGIST_CLASS(GroupRotationAffector);
        REGIST_CLASS(RotateAffector);
        REGIST_CLASS(ScaleAffector);
    }
}
