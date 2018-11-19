//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-17  PanQingyun. All rights reserved. ************************//

#ifndef Particle_h
#define Particle_h

#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DTransform.hpp"
#include "../Config/Table.h"
#include "E3DParticlePool.h"
#include "../Source/E3DVertex.h"

typedef enum
{
	eps_Active = 0,
	eps_Deth = 1,
} eParticleLiveState;

namespace E3DEngine
{
	class TextureFrameEffect;
	class BatchRenderer;
    class ParticleAffector;
    class ParticleEmitter;
	class E3D_EXPORT_DLL Particle : public Ref , public IActor
    {
    public:
        Particle();
		void Create(float width, float height, bool ownDimension, float color, vec3f position, int fsIndex,float time2Live);
		
		void SetDimension(float width, float height); // 设置粒子大小
        void Update(float deltaTime);
        void SetColor(float r, float g, float b);
        void SetColor(long color); // 16 进制颜色值
        void SetColor(float r, float g, float b, float a);
        void ReSet();
        virtual ~Particle() override;
        float * GetColor();
		void ActiveEffect(TextureUVConfig * cfg);

	public:
		virtual void EffectFrameChange(IObject * sender, EventArgs * e) override;
		virtual void EffectEnd(IObject * sender, EventArgs * e)			override;
		virtual void PlayDurationEnd(IObject * sender, EventArgs * e)	override;

    public:
        Vertex *			getVertex(mat4f worldMatrix);
		BatchVertex *		getBatchVertex();
        uint *				getIndices();
        float				getParticleTimeToLive() const;
        void				SetSize(Vector2 size);
        void				SetScale(float scale);
        void				SetTimeToLive(float totalTime);
        void				SetMoveDirction(vec3f direction);
        vec3f				GetMoveDirection();
        void				SetMoveSpeed(float speed);
        float				GetMoveSpeed();
        vec3f				GetReightVector();
        float				getLiveTime();
        float				getTotleLiveTime();
        
        void				setAlpha(float alpha);
        float				GetAlpha();
        void				SetRotateSpeed(float speed);
        float				GetRotateSpeed();
        void				SetRotateAngle(float Angle);
        float				GetRotateAngle();
		void				StartEffect();

	public:
        void	SetRandomForceID(int ID);        
        int		GetRandomForceID();        
        void	SetBornEmitterPos(vec3f pos);        
        vec3f	GetBornEmitterPos();        
        void	SetBornPos(vec3f pos);        
        vec3f	GetBornPos();        
        vec2f	GetUVCenter();        
        void	SetTextureUVCoord(float x, float y, vec2f scale);
        void	SetTextureUVCoord(vec2f uv, vec2f wh);
        void	ResetTextureUVCoord(float whscale);
        void	ResetFrameEffect();
        void	RotateByDir(vec3f dir,float force = 1.0f);

    public:
        CTransform * Transform;
        uint		 Index;
        uint		 GroupID;
        bool         bFristUpdte;

    private:
        void	updateVertexCoord();
        void	move2Position(vec3f newPos);
		void    initVertex();

    private:
        int     m_RandomForceID;
        float	m_fWidth;                     // 宽度
        float	m_fHeight;                    // 高度
        float	m_fColor[4];                  // 当前颜色（通常指顶点颜色 R G B A）
        vec3f	m_vDirection;                 // 方向
        vec3f   m_vBornEmitterPosition;
        vec3f   m_vBornPosition;
        float	m_fSpeed;                     // 速度
        vec3f		m_Point[4];
        BatchVertex BVertes[4];
		Vertex		Vertes[4];
        uint		Indices[6];
        float		m_fTextureCoord[4][2];
        float		m_fTimeToLive;                // 剩余生命
        float		m_fTotalTimeToLive;           // 生命周期
        float		m_rotateAngle;
        float		m_rotateSpeed;
        vec2f		m_NotChangeTextureCoord[4];
        TextureFrameEffect * m_FrameEffect;
        vec2f       m_uv;
        vec2f       m_wh;
        int			fShaderIndex;
    };

	struct E3D_EXPORT_DLL particleInitConfig
	{
		unsigned int ParticleNumber;
		float Time2Live;
		vec3f Pos;
		Vector2 Size;
		float Color;
		uint GroupID;
		vec3f BornEmitterPos;
		bool IsFirstCreate;
		particleInitConfig()
		{

		}

		particleInitConfig(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID, vec3f bornEmitterPos, bool isFirstCreate = false);
	};

    class E3D_EXPORT_DLL ParticleGroup : public GameObject
    {
    public:
        ParticleGroup();
        virtual ~ParticleGroup();
		void SetfShaderIndex(int index);
		void CreateParticle(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID, vec3f bornEmitterPos, bool isFirstCreate = false);
		
		virtual void TransformChange() override;
		std::list<share_pointer<Particle>> *GetActiveParticles();
	public:
        void	AddParticleEmitter(ParticleEmitter * emitter);
        void	AddParticleAffector(ParticleAffector * affector);
		void	SetRenderer(BatchRenderer* buffer);
        void	SetEmitterEnable(bool isEnable);
		void	SetPause(bool bPause);
        void			ParseUVConfig(std::string uvStr);
        void			CleaParticle();
		void            UpdateParticles(float deltaTime);
		void			SetParticleDir(vec3f TouchPos, vec3f EmitterPos);
		void			SetParticleSize(vec2f size) { pSzie = size; }
		virtual void	SetMaxParticleNumber(UINT number);
		virtual void	AfterUpdate(float deltaTime) override;
		virtual void	SetDontDestory(bool dontDestory) override;
		virtual void	SetActive(bool isActive) override;

		int				GetVertexSize();
		std::vector<ParticleEmitter*> *  GetEmitter();
		std::vector<ParticleAffector*> * GetAffector();
    public:
        int				m_isLock;
        uint			ParticleID; // 唯一的ID
        string			m_MaterialName;
        int				ParticleConfigID;
        vec3f           m_ParticleDir;
        float           m_DirOffset;
        vec3f           m_EmitterPositon;
		std::string		LayerName;
		std::string		ConfigName;

    private:
        void		createVetexIndex();
        void		checkParticleState(float deltaTime);

        bool		activeParticleFromDeath(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID,vec3f bornEmitterPos);
		void		clearParticle2DeathPool(bool bDelete = false);
		void		createParticleFromPool(int createParticleNumber, Vector2 &size, float color, vec3f pos, float time2Live, uint groupID, vec3f bornEmitterPos, bool isFirstCreate);
		void		createParticleFromDethPool(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID, vec3f bornEmitterPos, int createParticleNumber);

		particleListIterator		deleteParticle(particleListIterator& pItr);
		share_pointer<Particle>	    createParticle();

    private:
		float					_currentRotation;
		std::list<share_pointer<Particle>>  m_ParticlePool;
		std::list<share_pointer<Particle>>	m_ActiveParticles;
		std::list<share_pointer<Particle>>	m_DethParticles;
        std::vector<ParticleEmitter*>	m_particleEmitters;
		std::vector<ParticleAffector*>	m_particleAffectors;
		std::vector<TextureUVConfig*>	m_vecUVConfigs;
		particleInitConfig				initCfg;
        UINT	m_uiMaxParticleNumber;
        uint			m_particleIndex;
        long			m_nColor;
        uint			vertexStartIndex;
        bool			m_bIsPause;
        int				fShaderIndex;
		bool			beGetFromLocalPool;
		bool			bIsEnable;
		bool			bLockEnable;
		vec2f			pSzie;
    };
    
}
#endif
