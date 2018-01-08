//////////////////////////////////////////////////////////////////////////
/// Create by PanQingyun
/// 2017 - 11 - 27
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "../Source/Interface.h"

namespace E3DEngine
{
	class Physics extends Ref
	{
	private:
		Physics();

	public:
		~Physics();
		static Physics &GetInstance()
		{
			static Physics _ins;
			return _ins;
		}
		void InitPhysics();

		void CreateGround();

		void Update(float deltaTime);
		void Destory();
		void AddRigidBody(btRigidBody* body, int group = 0, int mask = 0);
		btDiscreteDynamicsWorld * GetWorld()
		{
			return m_pDynamicsWorld;
		}
	private:
		btDefaultCollisionConfiguration* m_pCollisionConfiguration;
		btCollisionDispatcher* m_pDispatcher;
		btBroadphaseInterface* m_pOverlappingPairCache;
		btSequentialImpulseConstraintSolver* m_pSolver;
		btDiscreteDynamicsWorld* m_pDynamicsWorld;
		btBoxShape* m_pGroundShape;
		btCollisionObject* objA;
		btCollisionObject* objB;
		std::map<uint, char> m_hasCheckObjectMap;
	};
}