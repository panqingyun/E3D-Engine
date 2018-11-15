
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
#ifndef __IGNORED_INCLUDE__
	struct E3D_EXPORT_DLL ColCallBack : public btCollisionWorld::ContactResultCallback
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
	class E3D_EXPORT_DLL RigidBody : public Component
	{
		DECLARE_CLASS(RigidBody)
	public:
		RigidBody();
		~RigidBody();

	public:
		static void SetMass(void *cp, object mass);
		static object GetMass(void *cp);
		static void SetFriction(void *cp, object friction);
		static object GetFriction(void *cp);
		static void SetRestitution(void *cp, object restitution);
		static object GetRestitution(void *cp);

	public:
		virtual void CreateBehaviour() override;
		virtual void OnCreateComplete() override;
		virtual void Update(float deltaTime) override;
	
#ifndef __IGNORED_INCLUDE__

		void CreateRigidBody(btCollisionShape *shape);

	public:
		virtual void registProperty() override
		{
			SAVE_METHOD(Mass, FT_FLOAT);
			SAVE_METHOD(Friction, FT_FLOAT);
			SAVE_METHOD(Restitution, FT_FLOAT);
		}

	protected:
		float Mass;
		float Friction;
		float Restitution;
		btRigidBody* mRigidBody;
		btTransform  mStartTransform;
		ColCallBack	 mColCallBack;
		btDefaultMotionState*	mMotionState;
#endif
	};

	class E3D_EXPORT_DLL Collider : public Component
	{
	public:
		virtual ~Collider()
		{
#ifndef __IGNORED_INCLUDE__
			SAFE_DELETE(m_pShape);
#endif
		}
		virtual void OnCreate();
		virtual void SetActive(bool active) override;
	public:
#ifndef __IGNORED_INCLUDE__
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);

		virtual btCollisionShape * GetCollisionShape();
	protected:

		btCollisionShape*	m_pShape;
#endif
	};
	
	class E3D_EXPORT_DLL BoxCollider : public  Collider
	{
		DECLARE_CLASS(BoxCollider)
	public:
		BoxCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;
		virtual void registProperty() override
		{

		}
#ifndef __IGNORED_INCLUDE__
	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
#endif
		virtual void CreateBehaviour() override;
	};

	class E3D_EXPORT_DLL SphereCollider : public  Collider
	{
		DECLARE_CLASS(SphereCollider)
	public:
		SphereCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;

	public:
		virtual void registProperty() override
		{

		}
#ifndef __IGNORED_INCLUDE__
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
#endif
		virtual void CreateBehaviour() override;
	};

	class E3D_EXPORT_DLL MeshCollider : public Collider
	{
		DECLARE_CLASS(MeshCollider)
	public:
		MeshCollider()
		{
			CreateBehaviour();
		}
		virtual void Awake() override;
		virtual void registProperty() override
		{

		}
#ifndef __IGNORED_INCLUDE__
	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
#endif
		virtual void CreateBehaviour() override;
	};

	class E3D_EXPORT_DLL MotionState 
#ifndef __IGNORED_INCLUDE__
		: public  btDefaultMotionState
#endif
	{
	public:
#ifndef __IGNORED_INCLUDE__
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

	class E3D_EXPORT_DLL CapsuleCollider : public Collider
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
		virtual void registProperty() override
		{

		}
	private: 
		float mRadius;
		float mHeight;
	};

}

#endif /* Collider_hpp */
