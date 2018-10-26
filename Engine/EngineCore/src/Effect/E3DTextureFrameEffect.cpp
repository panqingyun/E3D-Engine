//
//  ZZEffect3DTextureFrameAnimation.cpp
//
//  Created by 潘庆云 on 2017/5/16.
//

#include "E3DTextureFrameEffect.hpp"

namespace E3DEngine
{

	TextureFrameEffect::~TextureFrameEffect()
	{
		SAFE_DELETE(m_pConfig);
	}

	void TextureFrameEffect::Init(TextureFrameConfig cfg)
	{
		m_bPlayInReverse = false;
		m_bIsPlay		 = false;
		m_pConfig->Copy(cfg);
		initFrame();
	}
	
	void TextureFrameEffect::initFrame()
	{
		if (m_pConfig->type == -1)
		{
			Stop(true);
			return;
		}
		if (m_pConfig->type == 0)
		{// 规则序列帧
			m_fTotalRow		 = m_pConfig->heightTexture / m_pConfig->heightPic;
			m_fTotalColumn	 = m_pConfig->widthTexture / m_pConfig->widthPic;
		}
		else
		{// 不规则
			m_FrameStartPos.x	= (float)m_pConfig->startX / (float)m_pConfig->widthTexture;
			m_FrameStartPos.y	= (float)m_pConfig->startY / (float)m_pConfig->heightTexture;
			m_fTotalRow			= (float)m_pConfig->heightTexture / (float)m_pConfig->heightPic;
			m_fTotalColumn		= (float)m_pConfig->widthTexture / (float)m_pConfig->widthPic;
		}
		m_fTimeLongOneFrame = 1.0 / m_pConfig->speed;
		m_TextureScale.x	= 1.0 / m_fTotalColumn * m_pConfig->leftRightMirror;
		m_TextureScale.y	= 1.0 / m_fTotalRow * m_pConfig->topBottomMirror;
		if (!IsParticleEffect)
		{
			
		}
		if (mGameObject != nullptr)
		{
//			mGameObject->ActiveChangeEvent += EventHandler(&TextureFrameEffect::activeChange, this);
		}
		m_nCurrentPos				= 0;
		m_fCurrentFrameHasPlayTime	= 0;
		m_nEndFrameNumber	= (int)m_pConfig->framePos.size();
		m_nStartFrameNumber	= m_pConfig->repeatStartFrame;
		ShowNullFrame();
	}

	void TextureFrameEffect::Init(E3DEngine::TextureUVConfig cfg)
	{
		m_bPlayInReverse = false;
		m_bIsPlay		 = false;
		std::vector<std::string> framePos = StringBuilder::Split(cfg.framePos, ",");
		std::vector<vec2d> newPos;
		for (int i = 0; i < framePos.size() / 2; i ++)
		{
			vec2d _pos(Convert::ToFloat(framePos[i * 2]), Convert::ToFloat(framePos[i * 2 + 1]));
			newPos.push_back(_pos);
		}
		m_pConfig->framePos			= newPos;
		m_pConfig->heightPic		= cfg.heightPic;
		m_pConfig->heightTexture	= cfg.heightTexture;
		m_pConfig->isReverse		= cfg.isReverse == 1;
		m_pConfig->leftRightMirror	= cfg.leftRightMirror;
		m_pConfig->repeatStartFrame = cfg.repeatStartFrame;
		m_pConfig->speed			= cfg.speed;
		m_pConfig->startX			= cfg.startX;
		m_pConfig->startY			= cfg.startY;
		m_pConfig->topBottomMirror	= cfg.topBottomMirror;
		m_pConfig->type				= cfg.type;
		m_pConfig->widthPic			= cfg.widthPic;
		m_pConfig->widthTexture		= cfg.widthTexture;
		IsParticleEffect			= true;
		initFrame();
	}
	
	void TextureFrameEffect::activeChange(E3DEngine::IObject *sender, E3DEngine::EventArgs *e)
	{
		if (mGameObject->IsActive && IsAutoPlay)
		{
			Play();
		}
		else if(mGameObject->IsActive == false)
		{
			Stop(true);
		}
	}

	void TextureFrameEffect::Pause()
	{
		m_bIsPlay = false;
	}

	bool TextureFrameEffect::GetIsPlay()
	{
		return m_bIsPlay;
	}

	void TextureFrameEffect::SetStateType(DWORD stateType)
	{
		m_StateType = stateType;
	}

	bool TextureFrameEffect::CanStop()
	{
		if (!m_bIsPlay)
		{
			return false;
		}
		if (m_totalPlayTime < m_pConfig->duration)
		{
			return false;
		}
		
		return true;
	}

	bool TextureFrameEffect::Stop(bool now)
	{
		if (pActor == nullptr)
		{
			return true;
		}
		if (now)
		{
			Pause();
			ReSet();
			ShowNullFrame();
			StopPostponeTimer();
		}
		return true;
	}

	void TextureFrameEffect::ReSet()
	{
		m_nCurrentPos		= 0;
		m_nEndFrameNumber	= (int)m_pConfig->framePos.size();
		m_nStartFrameNumber	= m_pConfig->repeatStartFrame;
		m_bPlayInReverse = false; 
		m_totalPlayTime = 0.0f;
		vec2f restPos = computeCurrentFramePosition();
		if (!IsParticleEffect)
		{
			if (m_RenderObject != nullptr)
			{
				
			}
		}
		if (pActor != nullptr)
		{
			E3DEngine::EventArgs *e = new E3DEngine::EventArgs();
			e->lParam = restPos.x;
			e->rParam = restPos.y;
			pActor->EffectFrameChange(this, e);
			SAFE_DELETE(e);
		}
	}

	void TextureFrameEffect::Start()
	{
		m_bIsLoop					= true;
		
		if (m_RenderObject != nullptr)
		{
			m_RenderObject = mGameObject->GetRenderer();
		}
	}

	void TextureFrameEffect::Update(float deltaTime)
	{
		if (!m_bIsPlay)
		{
			return;
		}
		bool _continue = m_bIsFirstPlay || m_bIsLoop; // 第一次 或者循环播放
		if(_continue)
		{
			playInFrame(deltaTime);
		}
		else
		{
			m_bIsPlay = false;
		}
	}

	void TextureFrameEffect::Destory()
	{
		
	}

	TextureFrameEffect::TextureFrameEffect()
	{
		IsAutoPlay = true;
		m_pConfig = new TextureFrameConfig;
		m_pConfig->type = -1;
		pActor = nullptr;
	}

	void TextureFrameEffect::Play(float postponeTime, float duration)
	{
		if (m_bIsPlay)
		{
			return;
		}
		m_totalPlayTime = 0;
		m_pConfig->duration = duration;
		m_pConfig->postponeTime = postponeTime;
		
		if (postponeTime != 0.0f)
		{
			PostponePlay();
		}
		else
		{
			m_bIsPlay = true;
		}
		m_bIsFirstPlay = true;
	}

	vec2f TextureFrameEffect::computeCurrentFramePosition()
	{
		vec2f pos;
		if (m_pConfig->type == 0)
		{ // 规则序列帧
			pos.x = m_pConfig->framePos[m_nCurrentPos].x;
			pos.y = m_pConfig->framePos[m_nCurrentPos].y;
		}
		else
		{
			pos.x = m_FrameStartPos.x + m_FrameSize.x * (m_nCurrentPos % (int)m_fTotalColumn);
			pos.y = m_FrameStartPos.y + m_FrameSize.y * (m_nCurrentPos / (int)m_fTotalColumn);
		}
		return pos;
	}

	vec2f TextureFrameEffect::GetTextureFrameScale()
	{
		return m_TextureScale;
	}

	void TextureFrameEffect::playInFrame(float deltaTime)
	{
		if (m_pConfig->type == -1)
		{
			return;
		}
		if (!m_bIsPlay)
		{
			return;
		}
		// 第一次按顺序播放， 如果配置循环开始帧，第二次从循环开始帧起， 如果倒序 则第二次倒回循环开始帧再继续
		if (m_nCurrentPos == m_nEndFrameNumber)
		{ // 序列帧到结尾
			m_fCurrentFrameHasPlayTime = 0;
			// 决定下一次正序还是倒序
			if (m_pConfig->isReverse )
			{
				m_bPlayInReverse = !m_bPlayInReverse;
			}
			if (m_bPlayInReverse)
			{// 倒序
				m_nEndFrameNumber	= m_pConfig->repeatStartFrame;
				m_nStartFrameNumber	= (int)m_pConfig->framePos.size() - 1;
			}
			else
			{// 正序
				m_nEndFrameNumber	= (int)m_pConfig->framePos.size();
				m_nStartFrameNumber	= m_pConfig->repeatStartFrame;
			}
			m_nCurrentPos = m_nStartFrameNumber;
			// 事件调用
			if (pActor != nullptr)
			{
				pActor->EffectEnd(nullptr, nullptr);
			}
		}
		vec2f framePosition = computeCurrentFramePosition();
		if (m_fCurrentFrameHasPlayTime >= m_fTimeLongOneFrame)
		{// 一帧播放完毕
			m_fCurrentFrameHasPlayTime = 0;
			if (m_bPlayInReverse )
			{// 倒序
				m_nCurrentPos --;
			}
			else
			{// 正序
				m_nCurrentPos ++;
			}
			if (!IsParticleEffect)
			{
				
			}
			if (pActor != nullptr)
			{
				E3DEngine::EventArgs *e = new E3DEngine::EventArgs();
				e->lParam = framePosition.x;
				e->rParam = framePosition.y;
				pActor->EffectFrameChange(this, e);
				SAFE_DELETE(e);
			}
		}
		if (m_totalPlayTime >= m_pConfig->duration && m_pConfig->duration != 0.f)
		{
			if (pActor)
			{
				pActor->PlayDurationEnd(this, nullptr);
				Stop(true);
			}
		}
		m_totalPlayTime += deltaTime;
		m_fCurrentFrameHasPlayTime += deltaTime;
	}


	vec2f TextureFrameEffect::GetTextureFrameCoord(int frame)
	{
		m_nCurrentPos = frame;
		return computeCurrentFramePosition();
	}

	void TextureFrameEffect::PostponePlay()
	{
		PostponeShowNextFrame();
	}

	void TextureFrameEffect::PostponeShowNextFrame()
	{
		EventHandleFunction * callBack_Func = NewFunctionHandler(&TextureFrameEffect::postponeTextureFrame, this);
		// 延迟
		E3DEngine::EventArgs * e = new E3DEngine::EventArgs;
		e->lParam = ets_NotTrig;
		m_postponeTimerID = E3DEngine::Timer::AddTimer(m_pConfig->postponeTime, callBack_Func, e);
		E3DEngine::Timer::StartTimer(m_postponeTimerID);
	}

	void TextureFrameEffect::postponeTextureFrame(IObject* _sender, EventArgs * _e)
	{
		DWORD trigState = _e->lParam;
		m_postponeTimerID = 0;
		if (trigState == ets_NotTrig)
		{
			// 延迟后播放
			m_bIsPlay = true;
			if (m_pConfig->duration != 0)
			{
				EventHandleFunction * callBack_Func = NewFunctionHandler(&TextureFrameEffect::postponeTextureFrame, this);
				E3DEngine::EventArgs * e = new E3DEngine::EventArgs;
				e->lParam = ets_HasTrig;
				m_postponeTimerID = E3DEngine::Timer::AddTimer(m_pConfig->duration, callBack_Func, e);
				E3DEngine::Timer::StartTimer(m_postponeTimerID);
			}
		}
		else
		{// 结束播放
			Stop();
		}
		SAFE_DELETE(_e);
	}

	void TextureFrameEffect::StopPostponeTimer()
	{
		if (m_postponeTimerID != 0)
		{
			E3DEngine::Timer::StopTimer(m_postponeTimerID);
			m_postponeTimerID = 0;
		}
	}

	vec2f TextureFrameEffect::ShowFirstFrame()
	{
		ReSet();
		return m_pConfig->framePos[0];
	}

	void TextureFrameEffect::ShowNullFrame()
	{
		if (!IsParticleEffect)
		{
			
		}
	}

	vec2f TextureFrameEffect::ShowNextFrame()
	{
		m_nCurrentPos ++;
		if (m_nCurrentPos >= m_pConfig->framePos.size())
		{
			m_nCurrentPos = 0;
		}
		
		vec2f frameCoord = computeCurrentFramePosition();
		if (!IsParticleEffect )
		{
			
		}
		return frameCoord;
	}

	DWORD TextureFrameEffect::GetStateType()
	{
		return m_StateType;
	}

	void TextureFrameEffect::AddSource(IActor * s)
	{
		pActor = s;
	}

}

void TextureFrameConfig::Copy(TextureFrameConfig &cfg)
{
	this->image = cfg.image;
	this->speed = cfg.speed;
	this->repeatStartFrame = cfg.repeatStartFrame;
	this->type = cfg.type;
	this->isReverse = cfg.isReverse;
	this->leftRightMirror = cfg.leftRightMirror;
	this->topBottomMirror = cfg.topBottomMirror;
	this->widthTexture = cfg.widthTexture;
	this->heightTexture = cfg.heightTexture;
	this->widthPic = cfg.widthPic;
	this->heightPic = cfg.heightPic;
	this->startX = cfg.startX;
	this->startY = cfg.startY;
	this->postponeTime = cfg.postponeTime;
	this->duration = 0;
	this->postponeTime = 0;
	std::copy(cfg.framePos.begin(), cfg.framePos.end(), std::back_inserter(this->framePos));
}

TextureFrameConfig & TextureFrameConfig::operator=(TextureFrameConfig &cfg)
{
	Copy(cfg);
	return *this;
}

TextureFrameConfig::TextureFrameConfig(TextureFrameConfig &cfg)
{
	Copy(cfg);
}

TextureFrameConfig::TextureFrameConfig()
{

}
