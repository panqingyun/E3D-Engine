//
//  Collider.cpp
//  Created by 潘庆云 on 2017/7/14.
//

#include "E3DCollider.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DTransform.hpp"

namespace E3DEngine
{
	void ImplCollider()
	{
		REGIST_CLASS(BoxCollider);
		REGIST_CLASS(SphereCollider);
	}

	DECLARE_CLASS_NAME(BoxCollider)
	DECLARE_CLASS_NAME(SphereCollider)

	btBoxShape* createBoxShape(const btVector3& halfExtents)
	{
		btBoxShape* box = new btBoxShape(halfExtents);
		return box;
	}

	btSphereShape * createSphereShape(btScalar radius)
	{
		btSphereShape * sphere = new btSphereShape(radius);
		return sphere;
	}

	void  Collider::createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
	{
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			shape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new MotionState(startTransform, gameObject);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

		m_pRigidBody = new btRigidBody(cInfo);
		//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

		m_pRigidBody->setUserIndex(-1);
		m_pRigidBody->setFriction(10);

		m_pRigidBody->setUserPointer(gameObject);
		Physics::GetInstance().AddRigidBody(m_pRigidBody);
	}

	void BoxCollider::Start()
	{
	}

	void BoxCollider::Awake()
	{
		CreateBehaviour();
		vec3f lwh;
		lwh = gameObject->GetBounds();
		m_pMotionState = nullptr;
		m_pShape = createBoxShape(btVector3(btScalar(lwh.x / 2), btScalar(lwh.z / 2), btScalar(lwh.y / 2)));
		m_pShape->setUserPointer(gameObject);
		m_pBehaviour->Start();
	}

	void BoxCollider::Update(float deltaTime)
	{
		m_pBehaviour->Update(deltaTime);
	}

	void BoxCollider::Destory()
	{
		m_pBehaviour->Destory();
	}

	bool BoxCollider::CheckClick(vec2d screenPoint)
	{
		return false;
	}
	
	bool BoxCollider::CheckPress(vec2d screenPoint)
	{
		return false;
	}


	void BoxCollider::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(BoxCollider);
		m_pBehaviour->Awake();
		setBehaviourDefaultValue();
	}

	btRigidBody* Collider::CreateRigidBody(float mass)
	{
		m_fMass = mass;
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(
			btScalar(Transform->Position.x),
			btScalar(Transform->Position.y),
			btScalar(Transform->Position.z)));
		createRigidBody(mass, startTransform, m_pShape);
		Physics::GetInstance().GetWorld()->contactTest(m_pRigidBody, mColCallBack);
		return m_pRigidBody;
	}


	void MotionState::setWorldTransform(const btTransform &worldTrans)
	{
		if (mObject == nullptr)
			return; // silently return before we set a node 
		if (worldTrans == mWorldTrans)
		{
			return;
		}
		const btVector3 &position = worldTrans.getOrigin();
		mObject->Transform->SetPosition(position.getX(), position.getY(), position.getZ());

		vec3f rotate;
		worldTrans.getRotation().getEulerZYX(rotate.z, rotate.y, rotate.x);
		mObject->Transform->SetRotation(rotate.x * 180 / M_PI, rotate.y * 180 / M_PI, rotate.z * 180 / M_PI);
		mWorldTrans = worldTrans;
	}

	void SphereCollider::Awake()
	{
		CreateBehaviour();
		float l = gameObject->GetBounds().x;
		m_pMotionState = nullptr;
		m_pShape = createSphereShape(l);
		m_pShape->setUserPointer(gameObject);
		m_pBehaviour->Start();
	}

	void SphereCollider::Start()
	{

	}

	void SphereCollider::Update(float deltaTime)
	{
		m_pBehaviour->Update(deltaTime);
	}

	void SphereCollider::Destory()
	{
		m_pBehaviour->Destory();
	}

	bool SphereCollider::CheckClick(vec2d screenPoint)
	{
		return false;
	}

	bool SphereCollider::CheckPress(vec2d screenPoint)
	{
		return false;
	}

	void SphereCollider::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(SphereCollider);
		m_pBehaviour->Awake();
		setBehaviourDefaultValue();
	}

}
