//
//  Collider.hpp
//
//  Created by 潘庆云 on 2017/7/14.
//

#ifndef Collider_hpp
#define Collider_hpp

#include "../Object/E3DGameObject.h"
#include "E3DPhysics.h"
#include "../Object/E3DTransform.hpp"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	void ImplCollider();

	struct ColCallBack : btCollisionWorld::ContactResultCallback
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

	class Collider extends Component
	{
	public:
		virtual ~Collider()
		{
			SAFE_DELETE(m_pShape);
			SAFE_DELETE(m_pMotionState);
		}
	public:
		virtual void Start() override { }
		virtual void Update(float deltaTime) override { }
		virtual void Destory() override { }
	public:
		virtual bool CheckClick(vec2d screenPoint) { return false;}
		virtual bool CheckPress(vec2d screenPoint) { return false;}
		virtual btRigidBody* CreateRigidBody(float mass);
	protected:
		void createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);

		btCollisionShape*	m_pShape;
		btScalar			m_fMass;
		btRigidBody*		m_pRigidBody;
		btDefaultMotionState* m_pMotionState;
		ColCallBack			 mColCallBack;
		btTransform			m_StartTransform;
	};
	
	class BoxCollider extends Collider
	{
		DECLARE_CLASS(BoxCollider)
	public:
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;

	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);

		virtual void CreateBehaviour() override;
	};

	class SphereCollider extends Collider
	{
		DECLARE_CLASS(SphereCollider)
	public:
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
		virtual void Awake() override;
		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		virtual void Destory() override;

	public:
		virtual bool CheckClick(vec2d screenPoint);
		virtual bool CheckPress(vec2d screenPoint);
		virtual void CreateBehaviour() override;
	};

	class MotionState extends btDefaultMotionState
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
