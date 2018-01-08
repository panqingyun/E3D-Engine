//
//  ZZEffect3DTextureFrameAnimation.hpp
//
//  Created by 潘庆云 on 2017/5/16.
//

#ifndef ZZEffect3DTextureFrameAnimation_hpp
#define ZZEffect3DTextureFrameAnimation_hpp

#include "../Object/E3DRenderObject.hpp"
#include "../Source/E3DTimer.hpp"
#include "../Config/Table.h"
#include "E3DEffect.hpp"

using namespace E3DEngine;

struct TextureFrameConfig implement E3DEngine::IObject
{
	std::string image;
	float		speed;				// 序列帧播放速度
	int			repeatStartFrame;	// 循环开始索引
	int			type;				// 拼图类别  0:表示行列都是规则的序列
	bool		isReverse;			// 是否倒序，即正序播放，然后倒序播放
	int			leftRightMirror;	// 左右对称，1表示正常；-1表示左右对称
	int			topBottomMirror;	// 上下对称，1表示正常；-1表示上下对称
	DWORD		widthTexture;		// 纹理宽度，即大图宽度
	DWORD		heightTexture;		// 纹理高度，即大图高度
	DWORD		widthPic;			// 单帧图片宽度(像素)，不规则拼图时必填
	DWORD		heightPic;			// 单帧图片高度(像素)，不规则拼图时必填
	DWORD		startX;				// 开始UV的X(像素)，不规则拼图时必填
	DWORD		startY;				// 开始UV的Y(像素)，不规则拼图时必填
	float       postponeTime;
	float		duration;
	
	std::vector<vec2d> framePos;	// 序列帧位置数组

	TextureFrameConfig();
	TextureFrameConfig & operator = (TextureFrameConfig &cfg);
	TextureFrameConfig(TextureFrameConfig &cfg);
	
	void Copy(TextureFrameConfig &cfg);	
};

enum
{
	eFrameNormal = 0,
	eFrameTrig = 1,
};

namespace E3DEngine
{
	class TextureFrameEffect extends Component
	{
	public:
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;
	public:
		TextureFrameEffect();
		~TextureFrameEffect();
		void Init(TextureFrameConfig cfg);
		void Init(TextureUVConfig cfg );
		virtual void Play(float postponeTime = 0, float duration = 0); // duration = 0 表示 播完一帧就结束 postponeTime 延迟时间
		virtual bool Stop(bool now = false);
		virtual void ReSet();

	public:
		vec2f GetTextureFrameCoord(int frame);
		vec2f ShowNextFrame();
		vec2f ShowFirstFrame();
		DWORD GetStateType();
		vec2f GetTextureFrameScale();

	public:
		void  PostponeShowNextFrame(); // 延迟播放下到一帧
		void  PostponePlay();
		void  ShowNullFrame();
		bool  CanStop();
		void  StopPostponeTimer();
		void  Pause();
		bool  GetIsPlay();
		void  SetStateType(DWORD stateType);
		void  AddSource(IActor * s);

	protected:
		virtual void playInFrame(float deltaTime);
		
		vec2f computeCurrentFramePosition();
		void  activeChange(IObject * sender, EventArgs *e);
		void postponeTextureFrame(IObject * _sender, EventArgs *_e);
		void initFrame();

	private:
		vec2f m_FrameStartPos;				// 帧起始坐标
		vec2f m_FrameSize;					// 纹理尺寸
		vec2f m_TextureScale;				// 纹理缩放

		float m_fTimeLongOneFrame;			// 每帧的时间长度
		float m_fCurrentFrameHasPlayTime;	// 当前帧已播放时长
		float m_fTotalColumn;				// 图片的宽度是所需宽度的多少倍
		float m_fTotalRow;					// 图片的高度是所需高度的多少倍
		float m_totalPlayTime;

		int   m_nCurrentPos;				// 当前播放到第几帧
		int   m_nEndFrameNumber;
		int	  m_nStartFrameNumber;
		int   m_postponeTimerID;

		bool  m_bPlayInReverse;				// 是否在倒序播放
		bool  m_bIsPlay;
		bool  m_bIsLoop;
		bool  m_bIsFirstPlay;

		DWORD			m_StateType;
		RenderObject *	m_RenderObject;
		IActor *		pActor;
		TextureFrameConfig * m_pConfig;

	public:
		bool  IsAutoPlay;
		bool  IsParticleEffect;
		
	};
}

#endif /* ZZEffect3DTextureFrameAnimation_hpp */
