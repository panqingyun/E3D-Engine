//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-17  PanQingyun. All rights reserved. ************************//
#include "E3DParticleEmitter.hpp"
#include "E3DParticle.h"
#include "../Config/Table.h"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{
    
    void ParticleEmitter::Update(float deltaTime)
    {
        if (m_pParticleGroup->IsActive == false)
        {
            return;
        }
        if (!m_bEnable)
        {
            return;
        }
        if (m_bIsBlank && m_bIsLoop)
        {
            m_fHasBlankTime += deltaTime;
            if (m_fHasBlankTime >= m_fBlankTime)
            {
                m_fHasBlankTime = 0;
                m_CurrentParticleNumer = 0;
                m_bIsBlank = false;
            }
        }
        else
        {
            if (m_fBronInterval > 0.0)
            {
                m_fBronDeltaTime += deltaTime;
                if (m_fBronDeltaTime >= m_fBronInterval)
                {
                    m_fBronDeltaTime = 0.0;
                    _CreateParticle();
                }
            }
            else
            {
                _CreateParticle();
            }
        }
    }
    
    void ParticleEmitter::CreateParticleEx()
    {
        if (m_pParticleGroup->IsActive == false)
        {
            return;
        }
        if (!m_bEnable)
        {
            return;
        }
        if(m_pParticleGroup->m_isLock > 0)
        {
            return;
        }
        if (m_bIsBlank && m_bIsLoop)
        {
            return;
        }
        if (m_fBronInterval > 0.0)
        {
            m_fBronDeltaTime += 1.0f/60.0f;;
            if (m_fBronDeltaTime >= m_fBronInterval)
            {
                m_fBronDeltaTime = 0.0;
                _CreateParticle();
            }
        }
        else
        {
            _CreateParticle();
        }
    }
    
    void ParticleEmitter::Initilize(E3DEngine::ParticleGroup *p)
    {
        m_pConfigTable = nullptr;
        m_bIsLoop = true;
        m_bEnable = true;
        m_pParticleGroup = p;
        m_bIsBlank = false;
        m_CurrentParticleNumer = 0;
        m_fBlankTime = 0;
		m_pParticleGroup->UpdateRefrence(1);
    }
    
    void ParticleEmitter::InitCompleted()
	{
		m_pParticleGroup->SetParticleSize(vec2f(m_v2ParticleSize.x, m_v2ParticleSize.y));
        _CreateParticle();
		m_pParticleGroup->CreateParticle(m_MaxParticleNumber, m_LiveTime, vec3f(NO_POS), m_v2ParticleSize, m_fParticleColor, particleGroupID, vec3f(0.0, 0.0, 0.0), true);
		bIsFirstCreate = false;
    }
    
    bool ParticleEmitter::CheckLiveTime(float time)
    {
        float maxlivetime = m_LiveTime + m_fLiveRandom/2.0f;
        return time < maxlivetime;
    }
    
    void ParticleEmitter::SetEmitterPosition(vec3f position)
    {
        m_pParticleGroup->SetParticleDir(position, m_EmitterPosition);
        if (m_pParticleGroup->m_isLock == 0)
            m_EmitterPosition = position;
    }
    
    void ParticleEmitter::_CreateParticle()
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
        // 如果还没有创建足够的粒子
        if (m_CurrentParticleNumer < m_TotalParticleNumber)
        {
            // 生成粒子
            if (!bIsFirstCreate)
            {
				_GenEmissionPosition();
            }
        }
        else
        {
            if (m_bIsLoop)
            {
                // 已经创建了足够的粒子，并且是循环发射，发射器进入间歇
                m_bIsBlank = true;
            }
            else
            {
                // 不再发射
                m_bEnable = false;
                if (!StopEmitterHandle.empty())
                {
                    StopEmitterHandle(this, nullptr);
                }
            }
        }
    }
    
    ParticleEmitter::~ParticleEmitter()
    {
        SAFE_DELETE(m_pConfigTable);
    }
    
    
	void ParticleEmitter::ParseConfig(TableBase *pConfigTable)
	{
		m_pConfigTable = pConfigTable;
	}

	vvision::vec3f ParticleEmitter::GetEmitterPosition()
	{
		return m_EmitterPosition;
	}

	void ParticleEmitter::SetEnable(bool isEnable)
	{
		m_bEnable = isEnable;
	}

	PointEmitter::PointEmitter()
    {
        
    }
    
    void PointEmitter::Initilize(ParticleGroup *p)
    {
        ParticleEmitter::Initilize(p);
        m_Type = eParticleEmitterPoint;
        m_LiveTime = 2;
        m_v2ParticleSize.x = 0.15;
        m_v2ParticleSize.y = 0.15;
        m_fBlankTime = 1;
        m_fParticleColor = 0;
        m_TotalParticleNumber = 10000;
        m_pParticleGroup->SetMaxParticleNumber(1000);
        m_vPointPosition = vec3f(0, 0, 0);
    }
    
    void PointEmitter::_GenEmissionPosition()
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
        m_pParticleGroup->CreateParticle(m_CurrentCreateNumber, m_LiveTime, m_EmitterPosition + m_vPointPosition, m_v2ParticleSize, m_fParticleColor, particleGroupID,vec3f(0.0,0.0,0.0));
        m_CurrentParticleNumer += m_CurrentCreateNumber;
    }
    
    void PointEmitter::ParseConfig(E3DEngine::TableBase *pConfigTable)
    {
        PointEmitterConfig * cfg = (E3DEngine::PointEmitterConfig *)pConfigTable;
        m_LiveTime = cfg->ParticleLiveTime;
        m_v2ParticleSize.x = cfg->ParticleWidth;
        m_v2ParticleSize.y = cfg->ParticleHeight;
        m_fBlankTime = cfg->BlankTime;
        m_CurrentCreateNumber = cfg->CreateParticleOnce;
        m_TotalParticleNumber = cfg->TotalParticleNumber;
        m_bIsBillboard = cfg->IsBillboard == 1 ? true : false;
        m_bIsLoop = cfg->IsLoop == 1 ? true : false;
        //        m_pParent->SetIsBillborad(m_bIsBillboard);
		m_MaxParticleNumber = cfg->MaxParticleNumber;
        m_pParticleGroup->SetMaxParticleNumber(cfg->MaxParticleNumber);
        std::vector<std::string> strs = StringBuilder::Split(cfg->ParticlePosition, ",");
        if (strs.size() == 3)
        {
            m_vPointPosition =
            vec3f(Convert::ToFloat(strs[0]), Convert::ToFloat(strs[1]), Convert::ToFloat(strs[2]));
            m_pParticleGroup->Transform->SetPosition(m_vPointPosition);
            m_EmitterPosition.x == 0 ? m_EmitterPosition.x = m_vPointPosition.x : m_EmitterPosition.x = m_EmitterPosition.x;
            m_EmitterPosition.y == 0 ? m_EmitterPosition.y = m_vPointPosition.y : m_EmitterPosition.y = m_EmitterPosition.y;
            m_EmitterPosition.z = m_vPointPosition.z;
        }
    }
    
    AreaEmitter::AreaEmitter()
    {
        areaXPos = 0;
    }
    
    void AreaEmitter::Initilize(ParticleGroup *p)
    {
        ParticleEmitter::Initilize(p);
        m_Type = eParticleEmitterArea;
        m_vAreaRange.x = 5;
        m_vAreaRange.y = 5;
        m_vAreaRange.z = 5;
        m_LiveTime = 5;
        m_v2ParticleSize.x = 0.1;
        m_v2ParticleSize.y = 0.1;
        m_fParticleColor = 0;
        m_TotalParticleNumber = 1000;
        m_pParticleGroup->SetMaxParticleNumber(100);
    }
    
    void AreaEmitter::_GenEmissionPosition()
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
        
        for (int i = 0; i < m_CurrentCreateNumber; i++)
        {
            float xArea = RangeRandom(0, m_vAreaRange.x) - m_vAreaRange.x / 2 + m_EmitterPosition.x;
            float yArea = RangeRandom(0, m_vAreaRange.y) - m_vAreaRange.y / 2 + m_EmitterPosition.y;
            float zArea = RangeRandom(0, m_vAreaRange.z) - m_vAreaRange.z / 2 + m_EmitterPosition.z;
            
            Vector2 ParticleSize = m_v2ParticleSize;
            if (m_SizeScaleRange.y > m_SizeScaleRange.x)
            {
                int min = m_SizeScaleRange.x*100.0;
                int max = m_SizeScaleRange.y*100.0;
                float scalevale = (min + rand() % (max - min)) / 100.0;
                ParticleSize.x = ParticleSize.x*scalevale;
                ParticleSize.y = ParticleSize.y*scalevale;
            }
            
            float alpha = m_fParticleColor;
            if (m_AlphaRange.y > m_AlphaRange.x)
            {
                int min = m_AlphaRange.x*100.0;
                int max = m_AlphaRange.y*100.0;
                alpha = (min + rand() % (max - min)) / 100.0;
            }
            
            m_pParticleGroup->CreateParticle(1, m_LiveTime, vec3f(xArea, yArea, zArea), ParticleSize, alpha, particleGroupID,m_EmitterPosition);
        }
        m_CurrentParticleNumer += m_CurrentCreateNumber;
    }
    
    void AreaEmitter::ParseConfig(E3DEngine::TableBase *pConfigTable)
    {
        AreaEmitterConfig * cfg = (E3DEngine::AreaEmitterConfig *)pConfigTable;
        m_LiveTime = cfg->ParticleLiveTime;
        m_v2ParticleSize.x = cfg->ParticleWidth;
        m_v2ParticleSize.y = cfg->ParticleHeight;
        m_fBlankTime = cfg->BlankTime;
        m_bIsBillboard = cfg->IsBillboard == 1 ? true : false;
        m_bIsLoop = cfg->IsLoop == 1 ? true : false;
        m_TotalParticleNumber = cfg->TotalParticleNumber;
        m_CurrentCreateNumber = cfg->CreateParticleOnce;
        m_fBronInterval = cfg->BornInterval;
		//        m_pParent->SetIsBillborad(m_bIsBillboard);
		m_MaxParticleNumber = cfg->MaxParticleNumber;
        m_pParticleGroup->SetMaxParticleNumber(cfg->MaxParticleNumber);
        std::vector<std::string> alpharange = StringBuilder::Split(cfg->AlphaRange, ",");
        if (alpharange.size() == 2)
        {
            m_AlphaRange = vec2f(Convert::ToFloat(alpharange[0]), Convert::ToFloat(alpharange[1]));
        }
        std::vector<std::string> scalerange = StringBuilder::Split(cfg->ScaleRange, ",");
        if (scalerange.size() == 2)
        {
            m_SizeScaleRange = vec2f(Convert::ToFloat(scalerange[0]), Convert::ToFloat(scalerange[1]));
        }
        
        std::vector<std::string> range = StringBuilder::Split(cfg->AreaRange, ",");
        if (range.size() == 3)
        {
            m_vAreaRange = vec3f(Convert::ToFloat(range[0]), Convert::ToFloat(range[1]), Convert::ToFloat(range[2]));
        }
        std::vector<std::string> pos = StringBuilder::Split(cfg->ParticlePosition, ",");
        if (pos.size() == 3)
        {
            m_vPosition = vec3f(Convert::ToFloat(pos[0]), Convert::ToFloat(pos[1]), Convert::ToFloat(pos[2]));
            m_pParticleGroup->Transform->SetPosition(m_vPosition);
            m_EmitterPosition.x == 0 ? m_EmitterPosition.x = m_vPosition.x : m_EmitterPosition.x = m_EmitterPosition.x;
            m_EmitterPosition.y == 0 ? m_EmitterPosition.y = m_vPosition.y : m_EmitterPosition.y = m_EmitterPosition.y;
            m_EmitterPosition.z = m_vPosition.z;
        }
    }
    
    // 球形发射器
    BallEmitter::BallEmitter()
    {
        
    }
    
    void BallEmitter::Initilize(ParticleGroup *p)
	{
		ParticleEmitter::Initilize(p);
		m_v2ParticleSize.x = 0.5;
		m_v2ParticleSize.y = 0.5;
        m_Type = eParticleEmitterBall;
        m_LiveTime = 5;
        m_fParticleColor = 1;
        m_fBlankTime = 10;
        Radius = 3;
        m_TotalParticleNumber = 10000;
        m_CurrentCreateNumber = 1;
        m_SizeScaleRange = vec2f(1.0, 1.0);
        m_pParticleGroup->SetMaxParticleNumber(900);
    }
    
    void BallEmitter::_GenEmissionPosition()
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
        for (int i = 0; i < m_CurrentCreateNumber; i++)
        {
#ifdef _WIN32
            float alpha = M_PI * (rand() % 36000) / 18000.0f;
            float beta = M_PI * (rand() % 36000) / 18000.0f;
#else
            float alpha = M_PI * (random() % 36000) / 18000.0f;
            float beta = M_PI * (random() % 36000) / 18000.0f;
#endif
            float r = rand()%(int)Radius;
            float sinbeta = sin(beta);
            float x = Radius * cos(alpha) * sinbeta + m_EmitterPosition.x;
            float y = Radius * sin(alpha) * sinbeta + m_EmitterPosition.y;
            float z = Radius * cos(beta) + m_EmitterPosition.z;
            Vector2 ParticleSize = m_v2ParticleSize;
            if (m_SizeScaleRange.y > m_SizeScaleRange.x)
            {
                int min = m_SizeScaleRange.x*100.0;
                int max = m_SizeScaleRange.y*100.0;
                float scalevale = (min + rand() % (max - min)) / 100.0;
                ParticleSize.x = ParticleSize.x*scalevale;
                ParticleSize.y = ParticleSize.y*scalevale;
            }
            float livetime = m_LiveTime;
            if (m_fLiveRandom > 0.0)
            {
                int range = m_fLiveRandom * 200;
                float randvalue = (rand() % range) / 100.0f;
                if (randvalue < m_fLiveRandom)
                {
                    livetime = livetime - randvalue;
                }
                else
                {
                    livetime = livetime + randvalue - m_fLiveRandom;
                }
            }
            
            m_pParticleGroup->CreateParticle(1, livetime, vec3f(x, y, z), ParticleSize, m_fParticleColor, particleGroupID,m_EmitterPosition);
        }
        m_CurrentParticleNumer += m_CurrentCreateNumber;
    }
    
    void BallEmitter::ParseConfig(E3DEngine::TableBase *pConfigTable)
    {
        BallEmitterConfig * cfg = (E3DEngine::BallEmitterConfig *)pConfigTable;
        m_LiveTime = cfg->ParticleLiveTime;
        m_v2ParticleSize.x = cfg->ParticleWidth;
        m_v2ParticleSize.y = cfg->ParticleHeight;
        m_fBlankTime = cfg->BlankTime;
        m_TotalParticleNumber = cfg->TotalParticleNumber;
        m_bIsBillboard = cfg->IsBillboard == 1 ? true : false;
        m_bIsLoop = cfg->IsLoop == 1 ? true : false;
        m_fBronInterval = cfg->BornInterval;
        m_fLiveRandom = cfg->LiveTimeRandom;
        m_CurrentCreateNumber = cfg->CreateParticleOnce;
        std::vector<std::string> scalerange = StringBuilder::Split(cfg->ScaleRange, ",");
        if (scalerange.size() == 2)
        {
            m_SizeScaleRange = vec2f(Convert::ToFloat(scalerange[0]), Convert::ToFloat(scalerange[1]));
        }
		//        m_pParent->SetIsBillborad(m_bIsBillboard);
		m_MaxParticleNumber = cfg->MaxParticleNumber;
        m_pParticleGroup->SetMaxParticleNumber(cfg->MaxParticleNumber);
        std::vector<std::string> pos = StringBuilder::Split(cfg->ParticlePosition, ",");
        if (pos.size() == 3)
        {
            m_vPosition = vec3f(Convert::ToFloat(pos[0]), Convert::ToFloat(pos[1]), Convert::ToFloat(pos[2]));
            m_pParticleGroup->Transform->SetPosition(m_vPosition);
            m_EmitterPosition.x == 0 ? m_EmitterPosition.x = m_vPosition.x : m_EmitterPosition.x = m_EmitterPosition.x;
            m_EmitterPosition.y == 0 ? m_EmitterPosition.y = m_vPosition.y : m_EmitterPosition.y = m_EmitterPosition.y;
            m_EmitterPosition.z = m_vPosition.z;
        }
        
    }
}
