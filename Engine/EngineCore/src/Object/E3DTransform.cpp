//
//  Transform.cpp
//
//  Created by 潘庆云 on 2017/2/8.
//

#include "E3DTransform.hpp"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{
    void CTransform::SetPosition(vec3f position)
    {
		NOT_ACTIVE_RETURN(gameObject)
		m_bStateChange = true;
		Position = position;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
    }
	
	void CTransform::SetPosition(float x, float y, float z)
	{
		NOT_ACTIVE_RETURN(gameObject)
		vec3f position(x, y, z);
		m_bStateChange = true;
		Position = position;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
	}
	
    void CTransform::SetRotation(Quatf rotation)
	{
		NOT_ACTIVE_RETURN(gameObject)
		m_bStateChange = true;
		Rotation = rotation; 
		RotationEuler = Rotation.toEulerAngles();
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
    }
    
    void CTransform::SetRotation(float x, float y,float z)
	{
		NOT_ACTIVE_RETURN(gameObject)
		Quatf rotate = Quatf::fromEulerAngles(x, y, z);
		m_bStateChange = true;
		RotationEuler = vec3f(x, y, z);
		Rotation = rotate;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
    }
    
    void CTransform::SetRotation(mat4f rotateMatrix)
	{
		NOT_ACTIVE_RETURN(gameObject)
		Quatf rotate = Quatf::frommat(rotateMatrix);
		m_bStateChange = true;
		Rotation = rotate;
		RotationEuler = Rotation.toEulerAngles();
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
    }
    
	void CTransform::SetRotation(float x, float y, float z, float w)
	{
		/*Rotation.v.x = x;
		Rotation.v.y = y;
		Rotation.v.z = z;
		Rotation.w = w;
		RotationEuler = Rotation.toEulerAngles();*/
	}

	void CTransform::SetScale(vec3f scale)
	{
		NOT_ACTIVE_RETURN(gameObject)
		m_bStateChange = true;
		Scale = scale;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
    }
	
	void CTransform::SetScale(float x, float y, float z)
	{
		NOT_ACTIVE_RETURN(gameObject)
		m_bStateChange = true;
		Scale.x = x;
		Scale.y = y;
		Scale.z = z;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
	}

	void CTransform::AddChild(UINT objID, E3DEngine::CTransform *child)
	{
		if (Childs.find(objID) != Childs.end())
		{
			return;
		}
		Childs[objID] = child;
		child->Parent = this;
	}
	
    void CTransform::GenBillBoard(vec3f right, vec3f cameraForward)
    {
		// 求right 和vxoz的夹角 就是在前方向上旋转角度
		vec3f vxoz  = vec3f(right.x, 0, right.z);
		float cosa	= vxoz.dotProduct(right) / (right.length() * vxoz.length());
		float a		= acos(cosa);
		if (right.y > 0)
		{
			a = -a;
		}
		
		vec3f forward	= -cameraForward;
		Quatf q			= Quatf::fromAxisRot(forward, -a / M_PI * 180);
		Rotation		= q;
    }

	void CTransform::RemoveChild(UINT objID)
	{
		if (Childs.find(objID) == Childs.end())
		{
			return;
		}
		Childs.erase(objID);
	}

	void CTransform::Identity()
	{
		WorldMatrix.identity();
		Rotation = Quatf::frommat(WorldMatrix);
		Position = vec3f(WorldMatrix.at(0, 3), WorldMatrix.at(1, 3), WorldMatrix.at(2, 3));
		Scale = vec3f(1, 1, 1);
	}

	void CTransform::SetBillBoardNormal(vec3f pos, vec3f scale)
    {
		vec3f cameraPos = gameObject->pCamera->Transform->Position;
        
        vec3f forward = pos - cameraPos;
        forward.normalize();
        
        vec3f up = vec3f(0.0,1.0,0.0);
        up.normalize();
        
        vec3f side = forward.crossProduct(up);
        side.normalize();
        
        
        billboardMatrix.identity();
        
//        billboardMatrix.data[0] = side.x;billboardMatrix.data[4] = side.y;billboardMatrix.data[8] = side.z;
//        billboardMatrix.data[1] = up.x;  billboardMatrix.data[5] = up.y;  billboardMatrix.data[9] = up.z;
//        billboardMatrix.data[2] = forward.x;billboardMatrix.data[6] = 0;billboardMatrix.data[10] = forward.z;
        
        billboardMatrix.data[0] = side.x;billboardMatrix.data[1] = side.y;billboardMatrix.data[2] = side.z;
        billboardMatrix.data[4] = up.x;  billboardMatrix.data[5] = up.y;  billboardMatrix.data[6] = up.z;
        billboardMatrix.data[8] = forward.x;billboardMatrix.data[9] = 0;billboardMatrix.data[10] = forward.z;
        
        mat4f scaleM = mat4f::createScaleMatrix(scale.x, scale.y, scale.z);
        mat4f tranM = mat4f::createTranslation(pos.x, pos.y, pos.z);
        
        mat4f result = billboardMatrix * scaleM;
        billboardMatrix = tranM * result;
    }
    
	
	void CTransform::SetIsBillBoard(bool bill)
	{
		m_IsBillBoard = bill;
	}


	void CTransform::SetNeedUpdate(bool bIsNeed)
	{
		m_bNeedUpdate = bIsNeed;
	}

	vvision::vec3f CTransform::GetPosition()
	{
		return Position;
	}

	mat4f CTransform::GetParentMatrix()
	{
		mat4f Identity;
		Identity.identity();
		mat4f parentMatrix = Parent != nullptr ? Parent->WorldMatrix : Identity;
		return parentMatrix;
	}
	
	void CTransform::Destory()
	{
		Childs.clear();
	}

	vec3f CTransform::getParentScale()
	{
		vec3f vScale(1,1,1);
		vec3f vParentScale = Parent != nullptr ? Parent->Scale : vScale;
		return vParentScale;
	}
	
	vec3f CTransform::getParentPosition()
	{
		vec3f vPosition(0,0,0);
		vec3f vParentPosition = Parent != nullptr ? Parent->Position : vPosition;
		return vParentPosition;
	}
	
	Quatf CTransform::getParentRotation()
	{
		Quatf qRotate = Quatf::fromEulerAngles(0, 0, 0);
		Quatf parentRotation = Parent != nullptr ? Parent->Rotation : qRotate;
		return parentRotation;
	}
	
	void CTransform::SetMatrix(mat4f matrix)
	{
		NOT_ACTIVE_RETURN(gameObject)

		Position = vec3f(matrix[12], matrix[13], matrix[14]);
		Rotation = Quatf::frommat(matrix);
		// TODO scale
		m_bStateChange = true;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
	}

	void CTransform::SetRotation(vec3f rotate)
	{
		NOT_ACTIVE_RETURN(gameObject)
		Quatf rotateQuat = Quatf::fromEulerAngles(rotate.x, rotate.y, rotate.z);
		m_bStateChange = true;
		RotationEuler = rotate;
		Rotation = rotateQuat;
		if (gameObject != nullptr)
		{
			gameObject->TransformChange();
		}
	}
	
	void CTransform::translation()
	{
		// 平移
		WorldMatrix.at(3, 0)	=  Position.x;
		WorldMatrix.at(3, 1)	=  Position.y;
		WorldMatrix.at(3, 2)	=  Position.z;
	}
	
	void CTransform::scale()
	{
		// 缩放
		mat4f scale = mat4f::createScaleMatrix(Scale.x, Scale.y, Scale.z);
		WorldMatrix = WorldMatrix * scale;
	}
	
	void CTransform::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		m_pBehaviour->Create(NAME_SPACE, "Transform");
		setBehaviourDefaultValue();
	}


	void CTransform::setBehaviourDefaultValue()
	{
		Object::setBehaviourDefaultValue();
	}

	void CTransform::rotate()
	{
	}
	
    void CTransform::Update()
    {		
		if (!m_bNeedUpdate)
		{
			return;
		}
		WorldMatrix.identity();
		if (IsTransPosFirst)
		{
			translation();
			// 旋转
			WorldMatrix = Rotation.transform() * WorldMatrix ;
			scale();
		}
		else
		{
            if(m_IsBillBoard)
            {
                WorldMatrix = billboardMatrix;
            }
            else
            {
                // 旋转
                WorldMatrix = WorldMatrix * Rotation.transform();
                scale();
                translation();
            }
		}
		WorldMatrix = GetParentMatrix() * WorldMatrix;
		for (auto & Child : Childs)
		{
			Child.second->Update();
		}
		m_bStateChange = false;
    }

	CTransform::CTransform()
	{
		gameObject = nullptr;
		IsTransPosFirst = false;
		Parent = nullptr;
		m_bStateChange = false;
		m_IsBillBoard = false;
		m_bNeedUpdate = true;
		Identity();
		CreateBehaviour();
	}

}
