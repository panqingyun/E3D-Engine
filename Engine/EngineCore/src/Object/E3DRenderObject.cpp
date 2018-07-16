//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-17  PanQingyun. All rights reserved. ************************//

#include "E3DRenderObject.hpp"
#include "../Source/EngineDelegate.h"
#include "E3DTransform.hpp"
#include "../RenderSystem/Material/E3DMaterial.hpp"

//extern PFNGLMAPBUFFEROESPROC
namespace E3DEngine
{
	bool MinMaxAABB::IsInside(const vec3f& inPoint) const
	{
		if (inPoint[0] < m_Min[0])
			return false;
		if (inPoint[0] > m_Max[0])
			return false;

		if (inPoint[1] < m_Min[1])
			return false;
		if (inPoint[1] > m_Max[1])
			return false;

		if (inPoint[2] < m_Min[2])
			return false;
		if (inPoint[2] > m_Max[2])
			return false;

		return true;
	}

	void MinMaxAABB::CalculateVertices(vec3f outVertices[8]) const
	{
		//    7-----6
		//   /|    /|
		//  3-+---2 |
		//  | 4---|-| 5
		//  |/    |/
		//  0-----1
		outVertices[0].set(m_Min.x, m_Min.y, m_Min.z);
		outVertices[1].set(m_Max.x, m_Min.y, m_Min.z);
		outVertices[2].set(m_Max.x, m_Max.y, m_Min.z);
		outVertices[3].set(m_Min.x, m_Max.y, m_Min.z);
		outVertices[4].set(m_Min.x, m_Min.y, m_Max.z);
		outVertices[5].set(m_Max.x, m_Min.y, m_Max.z);
		outVertices[6].set(m_Max.x, m_Max.y, m_Max.z);
		outVertices[7].set(m_Min.x, m_Max.y, m_Max.z);
	}

	void MinMaxAABB::Init()
	{
		m_Min.normalize();
		m_Max.normalize();
	}

    RenderObject::RenderObject()
	{
		pMaterial = nullptr;
		m_nColor = 0xffffffff;
        nMaterialID = 0;
		m_bIsBufferData = false;
		mType = eT_RenderObject;
		RenderIndex = eRI_Normal;
		m_bIsActive = true;
		IsStaticDraw = true;
		m_bNeedSortVertex = false;
    }

	RenderObject::~RenderObject()
	{
		Vertices.clear();
		Indices.clear();		
	}
    
	void RenderObject::SetDrawModule(DWORD module)
	{
		m_nDrawModule = module;
	}


	void RenderObject::SetMaterialID(int ID)
    {
        nMaterialID			= ID;
    }
	
	void RenderObject::SetMaterial(Material *material)
	{
		pMaterial = material;
		if (RenderIndex != eRI_None)
		{
			// TODO 同样的材质，不同渲染层级，需要重新创建一个Renderer
			//m_pRenderer = GetRenderSystem()->GetRenderManager()->CreateVertexRender(material->mMaterialID);
		}
		IsStaticDraw = false;
		SceneManager::GetInstance().GetCurrentScene()->AddRenderObject(this, m_layer);
		//for (auto & attr : pMaterial->pShader->AttributeList)
		//{// TODO 根据材质需要的顶点数据重新分配顶点数组

		//}
	}

	void RenderObject::Render(float deltaTime)
	{
		
    }

	void RenderObject::Destory(RenderObject *obj)
	{
		SAFE_DELETE(obj);
	}


	void RenderObject::SetCamera(Camera * camera)
	{
		pCamera = camera;
	}

	void RenderObject::SetColor(long color)
	{
		m_nColor = color;
	}

	void RenderObject::SetIsBillborad(bool isBillboard)
	{
		m_bIsBillboard = isBillboard;
	}

	bool RenderObject::GetIsBillBoard()
	{
		return m_bIsBillboard;
	}


	void RenderObject::SetTransform(CTransform * _transform)
	{
		transform = _transform;
	}

	void RenderObject::CreateNewTransform()
	{
		if (transform == nullptr)
		{
			transform = new CTransform;
		}
	}

	E3DEngine::CTransform * RenderObject::GetTransform()
	{
		return transform;
	}

	void RenderObject::SetRenderIndex(DWORD index)
	{
		RenderIndex = (eRenderIndex)index;
		if (SceneManager::GetInstance().GetCurrentScene() == nullptr)
		{
			return;
		}
		SceneManager::GetInstance().GetCurrentScene()->ChangeRenderIndex(ID, (eRenderIndex)index);
	}


	void RenderObject::SetLayerMask(DWORD layer)
	{
		m_layer = layer;
		SceneManager::GetInstance().GetCurrentScene()->ChangeRenderObjectLayer(this);
	}

}
