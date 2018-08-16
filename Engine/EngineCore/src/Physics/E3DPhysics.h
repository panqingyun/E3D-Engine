//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-11-27  PanQingyun. All rights reserved. ***********************//

#pragma once
#include "../Source/Interface.h"
#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
	class RaycastHit : public Ref
	{
	public:
		GameObject *mGameObject;
	};

	struct Ray : public Ref
	{
		vec3f From;
		vec3f To;
	};

	class PhysicWorld : public  Ref
	{
	private:
		PhysicWorld();

	public:
		~PhysicWorld();
		static PhysicWorld &GetInstance()
		{
			static PhysicWorld _ins;
			return _ins;
		}
		void InitPhysics();

		void CreateGround();
		btVector3 GetInertia() { return mlocalInertia; }

		void Update(float deltaTime);
		void Destory();
		void AddRigidBody(btRigidBody* body, int group = 0, int mask = 0);

		btDiscreteDynamicsWorld * GetWorld()
		{
			return m_pDynamicsWorld;
		}

		bool RayCast(Ray ray, RaycastHit &hit);
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
		btVector3 mlocalInertia;
	};
}