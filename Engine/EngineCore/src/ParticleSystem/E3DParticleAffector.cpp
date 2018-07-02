//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-17  PanQingyun. All rights reserved. ************************//

#include "E3DParticleAffector.hpp"
#include "E3DParticle.h"
#include "../Config/Table.h"

namespace E3DEngine
{
    
	void ParticleAffector::Initilize(ParticleGroup *pParent)
	{
		m_pParticleGroup = pParent;
		particleGroupID = 0;
	}


	ParticleAffector::~ParticleAffector()
	{
		m_pParticleGroup = nullptr;
	}

	void ParticleAffector::Update(float deltaTime)
    {
        if (m_pParticleGroup->IsActive == false)
        {
            return;
        }
        //        AffectParticle(deltaTime);
    }
    
    void ParticleAffector::RotateParticleByMat(mat4f rotateMatrix)
    {
        m_matrixRotate = rotateMatrix;
        //m_pParent->Transform->SetRotation(rotateMatrix);
        
    }
    
	RandomForceAffector::RandomForceAffector()
	{
		m_Type = eParticleAffectorLinnerForce;
		m_vForceDirection = vec3f(0, -1, 0);
		m_vForceDirection.normalize();
		m_fSpeed = 4.5;
		m_fStartTime = 0.0;
		m_fEndTime = 0.0;
		m_RandomSpeed[0] = 0.0;
		m_RandomSpeed[1] = 0.0;
	}

	void RandomForceAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
		if (particle.getReferenceCount() == 0)
		{
			return;
		}
		Particle * ptr = particle.get_ptr();
		if (ptr->bFristUpdte)
        {
			ptr->bFristUpdte = false;
            float x = RangeRandom(m_xRandomRange[0], m_xRandomRange[1]);
            float y = RangeRandom(m_yRandomRange[0], m_yRandomRange[1]);
            float z = RangeRandom(m_zRandomRange[0], m_zRandomRange[1]);
            m_vForceDirection = vec3f(x, y, z);
            m_vForceDirection.normalize();
			ptr->SetMoveDirction(m_vForceDirection);
            
            if (m_bRotateByOrbit)
            {
				ptr->RotateByDir(m_pParticleGroup->m_ParticleDir);
                            }
            else if(m_bRotateByDir)
            {
				ptr->RotateByDir(ptr->GetMoveDirection());
            }
        }
        
        if (m_fEndTime > m_fStartTime)
        {
			float totalTime = ptr->getTotleLiveTime();
			float hasLiveTime = ptr->getLiveTime();
            float P = hasLiveTime / totalTime;
            
            if (P > m_fStartTime && P < m_fEndTime)
            {
				if (ptr->GetRandomForceID() != m_ID)
                {
					ptr->SetRandomForceID(m_ID);
                    float speed = m_fSpeed;
                    if (m_RandomSpeed[1] > m_RandomSpeed[0])
                    {
                        speed = RangeRandom(m_RandomSpeed[0], m_RandomSpeed[1]);
                    }
					ptr->SetMoveSpeed(speed);
                }
                
				vec3f newPos = ptr->Transform->Position + ptr->GetMoveDirection() * ptr->GetMoveSpeed() * fElapsedTime;
				ptr->Transform->SetPosition(newPos);
            }
        }
        else
        {
			vec3f dir = ptr->GetMoveDirection();
            if (m_pParticleGroup->m_isLock == 2)
            {
                dir.x += m_pParticleGroup->m_ParticleDir.x;
            }
            
			if (ptr->GetMoveSpeed() < 0.000001  && ptr->GetMoveSpeed() > -0.00001)
            {
                float speed = m_fSpeed;
                if (m_RandomSpeed[1] > m_RandomSpeed[0])
                {
                    speed = RangeRandom(m_RandomSpeed[0], m_RandomSpeed[1]);
                }
				ptr->SetMoveSpeed(speed);
            }
            
			vec3f newPos = ptr->Transform->Position + dir * ptr->GetMoveSpeed() * fElapsedTime;
            //            if (m_pParent->GetIsBillBoard())
            //            {
            //                particle->Transform->GenBillBoard(particle->GetReightVector(), m_pParent->pCamera->GetForwardVector());
            //            }
            
			ptr->Transform->SetPosition(newPos);
        }
    }
    
    
    void RandomForceAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        auto cfg	= (RandomForceAffectorConfig*)pConfig;
        auto xRange = StringBuilder::Split(cfg->xRandom, ",");
        m_xRandomRange[0] = Convert::ToFloat(xRange[0]);
        m_xRandomRange[1] = Convert::ToFloat(xRange[1]);
        
        auto yRange			= StringBuilder::Split(cfg->yRandom, ",");
        m_yRandomRange[0]	= Convert::ToFloat(yRange[0]);
        m_yRandomRange[1]	= Convert::ToFloat(yRange[1]);
        
        auto zRange			= StringBuilder::Split(cfg->zRandom, ",");
        m_zRandomRange[0]	= Convert::ToFloat(zRange[0]);
        m_zRandomRange[1]	= Convert::ToFloat(zRange[1]);

        m_bRotateByDir		= cfg->rotateByDir == 1;
        m_bRotateByOrbit	= cfg->rotateByOrbit;
        m_fStartTime		= cfg->StartTime;
        m_fEndTime			= cfg->EndTime;
        auto ForceRange		= StringBuilder::Split(cfg->ForceRange, ",");

        if (ForceRange.size() == 2)
        {
            m_RandomSpeed[0] = Convert::ToFloat(ForceRange[0]);
            m_RandomSpeed[1] = Convert::ToFloat(ForceRange[1]);
        }
        
        m_fSpeed = cfg->Force;
        m_ID = cfg->ID;
    }
    
	MoveToFiringPointForceAffector::MoveToFiringPointForceAffector()
	{
		m_Type = eParticleAffectorMoveToFiringPointForce;
		//m_TargetPosition = vec3f(0.0,0.0,0.0);
	}

	void MoveToFiringPointForceAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
        
        if (particle.getReferenceCount() == 0)
        {
            return;
        }
        Particle * ptr = particle.get_ptr();
        
        float angle = 0.0f;
        if (ptr->GetMoveSpeed() < 0.000001  && ptr->GetMoveSpeed() > -0.00001)
        {
            float speed = m_fSpeed;
            if (m_fForceRandomRange > 0.0)
            {
                int range = m_fForceRandomRange * 2;
                int randvalue = rand() % range;
                if (randvalue < m_fForceRandomRange)
                {
                    speed = speed - randvalue;
                }
                else
                {
                    speed = speed + randvalue - m_fForceRandomRange;
                }
            }
            ptr->SetMoveSpeed(speed);
            vec3f dir = ptr->GetBornEmitterPos() - ptr->Transform->GetPosition();
            dir.normalize();
            ptr->SetBornPos(ptr->Transform->GetPosition());
            ptr->SetRotateAngle(angle);
            ptr->SetMoveDirction(dir);
            int r = rand()%2;
            ptr->SetRotateSpeed(r > 0?m_fRotateWithEmitterAngle:(-1.0*m_fRotateWithEmitterAngle));
        }
        float hasLiveTime = ptr->getLiveTime();
        float totalTime = ptr->getTotleLiveTime();
        float offset = 0.0f;
        float p = hasLiveTime/totalTime;
        if(ptr->GetMoveSpeed() > 0.0f)
        {
            offset = 1.0f - ptr->GetMoveSpeed()*p;
            if(ptr->Transform->GetPosition().Distance(ptr->GetBornEmitterPos()) > 0.01f && p <= 1.0f)
            {
                vec3f newPos;
                angle = ptr->GetRotateAngle()+fElapsedTime*ptr->GetRotateSpeed();
                vec3f d = (ptr->GetBornPos() - ptr->GetBornEmitterPos())*offset;
                newPos.x = d.x * cos(angle) - d.y * sin(angle) + ptr->GetBornEmitterPos().x;
                newPos.y = d.x * sin(angle) + d.y * cos(angle) + ptr->GetBornEmitterPos().y;
                newPos.z = 0.0f;
                ptr->Transform->SetPosition(newPos);
                ptr->SetRotateAngle(angle);
            }
        }
        else
        {
            offset = ptr->GetMoveSpeed()*p*-1.0f;
            if(p <= 1.0f)
            {
                vec3f newPos;
                angle = ptr->GetRotateAngle()+fElapsedTime*ptr->GetRotateSpeed();
                vec3f d = (ptr->GetBornPos() - ptr->GetBornEmitterPos())*offset;
                newPos.x = d.x * cos(angle) - d.y * sin(angle) + ptr->GetBornEmitterPos().x;
                newPos.y = d.x * sin(angle) + d.y * cos(angle) + ptr->GetBornEmitterPos().y;
                newPos.z = 0.0f;
                ptr->Transform->SetPosition(newPos);
                ptr->SetRotateAngle(angle);
            }
        }
    }
    
    void MoveToFiringPointForceAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        MoveToFiringPointForceAffectorConfig *cfg = (MoveToFiringPointForceAffectorConfig*)pConfig;
        m_fSpeed = cfg->Force;
        m_fForceRandomRange = cfg->ForceRandomRange;
        m_fRotateWithEmitterAngle = cfg->RotateWithEmitterAngle;
    }
    
	RotateForceAffector::RotateForceAffector()
	{
		m_Type = eParticleAffectorRotateForce;
		//m_TargetPosition = vec3f(0.0,0.0,0.0);
	}

	void RotateForceAffector::InitParticle(Particle *p)
	{

	}

	void RotateForceAffector::Clone(ParticleAffector *pe)
	{

	}

	void RotateForceAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
		if (particle.getReferenceCount() == 0)
		{
			return;
		}
		Particle * ptr = particle.get_ptr();
		if (ptr->GetMoveSpeed() < 0.000001  && ptr->GetMoveSpeed() > -0.00001)
        {
            float speed = m_fSpeed;
            if (m_fForceRandomRange > 0.0)
            {
                int range = m_fForceRandomRange * 2;
                int randvalue = rand() % range;
                if (randvalue < m_fForceRandomRange)
                {
                    speed = speed - randvalue;
                }
                else
                {
                    speed = speed + randvalue - m_fForceRandomRange;
                }
            }
			ptr->SetMoveSpeed(speed);
			ptr->SetRotateAngle(0.0f);
			ptr->SetBornPos(ptr->Transform->GetPosition());
        }
		float theta = ptr->GetRotateAngle() + fElapsedTime*ptr->GetMoveSpeed();
        vec3f newPos;
		vec3f curPos = ptr->GetBornPos() - ptr->GetBornEmitterPos();
        newPos.x = curPos.x * (cos(theta) + m_vAxis.x * m_vAxis.x * (1 - cos(theta))) +
        curPos.y * (m_vAxis.x * m_vAxis.y * (1 - cosf(theta)) - m_vAxis.z * sin(theta)) +
        curPos.z * (m_vAxis.x * m_vAxis.z * (1 - cosf(theta) + m_vAxis.y * sinf(theta)));
        newPos.y = curPos.x * (m_vAxis.x * m_vAxis.y * (1 - cosf(theta)) + m_vAxis.z * sinf(theta))            + curPos.y * (m_vAxis.y * m_vAxis.y * (1 - cosf(theta)) + cosf(theta)) +
        curPos.z * (m_vAxis.y * m_vAxis.z * (1 - cosf(theta)) - m_vAxis.x * sinf(theta));
        newPos.z = curPos.x * (m_vAxis.x * m_vAxis.z * (1 - cosf(theta) - m_vAxis.y * sinf(theta))) + curPos.y * (m_vAxis.y * m_vAxis.z * (1 -cosf(theta)) + m_vAxis.x * sinf(theta)) +curPos.z * (m_vAxis.z * m_vAxis.z * (1 - cosf(theta)) + cosf(theta));
		newPos += ptr->GetBornEmitterPos();
		ptr->Transform->SetPosition(newPos);
		ptr->SetRotateAngle(theta);
    }
    
    void RotateForceAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        RotationForceAffectorConfig *cfg = (RotationForceAffectorConfig*)pConfig;
        m_fSpeed = cfg->Force;
        m_fForceRandomRange = cfg->ForceRandomRange;
        std::vector<std::string> strs = StringBuilder::Split(cfg->axis, ",");
        
        if (strs.size() == 3)
        {
            m_vAxis = vec3f(Convert::ToFloat(strs[0]),
                            Convert::ToFloat(strs[1]),
                            Convert::ToFloat(strs[2]));
        }
        m_vAxis.normalize();
    }
    
	LinerForceAffector::LinerForceAffector()
	{
		m_Type = eParticleAffectorLinnerForce;
		m_vForceDirection = vec3f(0, 0, 1);
		m_vForceDirection.normalize();
	}

	void LinerForceAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
		if (particle.getReferenceCount() == 0)
		{
			return;
		}
		Particle * ptr = particle.get_ptr();
		if (ptr->GetMoveSpeed() < 0.000001  && ptr->GetMoveSpeed() > -0.00001)
        {
            float speed = m_fSpeed;
            if (m_fForceRandomRange > 0.0)
            {
                int range = m_fForceRandomRange * 2;
                int randvalue = rand() % range;
                if (randvalue < m_fForceRandomRange)
                {
                    speed = speed - randvalue;
                }
                else
                {
                    speed = speed + randvalue - m_fForceRandomRange;
                }
            }
			ptr->SetMoveSpeed(speed);
        }
		vec3f newPos = ptr->Transform->Position + m_vForceDirection * ptr->GetMoveSpeed() * fElapsedTime;
        //		if (m_pParent->GetIsBillBoard())
        //		{
        //			particle->Transform->GenBillBoard(particle->GetReightVector(), m_pParent->pCamera->GetForwardVector());
        //		}
		ptr->Transform->SetPosition(newPos);
        
    }
    
    void LinerForceAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        LinnerForceAffectorConfig *cfg = (LinnerForceAffectorConfig*)pConfig;
        std::vector<std::string> strs = StringBuilder::Split(cfg->Direction, ",");
        
        if (strs.size() == 3)
        {
            m_vForceDirection = vec3f(Convert::ToFloat(strs[0]),
                                      Convert::ToFloat(strs[1]),
                                      Convert::ToFloat(strs[2]));
        }
        m_fSpeed = cfg->Force;
        m_fForceRandomRange = cfg->ForceRandomRange;
    }
    
	LinnerColorAffector::LinnerColorAffector()
	{
		m_nStartColor = vec4f(1, 1, 1, 1);
		m_nEndColor = vec4f(1, 1, 1, 1);
		m_fStartTime = 0;
		m_fEndTime = 0;
	}

	void LinnerColorAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
        
        float totalTime = 0;
        float hasLiveTime = 0;
        float liveTimeEnd = 0;
        float K = 0, P = 0;
		if (particle.getReferenceCount() == 0)
		{
			return;
		}
		Particle * ptr = particle.get_ptr();
		totalTime = ptr->getTotleLiveTime();
		hasLiveTime = ptr->getLiveTime() + fElapsedTime;
        liveTimeEnd = m_fEndTime * totalTime;
        P = hasLiveTime / totalTime;
        if (P >= m_fStartTime && m_fEndTime > P)
        {// 在这个影响周期内
            K = hasLiveTime / liveTimeEnd;
            float currentR = K * rChange + m_nStartColor.r;
            float currentG = K * gChange + m_nStartColor.g;
            float currentB = K * bChange + m_nStartColor.b;
            float currentA = K * aChange + m_nStartColor.a;
            
			ptr->SetColor(currentR, currentG, currentB, currentA);
        }
        
    }
    
    void LinnerColorAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        LinnerColorAffectorConfig * cfg = (LinnerColorAffectorConfig *)pConfig;
        if (cfg != nullptr)
        {
            m_nStartColor = Convert::ToColorRGBA(cfg->StartColor);
            m_nEndColor = Convert::ToColorRGBA(cfg->EndColor);
            m_fStartTime = cfg->StartTime;
            m_fEndTime = cfg->EndTime;
            m_UseSrcAlpha = cfg->UseSrcAlpha;
            
            rChange = m_nEndColor.r - m_nStartColor.r;
            gChange = m_nEndColor.g - m_nStartColor.g;
            bChange = m_nEndColor.b - m_nStartColor.b;
            aChange = m_nEndColor.a - m_nStartColor.a;
            
        }
    }
    int i = 0;

	GroupRotationAffector::GroupRotationAffector()
	{
		m_fRotateSpeed = 0;
		m_RotateAxis.normalize();
	}

	void GroupRotationAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
		if (particle.getReferenceCount() == 0)
		{
			return;
		}
		Particle * ptr = particle.get_ptr();

		//float totalTime = ptr->getTotleLiveTime();
		//float hasLiveTime = ptr->getLiveTime();
        //float p = hasLiveTime/totalTime;
        
        vec3f target = m_pParticleGroup->m_EmitterPositon;

		vec3f dir = ptr->Transform->GetPosition() - m_pParticleGroup->m_EmitterPositon;
        dir.normalize();
		ptr->RotateByDir(dir, m_fRotateSpeed);
    }
    
    void GroupRotationAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        RotationAffectorConfig * cfg = (RotationAffectorConfig *)pConfig;
        if (cfg != nullptr)
        {
            m_fRotateSpeed = cfg->RoteteSpeed;
            std::vector<std::string> axis = StringBuilder::Split(cfg->RotateAxis, ",");
            if (axis.size() == 3)
            {
                m_RotateAxis = vec3f(Convert::ToFloat(axis[0]), Convert::ToFloat(axis[1]), Convert::ToFloat(axis[2]));
            }
        }
    }
    
    void ScaleAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        SelfScalAffectorConfig * cfg = (SelfScalAffectorConfig *)pConfig;
        if (cfg != nullptr)
        {
            m_fStartScale = cfg->StartScale;
            m_fEndScale = cfg->EndScale;
            m_fStartTime = cfg->StartTime;
            m_fEndTime = cfg->EndTime;
        }
    }
    
    void ScaleAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
		if (particle.getReferenceCount() == 0)
		{
			return;
		}

        //缩放值和时间成线性关系
        // 两点式方程 (y - start) / (end - start) = (x - 0) / (totalTime - 0)
        float totalTime = 0;
        float hasLiveTime = 0;
        float liveTimeEnd = 0;
        float K = 0, P = 0;
		Particle * ptr = particle.get_ptr();

		totalTime = ptr->getTotleLiveTime();
		hasLiveTime = ptr->getLiveTime() + fElapsedTime;
        liveTimeEnd = m_fEndTime * totalTime;
        P = hasLiveTime / totalTime;
        if (P >= m_fStartTime && m_fEndTime > P)
        {
            K = (hasLiveTime - m_fStartTime*totalTime) / ((m_fEndTime - m_fStartTime)*totalTime);
            float scale = K * (m_fEndScale - m_fStartScale) + m_fStartScale;
			ptr->Transform->SetScale(vec3f(scale, scale, 1));
        }
    }
    
    void RotateAffector::ParseConfig(E3DEngine::TableBase *pConfig)
    {
        SelfRotateAffectorConfig * cfg = (SelfRotateAffectorConfig *)pConfig;
        if (cfg != nullptr)
        {
            m_fSpeed = cfg->RoteteSpeed;
            m_bStartRandom = cfg->StartRandom > 0?true:false;
            std::vector<std::string> axis = StringBuilder::Split(cfg->RotateAxis, ",");
            if (axis.size() == 3)
            {
                m_vAxis = vec3f(Convert::ToFloat(axis[0]), Convert::ToFloat(axis[1]), Convert::ToFloat(axis[2]));
            }
            axis = StringBuilder::Split(cfg->RotateSpeedRange, ",");
            if (axis.size() == 2)
            {
                m_vSpeedRange = vec2f(Convert::ToFloat(axis[0]), Convert::ToFloat(axis[1]));
            }
        }
        m_fAngle = 0;
    }
    
    void RotateAffector::AffectParticle(float fElapsedTime, share_pointer<Particle> particle)
    {
        
        if (m_pParticleGroup == nullptr)
        {
            return;
        }
		if (particle.getReferenceCount() == 0)
		{
			return;
		}
		Particle * ptr = particle.get_ptr();
		if (ptr->GetRotateSpeed() < 0.0000001 && ptr->GetRotateSpeed() > -0.0000001)
        {
			ptr->SetRotateSpeed(RangeRandom(m_vSpeedRange.x, m_vSpeedRange.y));
            if(m_bStartRandom)
            {
                float a = RangeRandom(0.0, 2*M_PI);
				ptr->SetRotateAngle(a);
            }
        }
        //Quatf q = Quatf::fromAxisRot(m_vAxis, m_fSpeed);
		float speed = ptr->GetRotateSpeed();
		float rotateAngle = ptr->GetRotateAngle();
        rotateAngle += speed*fElapsedTime;
		ptr->SetRotateAngle(rotateAngle);
        vec3f v;// = q.toEulerAngles();
        v.x = rotateAngle * m_vAxis.x;
        v.y = rotateAngle * m_vAxis.y;
        v.z = rotateAngle * m_vAxis.z;
        
		ptr->Transform->SetRotation(v.x, v.y, v.z);
    }
}
