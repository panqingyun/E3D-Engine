#include "E3DPhysics.h"
#include "../Object/E3DGameObject.h"
#include "../Source/E3DDebug.h"
#include "E3DCollider.hpp"

namespace E3DEngine
{
	Physics::Physics()
	{
	}

	Physics::~Physics()
	{
	}

	void Physics::InitPhysics()
	{
		btVector3 worldAabbMin(-10000, -10000, -10000);
		btVector3 worldAabbMax(10000, 10000, 10000);
		int maxProxies = 1024;
		btAxisSweep3* broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);

		m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
		m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
		m_pOverlappingPairCache = new btDbvtBroadphase();
		m_pSolver = new btSequentialImpulseConstraintSolver;
		// 创建物理世界
		m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, broadphase, m_pSolver, m_pCollisionConfiguration);
		// 重力加速度 10
		m_pDynamicsWorld->setGravity(btVector3(0, -10, 0));
		ImplCollider();
		//CreateGround();

	}

	void Physics::Update(float deltaTime)
	{
		m_pDynamicsWorld->stepSimulation(deltaTime);
		//int  numManifolds = m_pDispatcher->getNumManifolds();
		//for (int i = 0; i < numManifolds; i++)
		//{
		//	btPersistentManifold* contactManifold = m_pDynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		//	GameObject* obA = static_cast<GameObject*>(contactManifold->getBody0()->getUserPointer());
		//	GameObject* obB = static_cast<GameObject*>(contactManifold->getBody1()->getUserPointer());
		//	if (m_hasCheckObjectMap.find(obA->ID) != m_hasCheckObjectMap.end() &&
		//		m_hasCheckObjectMap.find(obB->ID) != m_hasCheckObjectMap.end())
		//	{// 不做重复检测
		//		continue;
		//	}
		//	// obA 与 obB 发生碰撞
		//	if (obA == nullptr || obB == nullptr)
		//	{
		//		continue;
		//	}
		//	int  numContacts = contactManifold->getNumContacts();
		//	for (int j = 0; j < numContacts; j++)
		//	{
		//		btManifoldPoint& pt = contactManifold->getContactPoint(j);
		//		if (pt.getDistance() < 0.f)
		//		{					
		//			m_hasCheckObjectMap[obA->ID] = 1;
		//			m_hasCheckObjectMap[obB->ID] = 1;
		//			obA->OnCollisionEnter(obB);
		//			obB->OnCollisionEnter(obA);
		//		}
		//	}
		//}
		m_hasCheckObjectMap.clear();
	}

	void Physics::Destory()
	{

	}

	void Physics::AddRigidBody(btRigidBody * body, int group /*= 0*/, int mask /*= 0*/)
	{
		if ( group == 0)
		{
			m_pDynamicsWorld->addRigidBody(body);
		}
		else
		{
			m_pDynamicsWorld->addRigidBody(body, group, mask);
		}
	}

	void Physics::CreateGround()
	{
		m_pGroundShape = new  btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -150, 0));

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			m_pGroundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_pGroundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		m_pDynamicsWorld->addRigidBody(body);
	}

}

