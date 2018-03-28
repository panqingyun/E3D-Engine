#pragma once
#include "E3DGLESRenderManager.hpp"
#include <src/Mesh/E3DMeshRender.h>

namespace E3DEngine
{
	class GLES_MeshRender : public MeshRender
	{
	public:
		GLES_MeshRender()
		{
			pRender = new GLES_Renderer;
		}
		virtual ~GLES_MeshRender() override
		{
			SAFE_DELETE(pRender);
		}
		
	public:
		virtual void FillVertex(Vertex vb);
		virtual void FillIndex(uint ib);
		virtual void FillEnd();
		virtual DWORD RecordCurrentVextexStartIndex(UINT objId);

		virtual DWORD RecordCurrentIndexStartIndex(UINT objId);
		virtual void VertexCountAdd(UINT objId, uint vertexCount);
		virtual void IndexCountAdd(UINT objId, uint indexCount);
		virtual void RemoveInRenderer(UINT objId);
		virtual RendererBuffer* GetRendererBuffer(UINT objID);
		virtual void TransformChange() override;
		virtual void Render(float deltaTime) override;
		virtual void SetDrawModule(DWORD module) override;

	public:
		virtual bool GetActive() { return pRender->GetActive(); }
		virtual void SetColor(long color);
		virtual void SetIsBillborad(bool isBillboard);
		virtual bool GetIsBillBoard();
		virtual UINT GetDrawModule() { return pRender->GetDrawModule(); }
		virtual CTransform * GetTransform();
		virtual void SetTransform(CTransform *_transform);
		virtual void CreateNewTransform();
		//virtual void SetRenderIndex(DWORD index) override;

		virtual void SetMaterial(Material *material);
		virtual Material *GetMaterial() { return pRender->GetMaterial(); }
		virtual void SetCamera(Camera * camera) { pRender->SetCamera(camera); }
		virtual void SetActive(bool active) { pRender->SetActive(active); }
		virtual void ClearVertexIndexBuffer() { pRender->ClearVertexIndexBuffer(); }
	protected:
		GLES_Renderer * pRender;
	};
}
