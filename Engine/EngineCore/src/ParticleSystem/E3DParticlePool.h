#ifndef __PARTICLE_POOL_H__
#define __PARTICLE_POOL_H__
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-17  PanQingyun. All rights reserved. ************************//
//////////////////////////////////////////////////////////////////////////
// È«¾ÖÁ£×Ó³Ø 
//////////////////////////////////////////////////////////////////////////

#include "../Source/Interface.h"

namespace E3DEngine
{
	class Particle;
	using particleListIterator = std::list<share_pointer<Particle>>::iterator;
	class E3D_EXPORT_DLL ParticlePool : public IObject
	{
	public:
		ParticlePool();
		static ParticlePool & GetInstance();

		void Destory()
		{
			m_ParticleList.clear();
		}

		void CreateParticlePool(unsigned int particleNumber);
		
		share_pointer<Particle> ActiveParticleFromPool();

		void DeleteParticleToDeathPool(share_pointer<Particle>  particle);

		void DeleteParticleToDeathPool(std::list<share_pointer<Particle>>& particlePools);

	private: 
		std::list<share_pointer<Particle>> m_ParticleList;
		unsigned int m_nMaxParticleNumber;
		bool	bLock;
	};
}

#endif
