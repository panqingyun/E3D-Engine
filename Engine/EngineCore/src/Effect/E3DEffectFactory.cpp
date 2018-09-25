//
//  EffectFactory.cpp
//
//  Created by 潘庆云 on 2017/1/26.
//

#include "E3DEffectFactory.hpp"
namespace E3DEngine
{

    void EffectFactory::Update(float deltaTime)
    {
        std::map<UINT, Effect*>::iterator it = m_mapEffects.begin();
        for (; it != m_mapEffects.end(); ++it)
        {
            it->second->Update(deltaTime);
        }
    }
    
    void EffectFactory::Destory()
    {
        for(std::map<UINT,Effect *>::iterator it = m_mapEffects.begin();
            it != m_mapEffects.end(); ++it)
        {
            Effect * pEffect = it->second;
            SAFE_DELETE(pEffect);
        }
		m_mapEffects.clear();
    }
    
    void EffectFactory::Initilize()
    {
    }

	EffectFactory& EffectFactory::GetInstance()
	{
		static EffectFactory _ins;
		return _ins;
	}

}
