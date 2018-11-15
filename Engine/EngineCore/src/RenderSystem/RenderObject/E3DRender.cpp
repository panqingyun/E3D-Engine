//
//  E3DRenderer.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DRender.hpp"
#include "..\E3DRenderSystem.hpp"
#include "..\..\Source\E3DVertexManager.h"
#include "..\..\Source\Application.h"
#include "..\..\Scene\E3DSceneLoader.h"

namespace E3DEngine
{
	void Renderer::OnCreateComplete()
	{
		std::string path = "";
		if (MaterialPath[0] == MaterialPath[1] && MaterialPath[1] == '.')
		{
			path = GetCurLoadRootPath() + MaterialPath;
		}
#ifdef __E3D_EDITOR__
		else if (MaterialPath.find(":") != std::string::npos)
		{
			path = MaterialPath;
		}
#endif
		else
		{
			path = Application::AppDataPath + MaterialPath;
		}
		Material *m = GetRenderSystem()->GetMaterialManager()->CreateMaterial(path, MaterialID);
		BatchRenderer * brd = GetRenderSystem()->GetRenderManager()->GetRenderer(m->ID, VertexManager::GetVertex(mGameObject->VertexBufferName).size(), (RENDER_TYPE)RendererType, mGameObject->GetIsStatic());
		mGameObject->SetRenderer(brd);
		pRenderer = brd;
	}

	Object * Renderer::Get()
	{
		return pRenderer;
	}

	void BatchRenderer::FillVertex(std::vector<Vertex>& vb)
	{
		Vertices.insert(Vertices.end(), vb.begin(), vb.end());
	}

	void BatchRenderer::FillVertex(Vertex vb)
	{
		Vertices.emplace_back(vb);
	}

	void BatchRenderer::FillBatchVertex(BatchVertex bv)
	{
		mBatchVertex.emplace_back(bv);
	}

	void BatchRenderer::FillIndex(uint ib)
	{
		Indices.push_back(m_vertexCount + ib);
	}

	void BatchRenderer::FillBegin(UINT objId)
	{
		RecordCurrentVextexStartIndex(ID);
		RecordCurrentIndexStartIndex(ID);
	}

	void BatchRenderer::FillEnd(UINT objId, uint vertexCount, uint indexCount)
	{
		VertexCountAdd(objId, vertexCount);
		IndexCountAdd(objId, indexCount);
		m_IsActive = true;
		bNeedUpdateVertex = true;
	}

	BatchRenderer::BatchRenderer()
	{
		m_vertexCount = 0;
		bNeedUpdateVertex = false;
		m_indexCount = 0;
		CreateBehaviour();
	}

	void BatchRenderer::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Renderer);
		setBehaviourDefaultValue();
	}

	void BatchRenderer::setBehaviourDefaultValue()
	{
		Object::setBehaviourDefaultValue();
	}

	BatchRenderer::~BatchRenderer()
	{
		m_objRendererBuffers.clear();
	}

	DWORD BatchRenderer::RecordCurrentVextexStartIndex(UINT objId)
	{
		m_objRendererBuffers[objId].VertextStartIndex = m_vertexCount;
		return m_vertexCount;
	}

	DWORD BatchRenderer::RecordCurrentIndexStartIndex(UINT objId)
	{
		m_objRendererBuffers[objId].IndexStartIndex = m_indexCount;
		return m_indexCount;
	}

	void BatchRenderer::VertexCountAdd(UINT objId, uint vertexCount)
	{
		m_objRendererBuffers[objId].VertextNumber = vertexCount;
		m_vertexCount += vertexCount;
	}

	void BatchRenderer::IndexCountAdd(UINT objId, uint indexCount)
	{
		m_objRendererBuffers[objId].IndexNumber = indexCount;
		m_indexCount += indexCount;
	}

	void BatchRenderer::RemoveInRenderer(UINT objId)
	{
		if (IsStaticDraw)
		{
			std::map<UINT, RendererBuffer>::iterator vbuffer = m_objRendererBuffers.find(objId);
			if (vbuffer == m_objRendererBuffers.end())
			{
				return;
			}
			for (auto & m_objVextexBuffer : m_objRendererBuffers)
			{
				if (m_objVextexBuffer.second.VertextStartIndex > vbuffer->second.VertextStartIndex)
				{
					m_objVextexBuffer.second.VertextStartIndex -= vbuffer->second.VertextNumber;
					m_objVextexBuffer.second.IndexStartIndex -= vbuffer->second.IndexNumber;
				}
			}
			Vertices.erase(Vertices.begin() + vbuffer->second.VertextStartIndex, Vertices.begin() + vbuffer->second.VertextStartIndex + vbuffer->second.VertextNumber);
			if (!mBatchVertex.empty())
			{
				mBatchVertex.erase(mBatchVertex.begin() + vbuffer->second.VertextStartIndex, mBatchVertex.begin() + vbuffer->second.VertextStartIndex + vbuffer->second.VertextNumber);
			}

			Indices.erase(Indices.begin() + vbuffer->second.IndexStartIndex, Indices.begin() + vbuffer->second.IndexStartIndex + vbuffer->second.IndexNumber);
			for (int i = 0; i < Indices.size(); i++)
			{
				if (i >= vbuffer->second.IndexStartIndex)
				{
					Indices[i] -= vbuffer->second.VertextNumber;
				}
			}
			m_vertexCount -= vbuffer->second.VertextNumber;
			m_indexCount -= vbuffer->second.IndexNumber;
			m_objRendererBuffers.erase(vbuffer);
			m_nIndexSize = Indices.size();
			bNeedUpdateVertex = true;
		}
		else
		{
			m_IsActive = false;
		}
	}
	
	RendererBuffer* BatchRenderer::GetRendererBuffer(UINT objID)
	{
		if (m_objRendererBuffers.find(objID) == m_objRendererBuffers.end())
		{
			return nullptr;
		}
		return &m_objRendererBuffers[objID];
	}

	void BatchRenderer::TransformChange()
	{
		
	}
	
}
