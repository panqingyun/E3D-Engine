//
//  Effect.cpp
//  Created by 潘庆云 on 2017/1/26.
//

#include "E3DEffect.hpp"

namespace E3DEngine
{

    void Effect::Update(float deltaTime)
    {
        if (!m_bIsPlay)
        {
            return;
        }
        bool _continue = m_bIsFirstPlay || m_bIsLoop; // 第一次 或者循环播放
        if(_continue)
        {
            //playInFrame(deltaTime);
        }
        else
        {
            m_bIsPlay = false;
        }
    }
	
	void Effect::Stop()
	{
		m_bIsPlay = false;
	}

	Effect::~Effect()
	{
		SAFE_DELETE(m_pEventArgs);
	}

	Effect::Effect()
	{
		m_pEventArgs = nullptr;
		m_bIsPlay = false;
	}

}
