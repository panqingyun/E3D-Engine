#ifndef __PARTICLE_POOL_H__
#define __PARTICLE_POOL_H__

//////////////////////////////////////////////////////////////////////////
// È«¾ÖÁ£×Ó³Ø 
//////////////////////////////////////////////////////////////////////////

#include "../Source/Interface.h"

namespace E3DEngine
{
	class Particle;
	using particleListIterator = std::list<share_pointer<Particle>>::iterator;
	class ParticlePool implement IObject
	{
	public:
		ParticlePool()
		{
			m_nMaxParticleNumber = 0;
			bLock = false;
		}
		static ParticlePool & GetInstance()
		{
			static ParticlePool _ins;
			return _ins;
		}

		void Destory()
		{
			m_ParticleList.clear();
		}

		void CreateParticlePool(UINT particleNumber);
		
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