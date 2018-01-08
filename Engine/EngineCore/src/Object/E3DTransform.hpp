//
//  Transform.hpp
//
//  Created by 潘庆云 on 2017/2/8.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "E3DObject.h"

namespace E3DEngine
{
    class GameObject;
	class CTransform extends Object
    {
    public:
        CTransform();
		void SetMatrix(mat4f matrix);
        void Update();
        void SetPosition(vec3f position);
		void SetPosition(float x, float y, float z);
        void SetRotation(Quatf rotation);
        void SetRotation(mat4f rotateMatrix);
		void SetRotation(float x, float y,float z);
		void SetRotation(vec3f rotate);
		void SetRotation(float x, float y, float z, float w);
		void SetScale(vec3f scale);
		void SetScale(float x, float y, float z);
        void GenBillBoard(vec3f center, vec3f cameraForward);
		void RemoveChild(QWORD objID);
		void Identity();
        void SetBillBoardNormal(vec3f pos,vec3f scale);
        void SetIsBillBoard(bool bill);
		void SetNeedUpdate(bool bIsNeed);
        
        vec3f GetPosition();
		void AddChild(QWORD objID ,CTransform * child);
		mat4f GetParentMatrix();
		void Destory();
	public:
		Quatf getParentRotation();
		vec3f getParentPosition();
		vec3f getParentScale();
		void  translation();
		void  rotate();
		void  scale();

	protected:
		virtual void CreateBehaviour();
		virtual void setBehaviourDefaultValue();

    public:
        GameObject * gameObject;
        mat4f WorldMatrix;
        mat4f billboardMatrix;
        vec3f Position;
        vec3f Scale;
		Quatf Rotation;
		vec3f RotationEuler;
		bool  IsTransPosFirst;
		CTransform * Parent;
		std::map<QWORD, CTransform*> Childs;
	private:
		bool  m_bStateChange;
        bool    m_IsBillBoard;
		bool  m_bNeedUpdate;
    };
}

#endif /* Transform_hpp */
