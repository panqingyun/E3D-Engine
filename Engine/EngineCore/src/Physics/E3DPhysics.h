//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-11-27  PanQingyun. All rights reserved. ***********************//

#pragma once
#include "../Source/Interface.h"
#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL RaycastHit : public Ref
	{
	public:
		vec3f mPickPos;
		float mDistance;
		GameObject *mGameObject;
	};

	struct E3D_EXPORT_DLL Ray : public Ref
	{
		Ray()
		{

		}
		Ray(vec3f f, vec3f t)
		{
			From = f;
			To = t;
		}
		vec3f From;
		vec3f To;
	};

	class E3D_EXPORT_DLL PhysicWorld : public  Ref
	{

	private:
		PhysicWorld();

	public:
		~PhysicWorld();
		static PhysicWorld &GetInstance();
#ifndef __IGNORED_INCLUDE__
		void InitPhysics();

		void CreateGround();
		btVector3 GetInertia();

		void Update(float deltaTime);
		void Destory();
		void Cleanup();
		void AddRigidBody(btRigidBody* body, int group = 0, int mask = 0);

		btDiscreteDynamicsWorld * GetWorld();

#endif
		bool RayCast(Ray ray, RaycastHit &hit);
		void SetPause(bool bPause);

#ifndef __IGNORED_INCLUDE__
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
		bool	mPause;
		bool	mbPaused;
#endif
	};
}