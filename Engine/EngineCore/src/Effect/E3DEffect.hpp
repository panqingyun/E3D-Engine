
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-26 PanQingyun. All rights reserved. *************************//

#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>
#include "../Object/E3DGameObject.h"
#include "../Source/E3DDelegate.h"

namespace E3DEngine
{
    class Effect extends Ref
    {
        friend class EffectFactory;
    protected:
        Effect()
		{
			m_pEventArgs = nullptr;
			m_bIsPlay = false;
		}
		virtual ~Effect()
		{
			SAFE_DELETE(m_pEventArgs);
		}
    public:
        virtual void Update(float deltaTime);
        virtual void Play() = 0;
		virtual void Stop();
    public:
        event EventDelegates PlayEffectEndHandler; // 特效播放完成的回调函数
    protected:
        virtual void playInFrame(float deltaTime) = 0;
    protected:
        float m_fTotalTime;                 // 总共执行时间
        bool m_bIsLoop;                     // 是否循环播放
        IObject * m_pHandleCallBackClass;   // 回调函数处理者
        bool m_bIsPlay;                     // 是否在播放中
        float m_fHasPlayTime;               // 一帧已经播放的时间
        bool m_bIsFirstPlay;                // 是否首次播放
        EventArgs *m_pEventArgs;            // 播放结束事件的参数
        float m_fOneFrameTime;              // 一帧应播放的时间长度
        int m_nCurrentFrame;                // 当前是第几帧

    };
}
#endif /* Effect_hpp */
