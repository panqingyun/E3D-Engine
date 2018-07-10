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
	class Renderer;
    class Camera;
    class ParticleAffector;
    class ParticleEmitter;
	class Particle : public Ref , public IActor
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
        float * GetColor()
        {
            return m_fColor;
        }
		void ActiveEffect(TextureUVConfig * cfg);

	public:
		virtual void EffectFrameChange(IObject * sender, EventArgs * e) override;
		virtual void EffectEnd(IObject * sender, EventArgs * e)			override;
		virtual void PlayDurationEnd(IObject * sender, EventArgs * e)	override;

    public:
        eParticleLiveState	getParticleState() const;
        void				setParticleState(eParticleLiveState state);
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
        void				SetCamera(Camera * camera);
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
		vec4f	cumputBillboardCoord(int index);
		void    initVertex();

    private:
        int     m_RandomForceID;
        float	m_fWidth;                     // 宽度
        float	m_fHeight;                    // 高度
        bool	m_bOwnDimension;               // 是否可控制粒子大小
        float	m_fColor[4];                  // 当前颜色（通常指顶点颜色 R G B A）
        vec3f	m_vDirection;                 // 方向
        vec3f   m_vBornEmitterPosition;
        vec3f   m_vBornPosition;
        float	m_fSpeed;                     // 速度
        vec3f		m_Point[4];
        BatchVertex BVertes[4];
		Vertex		Vertes[4];
        uint		Indices[6];
        long		m_nCurrentColor;
        float		m_fTextureCoord[4][2];
        float		m_fTimeToLive;                // 剩余生命
        float		m_fTotalTimeToLive;           // 生命周期
        Quatf		m_qQuat;
        vec3f		m_rotateAxis;
        float		m_rotateAngle;
        float		m_rotateSpeed;
        bool		m_bIsBillBoard;
        float		rudis;
        vec3f		m_vRight;
        vec3f		m_vUp;
        eParticleLiveState		m_eParticleState;
        Camera		*	m_MainCamera;
        vec2f		m_NotChangeTextureCoord[4];
        TextureFrameEffect * m_FrameEffect;
        vec2f       m_uv;
        vec2f       m_wh;
        int			fShaderIndex;
    };

	struct particleInitConfig 
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

		particleInitConfig(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID, vec3f bornEmitterPos, bool isFirstCreate = false)
		{
			ParticleNumber = particleNumber;
			Time2Live = time2Live;
			Pos = pos;
			Size = size;
			Color = color;
			GroupID = groupID;
			BornEmitterPos = bornEmitterPos;
			IsFirstCreate = isFirstCreate;
		}
	};

    class ParticleGroup : public GameObject
    {
    public:
        ParticleGroup();
        virtual ~ParticleGroup() override;
		int	 GetRefrence();
        void UpdateRefrence(int number);
        void SetTextureIndex(int index);
		void SetfShaderIndex(int index);
		void CreateParticle(unsigned int particleNumber, float time2Live, vec3f pos, Vector2 size, float color, uint groupID, vec3f bornEmitterPos, bool isFirstCreate = false);
		
		virtual void TransformChange() override;
		virtual void CreateBehaviour() override;
		std::list<share_pointer<Particle>> *GetActiveParticles();
	public:
        void	AddParticleEmitter(ParticleEmitter * emitter);
        void	AddParticleAffector(ParticleAffector * affector);
		void	SetRenderer(Renderer* buffer);
        void	SetEmitterEnable(bool isEnable);
		void	SetPause(bool bPause);
        void			ParseUVConfig(std::string uvStr);
        void			CleaParticle();
		void            UpdateParticles(float deltaTime);
		void			SetParticleDir(vec3f TouchPos, vec3f EmitterPos);
		void			SetParticleSize(vec2f size) { pSzie = size; }
		virtual void	SetMaxParticleNumber(UINT number);
		virtual void	SetCamera(Camera * camera) override;
		virtual void	AfterUpdate(float deltaTime) override;

		void makeBillboard();

		virtual void	SetDontDestory(bool dontDestory) override;
		virtual void	SetActive(bool isActive) override;

		std::vector<ParticleEmitter*> *  GetEmitter();
		std::vector<ParticleAffector*> * GetAffector();
    public:
        int				m_isLock;
        Material		* m_pMaterial;
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
        UINT	m_nRefrence;   // 引用粒子团的发射器和影响器的计数，当引用值是0的时候 删除这个粒子团
        UINT	m_uiMaxParticleNumber;
        int		m_nTextureIndex;
        bool    m_bIsBlendONE;
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
