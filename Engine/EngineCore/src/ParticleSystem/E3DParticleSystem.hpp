
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-17  PanQingyun. All rights reserved. ************************//

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
	class TableManager;
	class ParticleSystem : public ISystem
	{
	public:		
		static ParticleSystem& GetInstance()
		{
			static ParticleSystem _ins;
			return _ins;
		}
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
		std::vector<ParticleGroup*> * ActiveParticle( std::string cfgName);

	protected:
		void createParticleAffector(ParticleConfig *config, std::string cfgName, ParticleGroup * particle);
		void createParticleEmitter(ParticleConfig *config, std::string cfgName, ParticleGroup * particle);
		void initParticleRenderer(ParticleConfig *config, ParticleGroup * particle);
		void initParticleGroup(ParticleGroup * particle, std::string cfgName, ParticleConfig *config);

	private:
		TableManager * mCurTableManager;

	};
}
#endif /* ParticleSystem_hpp */
