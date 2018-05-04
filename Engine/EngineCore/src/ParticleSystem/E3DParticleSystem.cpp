//
//  ParticleSystem.cpp
//
//  Created by 潘庆云 on 2017/1/17.
//

#include "E3DParticleSystem.hpp"
#include "E3DParticleFactory.hpp"
#include "../Config/TableManager.h"
#include "../Config/Table.h"
#include "../Config/TableRegister.h"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{

	void ParticleSystem::Initilize()
	{

	}

	void ParticleSystem::AnalysisConfig(const char *config)
	{

	}

	void ParticleSystem::CreateParticleEmitter(std::string configName, uint configID, ParticleGroup * p, const char * emitterName, int emitterID, vec3f position)
	{
		TableBase * emitterTbl = EngineDelegate::GetInstance().GetTableManager(configName)->Select(emitterName, emitterID);

		if (emitterTbl != nullptr)
		{
			ParticleEmitter *pEmitter = ParticleFactory::GetInstance().CreateParticleEmitter(p, emitterTbl->Name);
			pEmitter->particleGroupID = configID;
			pEmitter->ParseConfig(emitterTbl);
			p->AddParticleEmitter(pEmitter);
			pEmitter->SetEmitterPosition(position);
			pEmitter->InitCompleted();
		}

	}

	void ParticleSystem::CreateParticleAffector(std::string configName, uint configID, E3DEngine::ParticleGroup *p, const char *affectorName, int affectorID)
	{
		TableBase * affectorTbl = EngineDelegate::GetInstance().GetTableManager(configName)->Select(affectorName, affectorID);

		if (affectorTbl != nullptr)
		{
			ParticleAffector *pAffertor = ParticleFactory::GetInstance().CreateParticleAffector(p, affectorTbl->Name);
			pAffertor->particleGroupID = configID;
			pAffertor->ParseConfig(affectorTbl);
			p->AddParticleAffector(pAffertor);
		}
	}
  

	void ParticleSystem::ClearParticle()
	{

	}

	void ParticleSystem::Destory()
	{
		ClearParticle();
	}

	void ParticleSystem::Update(float deltaTime)
	{
		ParticleFactory::GetInstance().Update(deltaTime);
	}

	std::vector<ParticleGroup*> * ParticleSystem::ActiveParticle(std::string cfgName)
	{
		auto activeParticle = new std::vector<ParticleGroup *>();
		auto tblManager		= EngineDelegate::GetInstance().GetTableManager(cfgName);
		std::vector<ParticleConfig*> * config = nullptr;
		if (tblManager != nullptr)
		{
			config = tblManager->GetTable<ParticleConfig>();
		}
		if (config != nullptr)
		{
			for (auto & it : *config)
			{
				auto particle = ParticleFactory::GetInstance().CreateParticle();
				if (particle == nullptr)
				{
					continue;
				}
				// 初始化粒子团属性
				initParticleGroup(particle, cfgName, it);
				// 初始化粒子团渲染器
				initParticleRenderer(it, particle);
				// 创建发射器
				createParticleEmitter(it, cfgName, particle);
				// 创建影响器
				createParticleAffector(it, cfgName, particle);
				activeParticle->push_back(particle);
			}
			config->clear();
			SAFE_DELETE(config);
		}
		return activeParticle;
	}


	ParticleSystem::~ParticleSystem()
	{
		Destory();
	}


	std::string ParticleSystem::GetName()
	{
		return "ParticleSystem";
	}

	void ParticleSystem::CameraRotate(mat4f rotate)
	{

	}

	void ParticleSystem::initParticleGroup(ParticleGroup * particle, std::string cfgName, ParticleConfig *config)
	{
		particle->ConfigName		= cfgName;
		particle->Tag				= config->ID;
		particle->m_isLock			= config->LockEmitterMove;
		particle->m_MaterialName	= config->Material;
		particle->ParticleConfigID	= config->ID;
		particle->m_DirOffset		= config->DirectionOffset;

		particle->ParseUVConfig(config->TextureUV);
		particle->SetfShaderIndex(config->fShaderIndex);
	}

	void ParticleSystem::initParticleRenderer(ParticleConfig *config, ParticleGroup * particle)
	{
		auto layerConfig = EngineDelegate::GetInstance().GetTableManager(LAYER_CONFIAG_NAME)->Select<LayerConfig>(config->LayerID);
		if (layerConfig == nullptr)
		{
			return;
		}
		std::string layerName = layerConfig->Name;
		particle->SetLayerMask(1 << layerConfig->ID);
		SceneManager::GetInstance().GetCurrentScene()->AddChild(particle);
		std::vector<string> materialCfg = StringBuilder::Split(particle->m_MaterialName, ":");
		std::string materialPath = "";
		int materialID = 1;
		if (materialCfg.size() == 2)
		{
			materialPath = materialCfg[0];
			materialID = Convert::ToInt(materialCfg[1]);
		}
		else if(materialCfg.size() == 1)
		{
			materialPath = materialCfg[0];
		}

		Material * mMaterial = GetRenderSystem()->GetMaterialManager()->CreateMaterial(Application::ResourcePath + materialPath, materialID);
		Renderer * render = GetRenderSystem()->GetRenderManager()->GetRenderer(mMaterial->ID);
		render->SetMaterial(mMaterial);
		particle->SetRenderer(render);
		particle->SetActive(true);
		render->SetRenderIndex(eRI_TopMost);
	}

	void ParticleSystem::createParticleEmitter(ParticleConfig *config, std::string cfgName, ParticleGroup * particle)
	{
		auto emitters = StringBuilder::Split(config->Emitter, ";"); // name1:ID1,ID2;name2:ID1,ID2
		int emitterID = 0;
		for (auto & emitter : emitters)
		{
			auto emitterNameIDs = StringBuilder::Split(emitter, ":");
			auto name			= StringBuilder::Trim(emitterNameIDs[0]);
			auto ids			= StringBuilder::Split(emitterNameIDs[1], ",");

			for (auto & id : ids)
			{
				emitterID = Convert::ToInt(StringBuilder::Trim(id));
				CreateParticleEmitter(cfgName, config->ID, particle, name.c_str(), emitterID);
			}

		}
		emitters.clear();
	}

	void ParticleSystem::createParticleAffector(ParticleConfig *config, std::string cfgName, ParticleGroup * particle)
	{
		auto affectors = StringBuilder::Split(config->Affector, ";"); // name1:ID1,ID2;name2:ID1,ID2
		int affectorID = 0;
		for (auto & affector : affectors)
		{
			auto affectorNameIDs	= StringBuilder::Split(affector, ":");
			auto name				= StringBuilder::Trim(affectorNameIDs[0]);
			auto ids				= StringBuilder::Split(affectorNameIDs[1], ",");
			for (auto & id : ids)
			{
				affectorID = Convert::ToInt(StringBuilder::Trim(id));
				CreateParticleAffector(cfgName, config->ID, particle, name.c_str(), affectorID);
			}

		}
		affectors.clear();
	}

}
