
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
		Mass = 0;
		Friction = 500;
		Restitution = 0.1;
		mRigidBody = nullptr;
		mMotionState = nullptr;
		CreateBehaviour();
	}

	RigidBody::~RigidBody()
	{
	}

	void RigidBody::SetMass(void *cp, object mass)
	{
		RigidBody *rb = (RigidBody*)cp;
		float mValue = object_cast<float>(mass);
		rb->Mass = mValue;
		if (rb->mRigidBody != nullptr)
		{
			rb->mRigidBody->setMassProps(mValue, PhysicWorld::GetInstance().GetInertia());
		}
	}


	void RigidBody::SetFriction(void *cp, object friction)
	{
		RigidBody *rb = (RigidBody*)cp;
		float mValue = object_cast<float>(friction);
		rb->Friction = mValue;
		if (rb->mRigidBody != nullptr)
		{
			rb->mRigidBody->setFriction(mValue);
		}
	}


	object RigidBody::GetFriction(void *cp)
	{
		RigidBody *rb = (RigidBody*)cp;
		return rb->Friction;
	}

	void RigidBody::SetRestitution(void *cp, object restitution)
	{
		RigidBody *rb = (RigidBody*)cp;
		float mValue = object_cast<float>(restitution);
		rb->Restitution = mValue;
		if (rb->mRigidBody != nullptr)
		{
			rb->mRigidBody->setRestitution(mValue);
		}
	}

	void RigidBody::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(RigidBody);
		mBehaviour->Awake();
		setBehaviourDefaultValue();
	}


	void RigidBody::OnCreateComplete()
	{
		Collider * collider = mGameObject->GetCollider();
		if (collider != nullptr)
		{
			btCollisionShape *shape = collider->GetCollisionShape();
			CreateRigidBody(shape);
		}
		else
		{
			// TODO
		}
	}


	void RigidBody::Update(float deltaTime)
	{
		mBehaviour->Update(deltaTime);
		if (mMotionState == nullptr)
		{
			return;
		}
		if (Mass != 0)
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
		mStartTransform.setRotation(q);

		mRigidBody->setWorldTransform(mStartTransform);
	}

	void  RigidBody::CreateRigidBody(btCollisionShape *shape)
	{
		mStartTransform.setIdentity();
		mStartTransform.setOrigin(btVector3(
			btScalar(Transform->Position.x),
			btScalar(Transform->Position.y),
			btScalar(Transform->Position.z)));
		btQuaternion q;
		q.setEuler(Transform->RotationEuler.y * M_PI / 180, Transform->RotationEuler.x* M_PI / 180, Transform->RotationEuler.z* M_PI / 180);

		mStartTransform.setRotation(q);
		
		bool isDynamic = (Mass != 0.f);
		btVector3 localInertia = PhysicWorld::GetInstance().GetInertia();
		if (isDynamic)
			shape->calculateLocalInertia(Mass, localInertia);

		mMotionState = new MotionState(mStartTransform, mGameObject);
		btRigidBody::btRigidBodyConstructionInfo cInfo(Mass, mMotionState, shape, localInertia);

		mRigidBody = new btRigidBody(cInfo);

		mRigidBody->setUserIndex(-1);
		mRigidBody->setFriction(Friction); // 摩擦力
		mRigidBody->setUserPointer(mGameObject);
		mRigidBody->setRestitution(Restitution);
		PhysicWorld::GetInstance().GetWorld()->contactTest(this->mRigidBody, mColCallBack);
		PhysicWorld::GetInstance().AddRigidBody(mRigidBody);
	}

	object RigidBody::GetMass(void *cp)
	{
		RigidBody *rb = (RigidBody*)cp;
		return rb->Mass;
	}

	object RigidBody::GetRestitution(void *cp)
	{
		RigidBody *rb = (RigidBody*)cp;
		return rb->Restitution;
	}

	void BoxCollider::Awake()
	{
		vec3f lwh;
		lwh = mGameObject->GetBounds();
		m_pShape = createBoxShape(btVector3(btScalar(lwh.x / 2), btScalar(lwh.z / 2), btScalar(lwh.y / 2)));
		m_pShape->setLocalScaling(btVector3(mGameObject->Transform->Scale.x, mGameObject->Transform->Scale.y, mGameObject->Transform->Scale.z));
		m_pShape->setUserPointer(mGameObject);
		mBehaviour->Awake();
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
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(BoxCollider);
		mBehaviour->Awake();
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
		float l = mGameObject->GetBounds().x;
		m_pShape = createSphereShape(l);
		m_pShape->setLocalScaling(btVector3(mGameObject->Transform->Scale.x, mGameObject->Transform->Scale.y, mGameObject->Transform->Scale.z));
		m_pShape->setUserPointer(mGameObject);
		mBehaviour->Awake();
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
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(SphereCollider);
		mBehaviour->Awake();
		setBehaviourDefaultValue();
	}


	void MeshCollider::Awake()
	{
		std::vector<Vertex> &vertexs = mGameObject->GetVertex();
		std::vector<UINT> &indexs = mGameObject->GetIndex();
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
		part.m_numVertices = mGameObject->GetVertex().size();
		part.m_triangleIndexBase = (const unsigned char*)indexs.data();
		part.m_triangleIndexStride = sizeof(UINT) * 3;
		part.m_numTriangles = indexs.size() / 3;
		part.m_indexType = PHY_INTEGER;    

		btTriangleIndexVertexArray * indexVertex = new btTriangleIndexVertexArray();
		indexVertex->addIndexedMesh(part, PHY_INTEGER);
		m_pShape = new btBvhTriangleMeshShape(indexVertex, true);
		m_pShape->setLocalScaling(btVector3(mGameObject->Transform->Scale.x, mGameObject->Transform->Scale.y, mGameObject->Transform->Scale.z));
		m_pShape->setUserPointer(mGameObject);
		mBehaviour->Awake();
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
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(MeshCollider);
		mBehaviour->Awake();
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
		m_pShape->setLocalScaling(btVector3(mGameObject->Transform->Scale.x, mGameObject->Transform->Scale.y, mGameObject->Transform->Scale.z));
		m_pShape->setUserPointer(mGameObject);
		mBehaviour->Awake();
	}

	void CapsuleCollider::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(CapsuleCollider);
		mBehaviour->Awake();
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


	float CapsuleCollider::GetHeight()
	{
		return mHeight;
	}


	float CapsuleCollider::GetRadius()
	{
		return mRadius;
	}

	btScalar ColCallBack::addSingleResult(btManifoldPoint & cp, const btCollisionObjectWrapper * colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper * colObj1Wrap, int partId1, int index1)
	{
		/*btVector3 posA = cp.getPositionWorldOnA();
		btVector3 posB = cp.getPositionWorldOnB();*/

		// obA 与 obB 发生碰撞
		if (colObj0Wrap->getCollisionObject()->getUserPointer() == nullptr)
		{
			return 0;
		}
		else if (colObj1Wrap->getCollisionObject()->getUserPointer() == nullptr)
		{
			return 0;
		}
		GameObject *obA = static_cast<GameObject*>(colObj0Wrap->getCollisionObject()->getUserPointer());
		GameObject *obB = static_cast<GameObject*>(colObj1Wrap->getCollisionObject()->getUserPointer());
		obA->OnCollisionEnter(obA);
		obB->OnCollisionEnter(obB);

		return btScalar(0.f);
	}

	void Collider::OnCreate()
	{
		Component::OnCreate();
		mGameObject->SetCollider(this);
	}

	bool Collider::CheckClick(vec2d screenPoint)
	{
		return false;
	}


	bool Collider::CheckPress(vec2d screenPoint)
	{
		return false;
	}


	btCollisionShape * Collider::GetCollisionShape()
	{
		return m_pShape;
	}

}
