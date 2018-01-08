////
////  DynamicRectangle.cpp
////
////  Created by 潘庆云 on 2017/7/25.
////
//
//#include "E3DDynamicRectangle.hpp"
//#include "../Effect/E3DTextureFrameEffect.hpp"
//#include "../Source/EngineDelegate.h"
//
//namespace E3DEngine
//{
//	DynamicRectangle::~DynamicRectangle()
//	{
//		EngineDelegate::GetInstance().DestoryObject(m_pRender);
//		for (auto & m_vecWord : m_vecWords)
//		{
//			SAFE_DELETE(m_vecWord);
//		}
//        m_vecWords.clear();
//        for (auto & m_vecWordShadow : m_vecWordShadows)
//        {
//            SAFE_DELETE(m_vecWordShadow);
//        }
//        m_vecWordShadows.clear();
//	}
//	void DynamicRectangle::Init()
//	{
//		iindexTotal = 0;
//		ivertexTotal = 0;
//		m_pRender = new Renderer;
//		m_pRender->RemoveInRenderer(ID);
//		m_pRender->RecordCurrentVextexStartIndex(ID);
//		m_pRender->RecordCurrentIndexStartIndex(ID);
//		m_pRender->SetActive(true);
//		m_pRender->IsStaticDraw = false;
//		ParentNode->AddChild(m_pRender);
//	}
//
//	void DynamicRectangle::SetActive(bool isActive)
//	{
//		if (isActive == IsActive)
//		{
//			return;
//		}
//		IsActive = isActive;
//		m_pRender->SetActive(isActive);
//	}
//
//	void DynamicRectangle::Create(float perWidth, float perHeight, vec3f centerPosition, vec2f uv, vec2f wh)
//	{
//		// 0 ---- 3 4------7
//		// |	  | |      |
//		// |	  | |      |
//		// |	  | |      |
//		// 1------2 5------6
//
//		Particle *word = new Particle();
//		word->Create(perWidth, perHeight, false, 1, centerPosition, 0, LONG_TIME);
//		word->Index = (int)(m_vecWords.size()+m_vecWordShadows.size());
//		m_vecWords.push_back(word);
//		Vertex *vertex = word->getVertex();
//		for (int vi = 0; vi < 4; vi++)
//		{
//			m_pRender->FillVertex(vertex[vi]);
//		}
//		// 4 个顶点有 6个索引,
//		GLuint * index = word->getIndices();
//		for (int ii = 0; ii < 6; ii++)
//		{
//			GLuint idx = index[ii] + ivertexTotal;
//			m_pRender->FillIndex(idx);
//			iindexTotal++;
//		}
//		m_pRender->FillEnd();
//		word->SetTextureUVCoord(uv, wh);
//		word->SetColor(1, 1, 1, 1);
//		//word->SetTextureUVCoord(0, 0, vec2f(1,1));
//
//		ivertexTotal += 4;
//	}
//    
//	E3DEngine::DynamicRectangle * DynamicRectangle::CreateInstance(Object * parent)
//	{
//		DynamicRectangle * rect = new DynamicRectangle;		
//		rect->SetParent(parent);
//		return rect;
//	}
//
//	void DynamicRectangle::CreateTextShadow(float perWidth, float perHeight, vec3f centerPosition, vec2f uv, vec2f wh)
//    {
//        Particle *word = new Particle();
//		word->Create(perWidth, perHeight, false, 1, centerPosition, 0, LONG_TIME);
//        word->Index = (int)(m_vecWords.size()+m_vecWordShadows.size());
//        m_vecWordShadows.push_back(word);
//        Vertex *vertex = word->getVertex();
//        for (int vi = 0; vi < 4; vi++)
//        {
//            m_pRender->FillVertex(vertex[vi]);
//        }
//        // 4 个顶点有 6个索引,
//        GLuint * index = word->getIndices();
//        for (int ii = 0; ii < 6; ii++)
//        {
//            GLuint idx = index[ii] + ivertexTotal;
//            m_pRender->FillIndex(idx);
//            iindexTotal++;
//		}
//		m_pRender->FillEnd();
//        word->SetTextureUVCoord(uv, wh);
//        word->SetColor(1, 1, 1, 1);
//        //word->SetTextureUVCoord(0, 0, vec2f(1,1));
//        
//        ivertexTotal += 4;
//    }
//
//	void DynamicRectangle::CreateComplete()
//	{
//		m_pRender->VertexCountAdd(ID, (DWORD)m_vecWords.size() * 4);
//		m_pRender->IndexCountAdd(ID, (DWORD)m_vecWords.size() * 6);
//	}
//
//	void DynamicRectangle::SetMaterial(E3DEngine::Material *material)
//	{
//		m_pRender->pMaterial = material;
//	}
//
//
//	std::vector<Particle*> * DynamicRectangle::GetElements()
//	{
//		return &m_vecWords;
//	}
//
//
//	std::vector<Particle*> * DynamicRectangle::GetShadowElements()
//	{
//		return &m_vecWordShadows;
//	}
//
//	void DynamicRectangle::AfterUpdate(float deltaTime)
//	{
//		vertexStartIndex = m_pRender->GetRendererBuffer(ID)->VertextStartIndex;
//		std::vector<Particle*>::iterator it = m_vecWords.begin();
//		for (; it != m_vecWords.end(); ++it)
//		{
//			Particle *p = (*it);
//			if (p == nullptr)
//			{
//				continue;
//			}
//
//			p->Update(deltaTime);
//			m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 0] = p->getVertex()[0];
//			m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 1] = p->getVertex()[1];
//			m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 2] = p->getVertex()[2];
//			m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 3] = p->getVertex()[3];
//		}
//        
//        it = m_vecWordShadows.begin();
//        for (; it != m_vecWordShadows.end(); ++it)
//        {
//            Particle *p = (*it);
//            if (p == nullptr)
//            {
//                continue;
//            }
//            
//            p->Update(deltaTime);
//            m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 0] = p->getVertex()[0];
//            m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 1] = p->getVertex()[1];
//            m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 2] = p->getVertex()[2];
//            m_pRender->Vertices[vertexStartIndex + p->Index * 4 + 3] = p->getVertex()[3];
//        }
//		if (m_vecWords.empty())
//		{
//			//SetActive(false);
//		}
//	}
//
//	void DynamicRectangle::Move(vec3f newPos)
//	{
//		if (m_pRender == nullptr)
//		{
//			return;
//		}
//
//	}
//
//	void DynamicRectangle::Scale(vec3f scale)
//	{
//		if (m_pRender == nullptr)
//		{
//			return;
//		}
//	}
//
//	void DynamicRectangle::Rotate(vec3f rotate)
//	{
//		if (m_pRender == nullptr)
//		{
//			return;
//		}
//	}
//
//	void DynamicRectangle::SetDontDestory(bool dontDestory)
//	{
//		DontDestoryOnLoad = dontDestory;
//		if (m_pRender == nullptr)
//		{
//			return;
//		}
//		EngineDelegate::GetInstance().AddDonotDestory(m_pRender);
//	}
//
//	void DynamicRectangle::Pause(bool bPause)
//	{
//		if (PauseEffectDelegate.empty())
//		{
//			return;
//		}
//		EventArgs * e = new EventArgs;
//		bPause ? e->lParam = 0 : e->lParam = 1;
//		PauseEffectDelegate(this, e);
//		SAFE_DELETE(e);
//	}
//
//
//	void DynamicRectangle::Enable(bool bEnable)
//	{
//		if (EnableEffectDelegate.empty())
//		{
//			SetActive(bEnable);
//			return;
//		}
//		EventArgs * e = new EventArgs;
//		bEnable ? e->lParam = 0 : e->lParam = 1;
//		EnableEffectDelegate(this, e);
//		SAFE_DELETE(e);
//	}
//
//}
