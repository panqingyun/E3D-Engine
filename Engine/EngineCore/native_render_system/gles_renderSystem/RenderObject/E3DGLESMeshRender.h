#pragma once
#include "E3DGLESRenderManager.hpp"
#include <src/Mesh/E3DBone.hpp>

namespace E3DEngine
{
	class GLES_MeshRender : public MeshRender
	{
	public:
		GLES_MeshRender()
		{
			render = new GLES_Renderer;
		}
		virtual ~GLES_MeshRender() override
		{
			SAFE_DELETE(render);
		}
		
	public:
		virtual void FillVertex(Vertex vb);
		virtual void FillIndex(uint ib);
		virtual void FillEnd();
		virtual DWORD RecordCurrentVextexStartIndex(UINT objId);

		virtual DWORD RecordCurrentIndexStartIndex(UINT objId);
		virtual void VertexCountAdd(UINT objId, uint vertexCount);
		virtual void IndexCountAdd(UINT objId, uint indexCount);
		virtual void SetBlendType(DWORD blendType);
		virtual void RemoveInRenderer(UINT objId);
		virtual RendererBuffer* GetRendererBuffer(UINT objID);
		virtual void TransformChange() override;
		virtual void Render(float deltaTime) override;
		virtual void SetDrawModule(DWORD module) override;

	public:
		virtual bool GetActive() { return render->GetActive(); }
		virtual void SetColor(long color);
		virtual void SetIsBillborad(bool isBillboard);
		virtual bool GetIsBillBoard();
		virtual UINT GetDrawModule() { return render->GetDrawModule(); }
		virtual CTransform * GetTransform();
		virtual void SetTransform(CTransform *_transform);
		virtual void CreateNewTransform();
		virtual void SetRenderIndex(DWORD index);

		virtual void SetMaterial(Material *material) { render->SetMaterial(material); }
		virtual void SetCamera(Camera * camera) { render->SetCamera(camera); }
		virtual void SetActive(bool active) { render->SetActive(active); }
		virtual void ClearVertexIndexBuffer() { render->ClearVertexIndexBuffer(); }
	protected:
		GLES_Renderer * render;
	};
}