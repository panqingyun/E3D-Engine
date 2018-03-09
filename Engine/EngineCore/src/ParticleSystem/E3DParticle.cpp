//
//  Particle.cpp
//
//  Created by 潘庆云 on 2017/1/17.
//
#include "E3DParticle.h"
#include "../Effect/E3DEffectFactory.hpp"
#include "../Source/EngineDelegate.h"
#include "E3DParticleEmitter.hpp"
#include "E3DParticleAffector.hpp"

namespace E3DEngine
{
	Particle::Particle()
	{
		autoRelease();
		m_bIsBillBoard = true;
		Transform = new CTransform();
		m_MainCamera = nullptr;
		m_FrameEffect = new TextureFrameEffect();
		m_FrameEffect->IsParticleEffect = false;
	}
	
	void Particle::Create(float width, float height, bool ownDimension, float color, vec3f position, int fsIndex,float time2Live)
	{
		m_fTimeToLive = time2Live;
		m_fTotalTimeToLive = time2Live;
		m_fWidth = width;
		m_fHeight = height;
		m_bOwnDimension = ownDimension;
		m_vDirection = vec3f(0, 0, 0);
		fShaderIndex = fsIndex;
		
		ReSet();
		//memcpy(m_fTextureCoord, effect->m_fTextureCoords, sizeof(float)*8);
		m_NotChangeTextureCoord[0].x = 0;
		m_NotChangeTextureCoord[0].y = 0;
		//=========
		m_NotChangeTextureCoord[1].x = 0;
		m_NotChangeTextureCoord[1].y = 1;
		//=========
		m_NotChangeTextureCoord[2].x = 1;
		m_NotChangeTextureCoord[2].y = 1;
		//=========
		m_NotChangeTextureCoord[3].x = 1;
		m_NotChangeTextureCoord[3].y = 0;
		//=========
		
		Transform->SetPosition(position);
		vec3f up = vec3f(0, 1, 0);
		cos_theat[0] = Convert::Vec4ToVec3<float>(m_Point[0]).dotProduct(up) / Convert::Vec4ToVec3<float>(m_Point[0]).length();
		cos_theat[1] = Convert::Vec4ToVec3<float>(m_Point[1]).dotProduct(up) / Convert::Vec4ToVec3<float>(m_Point[1]).length();
		cos_theat[2] = Convert::Vec4ToVec3<float>(m_Point[2]).dotProduct(up) / Convert::Vec4ToVec3<float>(m_Point[2]).length();
		cos_theat[3] = Convert::Vec4ToVec3<float>(m_Point[3]).dotProduct(up) / Convert::Vec4ToVec3<float>(m_Point[3]).length();
		sin_theat[0] = sqrt(1 - cos_theat[0] * cos_theat[0]);
		sin_theat[1] = sqrt(1 - cos_theat[1] * cos_theat[1]);
		sin_theat[2] = -sqrt(1 - cos_theat[2] * cos_theat[2]);
		sin_theat[3] = -sqrt(1 - cos_theat[3] * cos_theat[3]);
		rudis = sqrt(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2;
		updateVertexCoord();
		bFristUpdte = true;
		m_rotateSpeed = 0.0f;
		m_rotateAngle = 0.0f;
		m_RandomForceID = 0;
		const uint indexs[] =
		{
			0, 1, 2,
			2, 3, 0
		};
		memcpy(Indices, indexs, sizeof(uint)* 6);
		StartEffect();
	}
	
	void Particle::ResetFrameEffect()
	{
		m_FrameEffect->ReSet();
	}
	
	void Particle::SetTextureUVCoord(float x, float y, vec2f scale)
	{
		float absScaleX = abs(scale.x);
		float absScaleY = abs(scale.y);
		for (int i = 0; i < 4; i++)
		{
			float _x = (m_NotChangeTextureCoord[i].x - 0.5) * (scale.x / absScaleX) + 0.5; // 如果X上的缩放是负的 则 表示纹理左右颠倒
			float _y = (m_NotChangeTextureCoord[i].y - 0.5) * (scale.y / absScaleY) + 0.5; // 如果Y上的缩放是负的 则 表示纹理上下颠倒
			m_fTextureCoord[i][0] = (x + _x) * absScaleX;
			m_fTextureCoord[i][1] = (y + _y) * absScaleY;
		}
	}
	
	void Particle::EffectFrameChange(IObject *_sender, EventArgs *e)
	{
		if (e == nullptr)
		{
			return;
		}
		
		SetTextureUVCoord(e->lParam, e->rParam, m_FrameEffect->GetTextureFrameScale());
	}

	void Particle::EffectEnd(IObject *_sender, EventArgs *e)
	{
		if (e == nullptr)
		{
			return;
		}

		SetTextureUVCoord(e->lParam, e->rParam, m_FrameEffect->GetTextureFrameScale());
	}
	
	void Particle::PlayDurationEnd(IObject * sender, EventArgs * e)
	{

	}

	void Particle::ResetTextureUVCoord(float whscale)
	{
		float w = m_wh.x;
		w = w*whscale;
		m_fTextureCoord[2][0] = m_uv.x + w;
		m_fTextureCoord[3][0] = m_uv.x + w;
		w = m_fWidth*whscale - (m_fWidth/2);
		m_Point[2] = vec3f(w, -m_fHeight / 2, 0);
		m_Point[3] = vec3f(w, m_fHeight / 2, 0);
	}
	
	void Particle::SetTextureUVCoord(vec2f uv, vec2f wh)
	{
		m_fTextureCoord[0][0] = uv.x;
		m_fTextureCoord[0][1] = uv.y;
		m_fTextureCoord[1][0] = uv.x;
		m_fTextureCoord[1][1] = uv.y + wh.y;
		m_fTextureCoord[2][0] = uv.x + wh.x;
		m_fTextureCoord[2][1] = uv.y + wh.y;
		m_fTextureCoord[3][0] = uv.x + wh.x;;
		m_fTextureCoord[3][1] = uv.y;
		
		m_uv = uv;
		m_wh = wh;
	}
	
	void Particle::ReSet()
	{
		m_fColor[0] = 1;
		m_fColor[1] = 1;
		m_fColor[2] = 1;
		m_fColor[3] = 1;
		m_Point[0] = vec3f(-m_fWidth / 2, m_fHeight / 2, 0);
		m_Point[1] = vec3f(-m_fWidth / 2, -m_fHeight / 2, 0);
		m_Point[2] = vec3f(m_fWidth / 2, -m_fHeight / 2, 0);
		m_Point[3] = vec3f(m_fWidth / 2, m_fHeight / 2, 0);
		Transform->SetRotation(vec3f(0,0,0));
		Transform->SetScale(vec3f(1,1,1));
		m_fSpeed = 0;
		m_vDirection = vec3f(0, 0, 0);
		if (m_FrameEffect != nullptr)
		{
			m_FrameEffect->Stop(true);
		}
	}
	
	Particle::~Particle()
	{
		SAFE_DELETE(Transform);
	}
	
	eParticleLiveState Particle::getParticleState() const
	{
		return m_eParticleState;
	}


	void Particle::setParticleState(eParticleLiveState state)
	{
		m_eParticleState = state;
	}
//worldMatrix * 
//worldMatrix * 
//worldMatrix * 	
//worldMatrix *

	Vertex * Particle::getVertex(mat4f worldMatrix)
	{
		vec4f pos0 = vec4f(Vertes[0].Position[0], Vertes[0].Position[1], Vertes[0].Position[2], 1.0);
		vec4f pos1 = vec4f(Vertes[1].Position[0], Vertes[1].Position[1], Vertes[1].Position[2], 1.0);
		vec4f pos2 = vec4f(Vertes[2].Position[0], Vertes[2].Position[1], Vertes[2].Position[2], 1.0);
		vec4f pos3 = vec4f(Vertes[3].Position[0], Vertes[3].Position[1], Vertes[3].Position[2], 1.0);
		Vertes[0].SetPosition(pos0.x, pos0.y, pos0.z);
		Vertes[1].SetPosition(pos1.x, pos1.y, pos1.z);
		Vertes[2].SetPosition(pos2.x, pos2.y, pos2.z);
		Vertes[3].SetPosition(pos3.x, pos3.y, pos3.z);
		return Vertes;
	}

	void Particle::SetSize(Vector2 size)
	{
		m_fWidth = size.x;
		m_fHeight = size.y;
		m_Point[0] = vec3f(-m_fWidth / 2, m_fHeight / 2, 0);
		m_Point[1] = vec3f(-m_fWidth / 2, -m_fHeight / 2, 0);
		m_Point[2] = vec3f(m_fWidth / 2, -m_fHeight / 2, 0);
		m_Point[3] = vec3f(m_fWidth / 2, m_fHeight / 2, 0);
	}

	void Particle::SetColor(long color)
	{
		m_nCurrentColor = color;
		vec4f vColor = Convert::ToColorRGBA(color);
		m_fColor[0] = vColor.r;
		m_fColor[1] = vColor.g;
		m_fColor[2] = vColor.b;
		m_fColor[3] = vColor.a;
		
	}
	
	void Particle::SetColor(float r, float g, float b)
	{
		m_fColor[0] = RangeNumber(r, 1, 0);
		m_fColor[1] = RangeNumber(g, 1, 0);
		m_fColor[2] = RangeNumber(b, 1, 0);
	}
	
	void Particle::SetColor(float r, float g, float b, float a)
	{
		m_fColor[0] = RangeNumber(r, 1, 0);
		m_fColor[1] = RangeNumber(g, 1, 0);
		m_fColor[2] = RangeNumber(b, 1, 0);
		m_fColor[3] = RangeNumber(a, 1, 0);
	}
	
	void Particle::SetDimension(float width, float height)
	{
		
	}
	vec4f Particle::cumputBillboardCoord(int index)
	{
		vec4f point;
		vec3f forward = -m_MainCamera->GetForwardVector();
		vec3f up = m_MainCamera->GetUpVector();
		//vec3f(0, m_MainCamera->GetUpVector().y, -abs(m_MainCamera->GetUpVector().z));
		
		//		if ( m_MainCamera->GetUpVector().z < 0.5 && m_MainCamera->GetUpVector().z > -0.5)
		//		{
		//			up	= vec3f(0, m_MainCamera->GetUpVector().y, -abs(m_MainCamera->GetUpVector().x));
		//		}
		vec3f right = forward.crossProduct(up);
		up.normalize();
		right.normalize();
		
		point.x = rudis * (up.x * cos_theat[index] + right.x * sin_theat[index]);
		point.y = rudis * (up.y * cos_theat[index] + right.y * sin_theat[index]);
		point.z = rudis * (up.z * cos_theat[index] + right.z * sin_theat[index]);
		point.w = 1.0f;
		return point;
	}
	
	// 根据旋转和 位移计算 顶点 新的坐标
	void Particle::updateVertexCoord()
	{
		// 1---------4
		// |\        |
		// |  \      |
		// |    \    |   (1,2,3),(3,4,1)
		// |      \  |
		// |        \|
		// 2---------3
		/*if (m_bIsBillBoard && m_MainCamera != nullptr)
		{
			vec4f point[4];
			for (int i =0; i < 4; i++)
			{
				point[i] = cumputBillboardCoord(i);
				m_Point[i] = Convert::Vec4ToVec3(point[i]);
			}
		}*/
		Vertes[0].SetPosition(m_Point[0].x, m_Point[0].y, m_Point[0].z);
		Vertes[0].SetNormal(0, 0, 1);
		Vertes[0].SetColor(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);
		Vertes[0].SettextureCoord1(m_fTextureCoord[0][0], m_fTextureCoord[0][1]);
		Vertes[0].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
		Vertes[0].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);
		Vertes[0].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
		Vertes[0].ShaderIndex = fShaderIndex;
		
		Vertes[1].SetPosition(m_Point[1].x, m_Point[1].y, m_Point[1].z);
		Vertes[1].SetNormal(0, 0, 1);
		Vertes[1].SetColor(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);
		Vertes[1].SettextureCoord1(m_fTextureCoord[1][0], m_fTextureCoord[1][1]);
		Vertes[1].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
		Vertes[1].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);
		Vertes[1].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
		Vertes[1].ShaderIndex = fShaderIndex;
		
		Vertes[2].SetPosition(m_Point[2].x, m_Point[2].y, m_Point[2].z);
		Vertes[2].SetNormal(0, 0, 1);
		Vertes[2].SetColor(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);
		Vertes[2].SettextureCoord1(m_fTextureCoord[2][0], m_fTextureCoord[2][1]);
		Vertes[2].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
		Vertes[2].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);
		Vertes[2].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
		Vertes[2].ShaderIndex = fShaderIndex;
		
		Vertes[3].SetPosition(m_Point[3].x, m_Point[3].y, m_Point[3].z);
		Vertes[3].SetNormal(0, 0, 1);
		Vertes[3].SetColor(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);
		Vertes[3].SettextureCoord1(m_fTextureCoord[3][0], m_fTextureCoord[3][1]);
		Vertes[3].SetTransformPosition(Transform->Position.x, Transform->Position.y, Transform->Position.z);
		Vertes[3].SetTransformScale(Transform->Scale.x, Transform->Scale.y, Transform->Scale.z);
		Vertes[3].SetTransformRotate(Transform->RotationEuler.x, Transform->RotationEuler.y, Transform->RotationEuler.z);
		Vertes[3].ShaderIndex = fShaderIndex;
	}
	
	void Particle::RotateByDir(vec3f dir,float force)
	{
		if(dir.length() > 0.0f)
		{
			dir.y *= -1.0f;
			float tana = dir.x / dir.y;
			float a = atan(tana);
			if(dir.y > 0)
			{
				a += M_PI;
			}
            
            /*if(force < 1.0f)
            {
                a = m_rotateAngle + a*force;
            }*/
            float offset = a - m_rotateAngle;
            a = m_rotateAngle + offset*force;
            
			Transform->SetRotation(0, 0, a);
			SetRotateAngle(a);
		}
	}
	
	void Particle::move2Position(vec3f newPos)
	{
		
	}
	
	void Particle::Update(float deltaTime)
	{
		m_fTimeToLive -= deltaTime;
		
		if (m_FrameEffect != nullptr)
		{
			m_FrameEffect->Update(deltaTime);
		}
		updateVertexCoord();
	}

	uint * Particle::getIndices()
	{
		return Indices;
	}

	float Particle::getParticleTimeToLive() const
	{
		return m_fTimeToLive;
	}

	void Particle::SetScale(float scale)
	{
		float w = m_fWidth*scale;
		float h = m_fHeight*scale;
		m_Point[0] = vec3f(-w / 2, h / 2, 0);
		m_Point[1] = vec3f(-w / 2, -h / 2, 0);
		m_Point[2] = vec3f(w / 2, -h / 2, 0);
		m_Point[3] = vec3f(w / 2, h / 2, 0);
	}


	void Particle::SetTimeToLive(float totalTime)
	{
		m_fTotalTimeToLive = totalTime;
		m_fTimeToLive = m_fTotalTimeToLive;
	}


	void Particle::SetMoveDirction(vec3f direction)
	{
		m_vDirection = direction;
	}


	vec3f Particle::GetMoveDirection()
	{
		return m_vDirection;
	}

	void Particle::SetMoveSpeed(float speed)
	{
		m_fSpeed = speed;
	}


	float Particle::GetMoveSpeed()
	{
		return m_fSpeed;
	}


	vec3f Particle::GetReightVector()
	{
		return Convert::Vec4ToVec3<float>(m_Point[3] - m_Point[0]);
	}


	void Particle::SetCamera(Camera * camera)
	{
		m_MainCamera = camera;
	}


	float Particle::getLiveTime()
	{
		return m_fTotalTimeToLive - m_fTimeToLive;
	}


	float Particle::getTotleLiveTime()
	{
		return m_fTotalTimeToLive;
	}


	void Particle::setAlpha(float alpha)
	{
		m_fColor[3] = alpha;
	}


	float Particle::GetAlpha()
	{
		return m_fColor[3];
	}


	void Particle::SetRotateSpeed(float speed)
	{
		m_rotateSpeed = speed;
	}


	float Particle::GetRotateSpeed()
	{
		return m_rotateSpeed;
	}


	void Particle::SetRotateAngle(float Angle)
	{
		float a = Angle * 180 / M_PI;
		if (a > 360.0 || Angle < -360.0)
		{
			Angle = 0.0;
		}
		m_rotateAngle = Angle;
	}


	float Particle::GetRotateAngle()
	{
		return m_rotateAngle;
	}


	void Particle::StartEffect()
	{
		if (m_FrameEffect != nullptr && m_FrameEffect->IsParticleEffect)
		{
			m_FrameEffect->Play();
			m_FrameEffect->AddSource(this);
			vec2f uvpos = m_FrameEffect->GetTextureFrameCoord(0);
			SetTextureUVCoord(uvpos.x, uvpos.y, m_FrameEffect->GetTextureFrameScale());
		}
	}

	void Particle::SetRandomForceID(int ID)
	{
		m_RandomForceID = ID;
	}

	int Particle::GetRandomForceID()
	{
		return m_RandomForceID;
	}

	void Particle::SetBornEmitterPos(vec3f pos)
	{
		m_vBornEmitterPosition = pos;
	}

	vec3f Particle::GetBornEmitterPos()
	{
		return m_vBornEmitterPosition;
	}

	void Particle::SetBornPos(vec3f pos)
	{
		m_vBornPosition = pos;
	}

	vec3f Particle::GetBornPos()
	{
		return m_vBornPosition;
	}

	vec2f Particle::GetUVCenter()
	{
		return m_uv + m_wh / 2;
	}

	void Particle::ActiveEffect(TextureUVConfig * cfg)
	{
		m_FrameEffect->Init(*cfg);
	}


	ParticleGroup::ParticleGroup()
	{
		m_particleIndex		= 0;
		m_pMaterial			= nullptr;
		m_bIsPause			= false;
		m_nColor			= 0xffffffff;
		beGetFromLocalPool	= false;
		bIsEnable			= true;
		bLockEnable			= false;
		CreateBehaviour();
	}

	void ParticleGroup::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(ParticleGroup);
		m_pBehaviour->Awake();
		GameObject::setBehaviourDefaultValue();
	}

	ParticleGroup::~ParticleGroup()
	{
		clearParticle2DeathPool(true);
		m_vecUVConfigs.clear();
		for (auto & emitter : m_particleEmitters)
		{
			SAFE_DELETE(emitter);
		}
		m_particleEmitters.clear();
		for (auto & affector : m_particleAffectors)
		{
			SAFE_DELETE(affector);
		}
		m_particleAffectors.clear();
	}
	
	void ParticleGroup::CleaParticle()
	{
		if (m_pRenderer != nullptr)
		{
			static_cast<Renderer*>(m_pRenderer)->RemoveInRenderer(ID);
		}
	}
	
	share_pointer<Particle> ParticleGroup::createParticle()
	{
		if (m_DethParticles.empty())
		{
			return share_pointer<Particle>::null();
		}
		share_pointer<Particle> p = m_DethParticles.front();
		m_DethParticles.pop_front();
		return p;
	}
	
	bool ParticleGroup::activeParticleFromDeath(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID,vec3f bornEmitterPos)
	{
		share_pointer<Particle> p = createParticle();
		if (p != share_pointer<Particle>::null() && p.getReferenceCount() != 0)
		{
			p.get_ptr()->GroupID = groupID;
			p.get_ptr()->StartEffect();
			p.get_ptr()->SetTimeToLive(time2Live);
			p.get_ptr()->SetColor(m_nColor);
			p.get_ptr()->SetSize(size);
			p.get_ptr()->SetMoveSpeed(0);
			p.get_ptr()->setAlpha(color);
			p.get_ptr()->Transform->SetPosition(pos);
			p.get_ptr()->SetBornEmitterPos(bornEmitterPos);
			p.get_ptr()->bFristUpdte = true;
			p.get_ptr()->ResetFrameEffect();
			m_ActiveParticles.push_back(p);
			return true;
		}
		return false;
	}
	
	void ParticleGroup::clearParticle2DeathPool(bool beDelete)
	{
		beGetFromLocalPool = false;
		if (m_ParticlePool.empty())
		{
			return;
		}
		if (!beDelete)
		{
			if (m_pRenderer == nullptr)
			{
				return;
			}
			static_cast<Renderer*>(m_pRenderer)->RemoveInRenderer(ID);
		}
		ParticlePool::GetInstance().DeleteParticleToDeathPool(m_ParticlePool);
		m_ParticlePool.clear();
		m_ActiveParticles.clear();
		m_DethParticles.clear();
	}
	
	void ParticleGroup::SetActive(bool isActive)
	{
		if (isActive == IsActive)
		{
			return;
		}
		IsActive = isActive;
		if (isActive)
		{
			createVetexIndex();
		}
		else
		{
			if (m_pRenderer != nullptr)
			{
				static_cast<Renderer*>(m_pRenderer)->RemoveInRenderer(ID);
			}
		}
		GameObject::SetActive(isActive);
	}
	
	std::vector<ParticleEmitter*> * ParticleGroup::GetEmitter()
	{
		return &m_particleEmitters;
	}

	std::vector<ParticleAffector*> * ParticleGroup::GetAffector()
	{
		return &m_particleAffectors;
	}

	void ParticleGroup::SetRenderer(Renderer * buffer)
	{
		m_pRenderer = buffer;
		m_pMaterial = buffer->GetMaterial();
		m_pMaterial->SetEnableDepthWrite(false);
		SceneManager::GetInstance().GetCurrentScene()->AddRenderObject(m_pRenderer, m_layerMask);
		m_pRenderer->CreateNewTransform();
		SetRenderIndex(eRI_TopMost);
		m_pRenderer->GetTransform()->SetIsBillBoard(true);
	}
	
	void ParticleGroup::SetCamera(Camera * camera)
	{
		pCamera = camera;
		m_pRenderer->SetCamera(camera);
	}
	
	void ParticleGroup::CreateParticle(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID,vec3f bornEmitterPos, bool isFirstCreate)
	{
		if (beGetFromLocalPool && !m_ParticlePool.empty())
		{
			createParticleFromDethPool(particleNumber, time2Live, pos, size, color, groupID, bornEmitterPos, particleNumber);
		}
		else
		{
			if (isFirstCreate)
			{
				initCfg = particleInitConfig(particleNumber, time2Live, pos, size, color, groupID, bornEmitterPos, true);
			}
			createParticleFromPool(initCfg.ParticleNumber, initCfg.Size, initCfg.Color, initCfg.Pos, initCfg.Time2Live, initCfg.GroupID, initCfg.BornEmitterPos, initCfg.IsFirstCreate);
			createVetexIndex();
			bIsEnable = true;
			if (!isFirstCreate)
			{
				createParticleFromDethPool(particleNumber, time2Live, pos, size, color, groupID, bornEmitterPos, particleNumber);
			}
		}
	}
	
	void ParticleGroup::SetMaxParticleNumber(UINT number)
	{
		m_uiMaxParticleNumber = number;
	}


	std::list<E3DEngine::share_pointer<E3DEngine::Particle>> * ParticleGroup::GetActiveParticles()
	{
		return &m_ActiveParticles;
	}


	void ParticleGroup::UpdateRefrence(int number)
	{
		m_nRefrence += number;
	}


	int ParticleGroup::GetRefrence()
	{
		return m_nRefrence;
	}


	void ParticleGroup::SetTextureIndex(int index)
	{
		m_nTextureIndex = index;
	}


	void ParticleGroup::SetfShaderIndex(int index)
	{
		fShaderIndex = index;
	}

	void ParticleGroup::AddParticleEmitter(E3DEngine::ParticleEmitter *emitter)
	{
		m_particleEmitters.push_back(emitter);
	}
	
	void ParticleGroup::AddParticleAffector(ParticleAffector * affector)
	{
		m_particleAffectors.push_back(affector);
	}
	
	void ParticleGroup::createVetexIndex()
	{
		if (m_pRenderer == nullptr)
		{
			return;
		}
		static_cast<Renderer*>(m_pRenderer)->RemoveInRenderer(ID);
		// 初始化粒子团内的所有粒子
		int ivertexTotal = 0;
		int iindexTotal = 0;
		Renderer * render = static_cast<Renderer*>(m_pRenderer);;
		render->RecordCurrentVextexStartIndex(ID);
		render->RecordCurrentIndexStartIndex(ID);
		

		for (share_pointer<Particle> &it : m_ParticlePool)
		{
			if (it.getReferenceCount() == 0)
			{
				continue;
			}
			Vertex *vertex = it.get_ptr()->getVertex(Transform->WorldMatrix);
			for (int vi = 0; vi < 4; vi++)
			{
				// TODO
				render->FillVertex(vertex[vi]);
			}
			// 4 个顶点有 6个索引,
			uint * index = it.get_ptr()->getIndices();
			for (int ii = 0; ii < 6; ii++)
			{
				uint idx = index[ii] + ivertexTotal;
				// TODO
				render->FillIndex(idx);
				iindexTotal++;
			}
			ivertexTotal += 4;
		}
		render->FillEnd();
		render->VertexCountAdd(ID, (DWORD)ivertexTotal);
		render->IndexCountAdd(ID, (DWORD)iindexTotal);
	}
	
	void ParticleGroup::TransformChange()
	{
		//m_pRenderer->SetTransform(Transform);		
		for (auto & emitter : m_particleEmitters)
		{
			emitter->SetEmitterPosition(Transform->Position);
		}
		m_pRenderer->TransformChange();
	}

	void ParticleGroup::UpdateParticles(float deltaTime)
	{
		if (static_cast<Renderer*>(m_pRenderer)->GetRendererBuffer(ID) == nullptr)
		{
			return;
		}

		m_ActiveParticles.sort([=] (share_pointer<Particle> &p1, share_pointer<Particle>&p2)
		{
			float dis1 = abs(m_pRenderer->pCamera->Transform->Position.Distance(p1.get_ptr()->Transform->Position));
			float dis2 = abs(m_pRenderer->pCamera->Transform->Position.Distance(p2.get_ptr()->Transform->Position));
			return dis1 > dis2;
		});

		vertexStartIndex = static_cast<Renderer*>(m_pRenderer)->GetRendererBuffer(ID)->VertextStartIndex;
		for (particleListIterator it = m_ActiveParticles.begin(); it != m_ActiveParticles.end();)
		{
			share_pointer<Particle> particle = *it;
			if (particle.getReferenceCount() == 0)
			{
				it ++;
				continue;
			}
			Particle *p = particle.get_ptr();
			if (p == nullptr)
			{
				it ++;
				continue;
			}
			if(p->getLiveTime() > 0.0f)
			{
				it ++;
				continue;
			}
			for (auto & m_particleAffector : m_particleAffectors)
			{
				if (particle.get_ptr()->GroupID != m_particleAffector->particleGroupID)
				{
					continue;
				}
				m_particleAffector->AffectParticle(deltaTime, particle);
			}
			
			float livetime = p->getParticleTimeToLive() - deltaTime;
			
			if (livetime <= 0)
			{
				particle.get_ptr()->Transform->Position = FAR_AWAY;
				it = deleteParticle(it);
			}
			else
			{
				it ++;
			}
			p->Update(deltaTime);
			Vertex * vertex = p->getVertex(Transform->WorldMatrix);
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + p->Index * 4 + 0] = vertex[0];
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + p->Index * 4 + 1] = vertex[1];
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + p->Index * 4 + 2] = vertex[2];
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + p->Index * 4 + 3] = vertex[3];
		}
	}
	
	void ParticleGroup::checkParticleState(float deltaTime)
	{
		for (auto & m_particleEmitter : m_particleEmitters)
		{
			m_particleEmitter->Update(deltaTime);
		}		
		
		m_ActiveParticles.sort([=](share_pointer<Particle> &p1, share_pointer<Particle>&p2)
		{
			float dis1 = abs(m_pRenderer->pCamera->Transform->Position.Distance(p1.get_ptr()->Transform->Position));
			float dis2 = abs(m_pRenderer->pCamera->Transform->Position.Distance(p2.get_ptr()->Transform->Position));
			return dis1 > dis2;
		});

		vertexStartIndex = static_cast<Renderer*>(m_pRenderer)->GetRendererBuffer(ID)->VertextStartIndex;
		//Debug::Log(ell_Error, "Particle Number is %d", m_ActiveParticles.size());
		for (particleListIterator itr = m_ActiveParticles.begin(); itr != m_ActiveParticles.end();)
		{
			share_pointer<Particle> particle = *itr;
			if (particle.getReferenceCount() == 0)
			{
				itr ++;
				continue;
			}
			if (particle.get_ptr() == nullptr)
			{
				itr ++;
				continue;
			}
			for (auto & m_particleAffector : m_particleAffectors)
			{
				if (particle.get_ptr()->GroupID != m_particleAffector->particleGroupID)
				{
					continue;
				}
				m_particleAffector->AffectParticle(deltaTime, particle);
			}
			
			float livetime = particle.get_ptr()->getParticleTimeToLive() - deltaTime;
			
			if (livetime <= 0)
			{
				particle.get_ptr()->Transform->Position = FAR_AWAY;
				deleteParticle(itr);
			}
			else
			{
				itr ++;
			}
			particle.get_ptr()->SetCamera(m_pRenderer->pCamera);
			particle.get_ptr()->Update(deltaTime);
			Vertex * vertex = particle.get_ptr()->getVertex(Transform->WorldMatrix);
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + particle.get_ptr()->Index * 4 + 0] = vertex[0];
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + particle.get_ptr()->Index * 4 + 1] = vertex[1];
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + particle.get_ptr()->Index * 4 + 2] = vertex[2];
			static_cast<Renderer*>(m_pRenderer)->Vertices[vertexStartIndex + particle.get_ptr()->Index * 4 + 3] = vertex[3];
		}
		if (m_ActiveParticles.empty() && !bIsEnable )
		{
			clearParticle2DeathPool();
			ParticleFactory::GetInstance().ResumParticleGroup(ConfigName, this);
		}
	}
	
	void ParticleGroup::SetEmitterEnable(bool isEnable)
	{
		bIsEnable = isEnable;
		for (auto & m_particleEmitter : m_particleEmitters)
		{
			m_particleEmitter->SetEnable(isEnable);
		}
		
		if (isEnable && !beGetFromLocalPool)
		{
			CreateParticle(initCfg.ParticleNumber, initCfg.Time2Live, initCfg.Pos, initCfg.Size, initCfg.Color, initCfg.GroupID, initCfg.BornEmitterPos, initCfg.IsFirstCreate);
		}
		
		if (isEnable && !IsActive)
		{
			SetActive(true);
		}
	}
	
	void ParticleGroup::SetPause(bool bPause)
	{
		m_bIsPause = bPause;
	}

	particleListIterator ParticleGroup::deleteParticle(particleListIterator& pItr)
	{
		share_pointer<Particle> particle = *pItr;
		if (m_ActiveParticles.size() == 0)
		{
			return pItr;
		}
		if (particle.getReferenceCount() == 0)
		{
			return ++pItr;
		}
		m_DethParticles.emplace_back(particle);
		particle.get_ptr()->ReSet();
		particle.get_ptr()->SetColor(m_nColor);
		for (auto & m_particleEmitter : m_particleEmitters)
		{
			if(m_particleEmitter->m_CurrentParticleNumer > 0)
				m_particleEmitter->m_CurrentParticleNumer--;
		}
		pItr = m_ActiveParticles.erase(pItr);
		return pItr;
	}
	
	void ParticleGroup::AfterUpdate(float deltaTime)
	{
		if (m_bIsPause)
		{
			return;
		}
		if (IsActive && !m_ParticlePool.empty())
		{
			makeBillboard();
			/*Camera * pCamera = m_pRenderer->pCamera;
			if (pCamera == nullptr)
			{
				return;
			}
			vec3f cameraPos = pCamera->Transform->Position;
			mat4f view = pCamera->GetViewMatrix();
			view.at(3, 0) = 0;
			view.at(3, 1) = 0;
			view.at(3, 2) = 0;
			view = view.inverse();
			m_pRenderer->GetTransform()->WorldMatrix = view;*/
			checkParticleState(deltaTime);
			m_pRenderer->TransformChange();
		}
	}
	
	void ParticleGroup::makeBillboard()
	{
		Camera * pCamera = m_pRenderer->pCamera;
		if (pCamera == nullptr)
		{
			return;
		}
		vec3f pos = m_pRenderer->GetTransform()->Position;
		vec3f cameraPos = pCamera->Transform->Position;

		vec3f forward = pos - cameraPos;
		forward.normalize();

		vec3f up = vec3f(0.0, 1.0, 0.0);
		up.normalize();

		vec3f side = forward.crossProduct(up);
		side.normalize();


		m_pRenderer->GetTransform()->WorldMatrix.identity();

		m_pRenderer->GetTransform()->WorldMatrix.data[0] = side.x; m_pRenderer->GetTransform()->WorldMatrix.data[1] = side.y; m_pRenderer->GetTransform()->WorldMatrix.data[2] = side.z;
		m_pRenderer->GetTransform()->WorldMatrix.data[4] = up.x;  m_pRenderer->GetTransform()->WorldMatrix.data[5] = up.y;  m_pRenderer->GetTransform()->WorldMatrix.data[6] = up.z;
		m_pRenderer->GetTransform()->WorldMatrix.data[8] = forward.x; m_pRenderer->GetTransform()->WorldMatrix.data[9] = 0; m_pRenderer->GetTransform()->WorldMatrix.data[10] = forward.z;

		mat4f tranM = mat4f::createTranslation(pos.x, pos.y, pos.z);

		mat4f result = m_pRenderer->GetTransform()->WorldMatrix;
		m_pRenderer->GetTransform()->WorldMatrix = tranM * result;
	}

	void ParticleGroup::SetParticleDir(vec3f TouchPos, vec3f EmitterPos)
	{
		if(m_isLock > 0)
		{
			vec3f d = vec3f(TouchPos.x, 0.0, 0.0);
			vec3f up = vec3f(0.0f, EmitterPos.y*m_DirOffset, 0.0f);
			m_ParticleDir = d - up;
		}
		else
		{
			//printf("TouchPos x:%f,y:%f   EmitterPos x:%f,y:%f\n",TouchPos.x,TouchPos.y,EmitterPos.x,EmitterPos.y);
			if(EmitterPos != TouchPos)
				m_ParticleDir = EmitterPos - TouchPos;
			else
				m_ParticleDir = vec3f(0.0f,0.0f,0.0f);
		}
		m_EmitterPositon = EmitterPos;
		m_ParticleDir.normalize();
	}
	
	void ParticleGroup::ParseUVConfig(std::string uvStr)
	{
		std::vector<std::string> uvVec = StringBuilder::Split(uvStr, ",");
		for (auto & i : uvVec)
		{
			std::string uvID = StringBuilder::Trim(i);
			if (uvID == "")
			{
				continue;
			}
			int id = Convert::ToInt(uvID);
			
			TextureUVConfig * config = EngineDelegate::GetInstance().GetTableManager(ConfigName)->Select<TextureUVConfig>(id);
			if (config == nullptr)
			{
				continue;
			}
			
			m_vecUVConfigs.push_back(config);
		}
	}
	
	void ParticleGroup::SetDontDestory(bool dontDestory)
	{
		DontDestoryOnLoad = dontDestory;
	}
	
	void ParticleGroup::createParticleFromPool(int createParticleNumber, Vector2 &size, float color, vec3f pos, float time2Live, uint groupID, vec3f bornEmitterPos, bool isFirstCreate)
	{
		m_particleIndex = 0;
		for (int i = 0; i < createParticleNumber; i++)
		{
			size_t num = m_vecUVConfigs.size();
			int _n = rand() % num;
			
			share_pointer<Particle> sp_P = ParticlePool::GetInstance().ActiveParticleFromPool();

			sp_P.get_ptr()->ActiveEffect(m_vecUVConfigs[_n]);
			sp_P.get_ptr()->Create(size.x, size.y, true, color, pos, fShaderIndex, time2Live);
			sp_P.get_ptr()->autoRelease();
			sp_P.get_ptr()->GroupID = groupID;
			sp_P.get_ptr()->Index = m_particleIndex;
			sp_P.get_ptr()->SetColor(m_nColor);
			sp_P.get_ptr()->SetMoveSpeed(0);
			sp_P.get_ptr()->SetCamera(pCamera);
			sp_P.get_ptr()->setAlpha(color);
			sp_P.get_ptr()->SetBornEmitterPos(bornEmitterPos);
			m_ParticlePool.emplace_back(sp_P);
			if (isFirstCreate)
			{
				/// 创建足够的粒子放入死亡列表里
				m_DethParticles.emplace_back(sp_P);
			}
			else
			{
				m_ActiveParticles.emplace_back(sp_P);
			}
			m_particleIndex++;
		}
		beGetFromLocalPool = true;
	}
	
	void ParticleGroup::createParticleFromDethPool(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID, vec3f bornEmitterPos, int createParticleNumber)
	{
		if (m_ParticlePool.size() >= m_uiMaxParticleNumber)
		{
			int particleCreatedNumber = 0;
			// 从死亡粒子池取粒子
			for (int i = 0; i < particleNumber; i++)
			{
				activeParticleFromDeath(particleNumber, time2Live, pos, size, color, groupID, bornEmitterPos);
			}
		}
	}
	
	
}
