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

	class EX_PORT PhysicWorld : public  Ref
	{

#ifndef __EDITOR__
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
		btVector3 GetInertia();

		void Update(float deltaTime);
		void Destory();
		void AddRigidBody(btRigidBody* body, int group = 0, int mask = 0);

		btDiscreteDynamicsWorld * GetWorld();

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
#endif
	};
}