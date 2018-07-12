
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-14  PanQingyun. All rights reserved. ************************//

#ifndef Collider_hpp
#define Collider_hpp

#include "../Object/E3DGameObject.h"
#include "E3DPhysics.h"
#include "../Object/E3DTransform.hpp"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	void ImplCollider();

	struct ColCallBack : public btCollisionWorld::ContactResultCallback
	{
	public:
		virtual btScalar addSingleResult(
			btManifoldPoint & cp,
			const btCollisionObjectWrapper * colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper * colObj1Wrap,
			int partId1,
			int index1) override
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
		};
	};

	class RigidBody : public Component
	{
		DECLARE_CLASS(RigidBody)
	public:
		RigidBody();
		~RigidBody();

	public:
		void SetMass(float mass);
		float GetMass() { return mMass; }
		void SetFriction(float friction);
		float GetFriction() { return mFriction; }
		void SetRestitution(float restitution);
		float GetRestitution() { return mRestitution; }

	public:
		virtual void CreateBehaviour() override;
		virtual void OnCreateComplete() override;
		virtual void Update(float deltaTime) override;
	private:
		void createRigidBody(btCollisionShape *shape);

	private:
		float mMass;
		float mFriction;
		float mRestitution;
		btRigidBody* mRigidBody;
		btTransform  mStartTransform;
		ColCallBack	 mColCallBack;
		btDefaultMotionState*	mMotionState;

	};

	class Collider : public Component
	{
	public:
		virtual ~Collider()
		{
			SAFE_DELETE(m_pShape);
			SAFE_DELETE(m_pMotionState);
		}
		virtual void OnCreate()
		{
			Component::OnCreate();
			gameObject->SetCollider(this);
		}
	public:
		virtual void Start() override { }
		virtual void Update(float deltaTime) override { }
		virtual void Destory() override { }
	public:
		virtual bool CheckClick(vec2d screenPoint) { return false;}
		virtual bool CheckPress(vec2d screenPoint) { return false;}
		virtual btCollisionShape * GetCollisionShape() { return m_pShape; }
	protected:

		btCollisionShape*	m_pShape;
	};
	
	class BoxCollider : public  Collider
	{
		DECLARE_CLASS(BoxCollider)
	public:
		BoxCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;

	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);

		virtual void CreateBehaviour() override;
	};

	class SphereCollider : public  Collider
	{
		DECLARE_CLASS(SphereCollider)
	public:
		SphereCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;

	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
		virtual void CreateBehaviour() override;
	};

	class MeshCollider : public Collider
	{
		DECLARE_CLASS(MeshCollider)
	public:
		MeshCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;

	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
		virtual void CreateBehaviour() override;
	};

	class MotionState : public  btDefaultMotionState
	{
	public:
		MotionState(const  btTransform &initialpos, GameObject *obj)
		{
			mObject = obj;
			mWorldTrans = initialpos;
		}

		virtual  ~MotionState() 
		{
		}

		void  setObject(GameObject *obj) 
		{
			mObject = obj;
		}

		virtual  void  getWorldTransform(btTransform &worldTrans) const 
		{
			worldTrans = mWorldTrans;
		}

		virtual  void  setWorldTransform(const  btTransform &worldTrans) override;

	protected:
		GameObject *mObject;
		btTransform mWorldTrans;
	};
}

#endif /* Collider_hpp */
