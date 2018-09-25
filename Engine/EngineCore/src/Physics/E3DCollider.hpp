
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

#ifndef __EDITOR__
	struct EX_PORT ColCallBack : public btCollisionWorld::ContactResultCallback
	{
	public:

		virtual btScalar addSingleResult(
			btManifoldPoint & cp,
			const btCollisionObjectWrapper * colObj0Wrap,
			int partId0,
			int index0,
			const btCollisionObjectWrapper * colObj1Wrap,
			int partId1,
			int index1) override;;

	};
#endif
	class EX_PORT RigidBody : public Component
	{
		DECLARE_CLASS(RigidBody)
	public:
		RigidBody();
		~RigidBody();

	public:
		void SetMass(float mass);
		float GetMass();
		void SetFriction(float friction);
		float GetFriction();
		void SetRestitution(float restitution);
		float GetRestitution();

	public:
		virtual void CreateBehaviour() override;
		virtual void OnCreateComplete() override;
		virtual void Update(float deltaTime) override;
	private:

#ifndef __EDITOR__
		void createRigidBody(btCollisionShape *shape);

	private:
		float mMass;
		float mFriction;
		float mRestitution;
		btRigidBody* mRigidBody;
		btTransform  mStartTransform;
		ColCallBack	 mColCallBack;
		btDefaultMotionState*	mMotionState;
#endif
	};

	class EX_PORT Collider : public Component
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
			mGameObject->SetCollider(this);
		}
	public:

#ifndef __EDITOR__
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);

		virtual btCollisionShape * GetCollisionShape();
	protected:

		btCollisionShape*	m_pShape;
#endif
	};
	
	class EX_PORT BoxCollider : public  Collider
	{
		DECLARE_CLASS(BoxCollider)
	public:
		BoxCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;

#ifndef __EDITOR__
	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
#endif
		virtual void CreateBehaviour() override;
	};

	class EX_PORT SphereCollider : public  Collider
	{
		DECLARE_CLASS(SphereCollider)
	public:
		SphereCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;

	public:

#ifndef __EDITOR__
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
#endif
		virtual void CreateBehaviour() override;
	};

	class EX_PORT MeshCollider : public Collider
	{
		DECLARE_CLASS(MeshCollider)
	public:
		MeshCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;

#ifndef __EDITOR__
	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
#endif
		virtual void CreateBehaviour() override;
	};

	class EX_PORT MotionState 
#ifndef __EDITOR__
		: public  btDefaultMotionState
#endif
	{
	public:

#ifndef __EDITOR__
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
#endif

	};

	class EX_PORT CapsuleCollider : public Collider
	{
		DECLARE_CLASS(CapsuleCollider)
	public:
		CapsuleCollider();
		~CapsuleCollider();

	public:
		virtual void Awake() override;
		virtual void CreateBehaviour() override;
		void SetRadius(float radius);
		void SetHieght(float height);
		float GetHeight();
		float GetRadius();

	private: 
		float mRadius;
		float mHeight;
	};

}

#endif /* Collider_hpp */
