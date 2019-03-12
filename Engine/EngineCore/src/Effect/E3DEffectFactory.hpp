//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-26 PanQingyun. All rights reserved. *************************//
#ifndef EffectFactory_hpp
#define EffectFactory_hpp

#include <stdio.h>
#include "E3DEffect.hpp"

namespace E3DEngine
{

    class E3D_EXPORT_DLL EffectFactory implement IFactory
    {
    public:
        static EffectFactory& GetInstance();
        template<typename T> T * CretateEffect()
        {
            T *t_ins = new T();
            m_mapEffects.insert(std::pair<UINT, Effect*>(m_nEffectID, static_cast<Effect*>(t_ins)));
            m_nEffectID ++;
            return t_ins;
        }
        virtual void Update(float deltaTime);
        virtual void Initilize();
        virtual void Destory();
        
    private:
        EffectFactory(){ }
    private:
        std::map<UINT,Effect *> m_mapEffects;
        UINT m_nEffectID;
    };

}
#endif /* EffectFactory_hpp */
