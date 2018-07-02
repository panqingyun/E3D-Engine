//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-18  PanQingyun. All rights reserved. ************************//

#ifndef ParticleSystemFactory_hpp
#define ParticleSystemFactory_hpp

#include <stdio.h>
#include "E3DParticleEmitter.hpp"
#include "E3DParticleAffector.hpp"
#include "E3DParticle.h"

namespace E3DEngine
{
    void ImplmentParticle();
    class ParticleFactory : public IFactory
    {
    public:
        static ParticleFactory& GetInstance()
        {
            static ParticleFactory _ins;
            return _ins;
        }
        virtual         void Initilize() override;
        virtual         void Destory() override;
        virtual         void Update(float deltaTime);
		ParticleGroup*	CreateParticle();
		void			ResumParticleGroup(std::string name, ParticleGroup * p);
		void			DeleteParticleGroupFromPool(std::string name);
        template<typename T> T *CreateParticleEmitter(ParticleGroup *p)
        {
            T *t = new T();
            ((ParticleEmitter*)t)->Initilize(p);
            return t;
        }
        template<typename T> T *CreateParticleAffector(ParticleGroup *p)
        {
            T *t = new T();
            ((ParticleAffector*)t)->Initilize(p);
            return t;
        }
        ParticleEmitter    * CreateParticleEmitter(ParticleGroup *p, std::string name);
        ParticleAffector   * CreateParticleAffector(ParticleGroup *p, std::string name);
    private:
        ParticleFactory();
		virtual ~ParticleFactory() override;
	private:
		std::map<std::string, ParticleGroup*>  m_ParticleGroupPool;
    };
    
}
#endif /* ParticleSystemFactory_hpp */
