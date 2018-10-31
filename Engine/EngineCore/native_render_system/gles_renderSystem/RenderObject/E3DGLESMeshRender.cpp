#include "E3DGLESMeshRender.h"

namespace E3DEngine
{

	void GLES_MeshRender::FillBegin(UINT objId)
	{
		pRender->FillBegin(objId);
	}

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
		pRender->FillVertex(vb);
	}


	void GLES_MeshRender::FillIndex(uint ib)
	{
		pRender->FillIndex(ib);
	}


	void GLES_MeshRender::FillEnd(UINT objId, uint vertexCount, uint indexCount)
	{
		pRender->FillEnd(objId, vertexCount, indexCount);
	}

	void GLES_MeshRender::RemoveInRenderer(UINT objId)
	{
		pRender->RemoveInRenderer(objId);
	}


	E3DEngine::RendererBuffer* GLES_MeshRender::GetRendererBuffer(UINT objID)
	{
		return pRender->GetRendererBuffer(objID);
	}


	void GLES_MeshRender::TransformChange()
	{
		pRender->TransformChange();
	}


	void GLES_MeshRender::Render(float deltaTime)
	{
		pRender->Render(deltaTime);
	}

	void GLES_MeshRender::SetDrawModule(DWORD module)
	{
		pRender->SetDrawModule(module);
	}

	E3DEngine::CTransform * GLES_MeshRender::GetTransform()
	{
		return pRender->GetTransform();
	}


	void GLES_MeshRender::SetTransform(CTransform *_transform)
	{
		pRender->SetTransform(_transform);
	}


	void GLES_MeshRender::CreateNewTransform()
	{
		pRender->CreateNewTransform();
	}

/*
	void GLES_MeshRender::SetRenderIndex(DWORD index)
	{
		render->SetRenderIndex(index);
	}
*/

	void GLES_MeshRender::SetMaterial(Material *material)
	{
		pRender->SetMaterial(material);
	}


	E3DEngine::Camera * GLES_MeshRender::GetCamera()
	{
		return pRender->GetCamera();
	}

}
