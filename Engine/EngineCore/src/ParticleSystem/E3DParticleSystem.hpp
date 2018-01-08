//
//  ParticleSystem.hpp
//
//  Created by 潘庆云 on 2017/1/17.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "../Source/Interface.h"
#include "../Object/E3DComponent.hpp"

namespace E3DEngine
{
	class ParticleAffector;
	class ParticleEmitter;
	class RenderObject;
	class ParticleGroup;
	class ParticleConfig;
	class ParticleSystem implement ISystem
	{
	public:		
		ParticleSystem() = default;
		virtual ~ParticleSystem() override;
		virtual void Initilize() override;
		void AnalysisConfig(const char * config);
		void CreateParticleEmitter(std::string configName, uint configID, ParticleGroup * p, const char * emitterName, int emitterID, vec3f position = vec3f(0, 0, 0));
		void CreateParticleAffector(std::string configName, uint configID, ParticleGroup * p, const char * affectorName, int affectorID);
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;
		virtual std::string GetName() override;
		virtual void ClearParticle();
		virtual void CameraRotate(mat4f rotate);
		std::vector<Component*> * ActiveParticle(QWORD particleID, std::string cfgName, vec3f position = vec3f(0, 0, 0), bool bActive = true);

	protected:
		void createParticleAffector(ParticleConfig *config, std::string cfgName, ParticleGroup * particle);
		void createParticleEmitter(ParticleConfig *config, std::string cfgName, ParticleGroup * particle, vec3f position);
		void initParticleLayer(ParticleConfig *config, ParticleGroup * particle, bool bActive);
		void initParticleGroup(ParticleGroup * particle, std::string cfgName, ParticleConfig *config, QWORD particleID);

	private:
		std::map<QWORD, std::vector<ParticleEmitter*>> m_ParticleEmitters;
		std::map<QWORD, std::vector<ParticleAffector*>> m_ParticleAffectors;
	};
}
#endif /* ParticleSystem_hpp */
