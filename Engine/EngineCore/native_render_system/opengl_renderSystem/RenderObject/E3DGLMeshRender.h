#pragma once
#include "E3DGLRender.hpp"
#include <src/Mesh/E3DMeshRender.h>

namespace E3DEngine
{
	class GL_MeshRender : public MeshRender
	{
	public:
		GL_MeshRender();
		virtual ~GL_MeshRender() override;
		
	public:
		virtual void FillBegin(UINT objId);
		virtual void FillVertex(Vertex vb);
		virtual void FillIndex(uint ib);
		virtual void FillEnd(UINT objId, uint vertexCount, uint indexCount);
		virtual void RemoveInRenderer(UINT objId);
		virtual RendererBuffer* GetRendererBuffer(UINT objID);
		virtual void TransformChange() override;
		virtual void Render() override;
		virtual void SetDrawModule(DWORD module) override;

	public:
		virtual UINT GetDrawModule();
		virtual CTransform * GetTransform();
		virtual void SetTransform(CTransform *_transform);
		virtual void CreateNewTransform();
		//virtual void SetRenderIndex(DWORD index) override;

		virtual void SetMaterial(Material *material);
		virtual void SetLayerMask(DWORD layer);
		virtual Material *GetMaterial();
		virtual void SetCamera(Camera * camera);
		virtual void ClearVertexIndexBuffer();
		virtual Camera *GetCamera() override;
	};
}
