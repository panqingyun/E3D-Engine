#include "E3DGLESMeshRender.h"

namespace E3DEngine
{
	/*void MeshRender::initBoneMatrix()
	{
	VecBoneMatrix.resize( m_pMeshBuffer->VecBoneMatrix.size());
	for (map<string, Bone*>::iterator it = m_pMeshBuffer->BoneMapping.begin(); it != m_pMeshBuffer->BoneMapping.end(); ++it)
	{
	Bone * bone = new Bone(it->second);
	BoneMapping[it->first] = bone;

	VecBoneMatrix[it->second->ID] = &bone->Transform->WorldMatrix;
	}
	}*/

	void GLES_MeshRender::FillVertex(Vertex vb)
	{
		render->FillVertex(vb);
	}


	void GLES_MeshRender::FillIndex(uint ib)
	{
		render->FillIndex(ib);
	}


	void GLES_MeshRender::FillEnd()
	{
		render->FillEnd();
	}


	DWORD GLES_MeshRender::RecordCurrentVextexStartIndex(UINT objId)
	{
		return render->RecordCurrentVextexStartIndex(objId);
	}


	DWORD GLES_MeshRender::RecordCurrentIndexStartIndex(UINT objId)
	{
		return render->RecordCurrentIndexStartIndex(objId);
	}


	void GLES_MeshRender::VertexCountAdd(UINT objId, uint vertexCount)
	{
		render->VertexCountAdd(objId, vertexCount);
	}


	void GLES_MeshRender::IndexCountAdd(UINT objId, uint indexCount)
	{
		render->IndexCountAdd(objId, indexCount);
	}


	void GLES_MeshRender::SetBlendType(DWORD blendType)
	{
		render->SetBlendType(blendType);
	}


	void GLES_MeshRender::RemoveInRenderer(UINT objId)
	{
		render->RemoveInRenderer(objId);
	}


	E3DEngine::RendererBuffer* GLES_MeshRender::GetRendererBuffer(UINT objID)
	{
		return render->GetRendererBuffer(objID);
	}


	void GLES_MeshRender::TransformChange()
	{
		render->TransformChange();
	}


	void GLES_MeshRender::Render(float deltaTime)
	{
		render->Render(deltaTime);
	}

	void GLES_MeshRender::SetDrawModule(DWORD module)
	{
		render->SetDrawModule(module);
	}


	void GLES_MeshRender::SetColor(long color)
	{
		render->SetColor(color);
	}


	void GLES_MeshRender::SetIsBillborad(bool isBillboard)
	{
		render->SetIsBillborad(isBillboard);
	}


	bool GLES_MeshRender::GetIsBillBoard()
	{
		return render->GetIsBillBoard();
	}


	E3DEngine::CTransform * GLES_MeshRender::GetTransform()
	{
		return render->GetTransform();
	}


	void GLES_MeshRender::SetTransform(CTransform *_transform)
	{
		render->SetTransform(_transform);
	}


	void GLES_MeshRender::CreateNewTransform()
	{
		render->CreateNewTransform();
	}

/*
	void GLES_MeshRender::SetRenderIndex(DWORD index)
	{
		render->SetRenderIndex(index);
	}
*/

	void GLES_MeshRender::SetMaterial(Material *material)
	{
		render->SetMaterial(material);
	}

}