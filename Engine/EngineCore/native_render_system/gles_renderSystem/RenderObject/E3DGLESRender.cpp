//
//  E3DVertexBuffer.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DGLESRenderManager.hpp"
#include <src/Camera/E3DCamera.h>
#include <src/Object/E3DTransform.hpp>

namespace E3DEngine
{
	
	void GLES_Renderer::prepareRender(float deltaTime)
	{
		if (pMaterial == nullptr)
		{
			return;
		}
		pMaterial->UseProgram();

		m_nIndexSize = (uint)Indices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		
		if (EnableDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
		}
		if (pMaterial->blendType == eBlendType_One)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}
        else if(pMaterial->blendType == eBlendType_Text)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
		else
		{
#ifdef __IOS__
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif // __IOS__
			
		}
//
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_ALPHA);

	}

	void GLES_Renderer::TransformChange()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), Vertices.data(), GL_STREAM_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* Indices.size(), Indices.data(), GL_STREAM_DRAW);
	}

	void GLES_Renderer::ClearVertexIndexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		if (!m_bIsBufferData)
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), nullptr, GL_STREAM_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* Indices.size(), nullptr, GL_STREAM_DRAW);
		}
	}

	void GLES_Renderer::Render(float deltaTime)
	{
		prepareRender(deltaTime);
		if (pMaterial == nullptr)
		{
			return;
		}

		if (Vertices.empty())
		{
			return;
		}

		pMaterial->pShader->UpdateMatrix4Value(PROJ_MATRIX, pCamera->GetProjectionMatrix());
		pMaterial->pShader->UpdateMatrix4Value(VIEW_MATRIX, pCamera->GetViewMatrix());
		pMaterial->pShader->UpdateMatrix4Value(MODEL_MATRIX, GetTransform()->WorldMatrix);
		pMaterial->pShader->UpdateFloatValue(ROTATION_VEC, GetTransform()->RotationEuler.x, GetTransform()->RotationEuler.y, GetTransform()->RotationEuler.z);
		if ( pCamera != nullptr)
		{
			vec3f &pos = pCamera->Transform->Position;
			pMaterial->pShader->UpdateFloatValue(CAMERA_POS, pos.x, pos.y, pos.z);
		}

		pMaterial->UseMaterial();

		// 绘制图形
		glDrawElements(m_nDrawModule, (int)m_nIndexSize, GL_UNSIGNED_SHORT, nullptr);
		int err = glGetError();
		afterRender(deltaTime);
	}

	void GLES_Renderer::afterRender(float deltaTime)
	{
		if (pMaterial == nullptr)
		{
			return;
		}
		pMaterial->InvalidMaterial();
		glDisable(GL_STENCIL_TEST);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}


}
