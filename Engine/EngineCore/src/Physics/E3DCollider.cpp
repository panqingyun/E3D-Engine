
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) PanQingyun. All rights reserved. 2017-7-14  ************************//

#include "E3DCollider.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DTransform.hpp"

namespace E3DEngine
{
	void ImplCollider()
	{
		REGIST_CLASS(BoxCollider);
		REGIST_CLASS(SphereCollider);
		REGIST_CLASS(MeshCollider);
		REGIST_CLASS(RigidBody);
		REGIST_CLASS(CapsuleCollider);
	}

	DECLARE_CLASS_NAME(BoxCollider)
	DECLARE_CLASS_NAME(SphereCollider)
	DECLARE_CLASS_NAME(MeshCollider)
	DECLARE_CLASS_NAME(RigidBody)
	DECLARE_CLASS_NAME(CapsuleCollider)

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

	btCapsuleShapeZ * createCapsuleShape(btScalar radius, btScalar height)
	{
		btCapsuleShapeZ * capsule = new btCapsuleShapeZ(radius, height);
		return capsule;
	}

	RigidBody::RigidBody()
	{
		mMass = 0;
		mFriction = 500;
		mRestitution = 0.1;
		mRigidBody = nullptr;
		mMotionState = nullptr;
		CreateBehaviour();
	}

	RigidBody::~RigidBody()
	{
	}

	void RigidBody::SetMass(float mass)
	{
		mMass = mass;
		if (mRigidBody != nullptr)
		{
			mRigidBody->setMassProps(mass, Physics::GetInstance().GetInertia());
		}
	}


	void RigidBody::SetFriction(float friction)
	{
		mFriction = friction;
		if (mRigidBody != nullptr)
		{
			mRigidBody->setFriction(friction);
		}
	}

	void RigidBody::SetRestitution(float restitution)
	{
		mRestitution = restitution;
		if (mRigidBody != nullptr)
		{
			mRigidBody->setRestitution(restitution);
		}
	}

	void RigidBody::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(RigidBody);
		m_pBehaviour->Awake();
		setBehaviourDefaultValue();
	}


	void RigidBody::OnCreateComplete()
	{
		Collider * collider = gameObject->GetCollider();
		if (collider != nullptr)
		{
			btCollisionShape *shape = collider->GetCollisionShape();
			createRigidBody(shape);
		}
		else
		{
			// TODO
		}
	}


	void RigidBody::Update(float deltaTime)
	{
		m_pBehaviour->Update(deltaTime);
		if (mMotionState == nullptr)
		{
			return;
		}
		if (mMass != 0)
		{
			return;
		}
		mStartTransform.setIdentity();
		vec3f position = Transform->GetPosition();
		mStartTransform.setOrigin(btVector3(
			btScalar(position.x),
			btScalar(position.y),
			btScalar(position.z)));

		btQuaternion q;
		q.setEuler(Transform->RotationEuler.y * M_PI / 180, Transform->RotationEuler.x* M_PI / 180, Transform->RotationEuler.z* M_PI / 180);
		vec3f scale = Transform->GetScale();
		mStartTransform.setRotation(q);

		mRigidBody->setWorldTransform(mStartTransform);
	}

	void  RigidBody::createRigidBody(btCollisionShape *shape)
	{
		mStartTransform.setIdentity();
		mStartTransform.setOrigin(btVector3(
			btScalar(Transform->Position.x),
			btScalar(Transform->Position.y),
			btScalar(Transform->Position.z)));
		btQuaternion q;
		q.setEuler(Transform->RotationEuler.y * M_PI / 180, Transform->RotationEuler.x* M_PI / 180, Transform->RotationEuler.z* M_PI / 180);

		mStartTransform.setRotation(q);
		
		bool isDynamic = (mMass != 0.f);
		btVector3 localInertia = Physics::GetInstance().GetInertia();
		if (isDynamic)
			shape->calculateLocalInertia(mMass, localInertia);

		mMotionState = new MotionState(mStartTransform, gameObject);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mMass, mMotionState, shape, localInertia);

		mRigidBody = new btRigidBody(cInfo);

		mRigidBody->setUserIndex(-1);
		mRigidBody->setFriction(mFriction); // 摩擦力
		mRigidBody->setUserPointer(gameObject);
		mRigidBody->setRestitution(mRestitution);
		Physics::GetInstance().GetWorld()->contactTest(this->mRigidBody, mColCallBack);
		Physics::GetInstance().AddRigidBody(mRigidBody);
	}

	void BoxCollider::Awake()
	{
		vec3f lwh;
		lwh = gameObject->GetBounds();
		m_pShape = createBoxShape(btVector3(btScalar(lwh.x / 2), btScalar(lwh.z / 2), btScalar(lwh.y / 2)));
		m_pShape->setLocalScaling(btVector3(gameObject->Transform->Scale.x, gameObject->Transform->Scale.y, gameObject->Transform->Scale.z));
		m_pShape->setUserPointer(gameObject);
		m_pBehaviour->Awake();
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
		float l = gameObject->GetBounds().x;
		m_pShape = createSphereShape(l);
		m_pShape->setLocalScaling(btVector3(gameObject->Transform->Scale.x, gameObject->Transform->Scale.y, gameObject->Transform->Scale.z));
		m_pShape->setUserPointer(gameObject);
		m_pBehaviour->Awake();
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


	void MeshCollider::Awake()
	{
		std::vector<Vertex> &vertexs = gameObject->GetVertex();
		std::vector<UINT> &indexs = gameObject->GetIndex();
		btIndexedMesh part;
		const int size = vertexs.size() * 3;
		float *vertexBase = new float[size];
		for (int i = 0; i < vertexs.size(); i++)
		{
			vertexBase[i * 3 + 0] = vertexs[i].Position[0];
			vertexBase[i * 3 + 1] = vertexs[i].Position[1];
			vertexBase[i * 3 + 2] = vertexs[i].Position[2];
		}
		
		part.m_vertexBase = (const unsigned char*)vertexBase;
		part.m_vertexStride = sizeof(btScalar) * 3;
		part.m_numVertices = gameObject->GetVertex().size();
		part.m_triangleIndexBase = (const unsigned char*)indexs.data();
		part.m_triangleIndexStride = sizeof(UINT) * 3;
		part.m_numTriangles = indexs.size() / 3;
		part.m_indexType = PHY_INTEGER;    

		btTriangleIndexVertexArray * indexVertex = new btTriangleIndexVertexArray();
		indexVertex->addIndexedMesh(part, PHY_INTEGER);
		m_pShape = new btBvhTriangleMeshShape(indexVertex, true);
		m_pShape->setLocalScaling(btVector3(gameObject->Transform->Scale.x, gameObject->Transform->Scale.y, gameObject->Transform->Scale.z));
		m_pShape->setUserPointer(gameObject);
		m_pBehaviour->Awake();
	}

	bool MeshCollider::CheckClick(vec2d screenPoint)
	{
		return false;
	}


	bool MeshCollider::CheckPress(vec2d screenPoint)
	{
		return false;
	}

	void MeshCollider::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(MeshCollider);
		m_pBehaviour->Awake();
		setBehaviourDefaultValue();
	}


	CapsuleCollider::CapsuleCollider()
	{
		CapsuleCollider();
	}

	CapsuleCollider::~CapsuleCollider()
	{
	}

	void CapsuleCollider::Awake()
	{
		m_pShape = createCapsuleShape(mRadius, mHeight); 
		m_pShape->setLocalScaling(btVector3(gameObject->Transform->Scale.x, gameObject->Transform->Scale.y, gameObject->Transform->Scale.z));
		m_pShape->setUserPointer(gameObject);
		m_pBehaviour->Awake();
	}

	void CapsuleCollider::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(CapsuleCollider);
		m_pBehaviour->Awake();
		setBehaviourDefaultValue();
	}


	void CapsuleCollider::SetRadius(float radius)
	{
		mRadius = radius;
	}


	void CapsuleCollider::SetHieght(float height)
	{
		mHeight = height;
	}

}
