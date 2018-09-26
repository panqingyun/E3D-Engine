//
//  E3DVertexBuffer.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DGLESRender.hpp"
#include <src/Camera/E3DCamera.h>
#include <src/Object/E3DTransform.hpp>
#include <src/RenderSystem/E3DRenderSystem.hpp>
#include <src/Scene/E3DSceneManager.hpp>
#include <src/Light/E3DLight.hpp>

namespace E3DEngine
{
	
	void GLES_Renderer::updateArrayBuffer(float deltaTime)
	{
		if (pMaterial == nullptr)
		{
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		pMaterial->UpdateShader(STATIC_VERTEX);
		if (!mBatchVertex.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			pMaterial->UpdateShader(DYNAMIC_VERTEX);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	}

	void GLES_Renderer::TransformChange()
	{
		if (!mBatchVertex.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), mBatchVertex.data(), GL_STREAM_DRAW);
		}
	}

	void GLES_Renderer::FillEnd(UINT objId, uint vertexCount, uint indexCount)
	{
		Renderer::FillEnd(objId, vertexCount, indexCount);
		if (pMaterial == nullptr)
		{
			assert(false);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
		pMaterial->UpdateShader(STATIC_VERTEX);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)* Indices.size(), Indices.data(), GL_STATIC_DRAW);
		if (!mBatchVertex.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), mBatchVertex.data(), GL_STREAM_DRAW);
			pMaterial->UpdateShader(DYNAMIC_VERTEX);
		}
	}

	void GLES_Renderer::ClearVertexIndexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* Indices.size(), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), nullptr, GL_STREAM_DRAW);
	}


	void GLES_Renderer::SetDrawModule(DWORD module)
	{
		switch (module)
		{
		case eDM_LINE_STRIP:
			m_nDrawModule = GL_LINE_STRIP;
			break;
		case eDM_TRIANGLE_STRIP:
			m_nDrawModule = GL_TRIANGLE_STRIP;
			break;
		case eDM_TRIANGLES:
			m_nDrawModule = GL_TRIANGLES;
			break;
		case  eDM_LINES:
			m_nDrawModule = GL_LINES;
			break;
		case eDM_POINTS:
			m_nDrawModule = GL_POINTS;
			break;
		default:
			m_nDrawModule = GL_TRIANGLES;
			break;
		}
	}

	void GLES_Renderer::Render(float deltaTime)
	{
		if (pMaterial == nullptr)
		{
			return;
		}

		if (Vertices.empty())
		{
			return;
		}
		m_nIndexSize = (DWORD)Indices.size();
		pMaterial->UseMaterial();

		updateArrayBuffer(deltaTime);

		updateEngineDefineShaderValue();

		// 绘制图形
		glDrawElements(m_nDrawModule, (int)m_nIndexSize, GL_UNSIGNED_INT, nullptr);
		int err = glGetError();
		afterRender(deltaTime);
	}

	void GLES_Renderer::updateEngineDefineShaderValue()
	{
		pMaterial->mShader->UpdateMatrix4Value(PROJ_MATRIX, pCamera->GetProjectionMatrix());
		pMaterial->mShader->UpdateMatrix4Value(VIEW_MATRIX, pCamera->GetViewMatrix());

		pMaterial->mShader->UpdateMatrix4Value(MODEL_MATRIX, GetTransform()->WorldMatrix);
		pMaterial->mShader->UpdateFloatValue(ROTATION_VEC, GetTransform()->RotationEuler.x  * M_PI / 180, GetTransform()->RotationEuler.y * M_PI / 180, GetTransform()->RotationEuler.z * M_PI / 180);

		DirectionLight * dlight = (DirectionLight *)SceneManager::GetCurrentScene()->GetDirectionalLight();
		if (dlight != nullptr)
		{
			pMaterial->mShader->UpdateFloatValue(LIGHT_COLOR, dlight->Color.r, dlight->Color.g, dlight->Color.b, dlight->Color.a);
			pMaterial->mShader->UpdateFloatValue(LIGHT_DIR, dlight->Transform->Position.x, dlight->Transform->Position.y, dlight->Transform->Position.z);
		}

		std::map<UINT, Light*>& plights = SceneManager::GetCurrentScene()->GetPointLights();
		if (plights.size() != 0)
		{
			std::vector<float> lightPos;
			std::vector<float> lightColor;
			std::vector<float> lightRange;
			for (auto & pl : plights)
			{
				lightPos.emplace_back(pl.second->Transform->Position.x);
				lightPos.emplace_back(pl.second->Transform->Position.y);
				lightPos.emplace_back(pl.second->Transform->Position.z);
				lightColor.emplace_back(pl.second->Color.r);
				lightColor.emplace_back(pl.second->Color.g);
				lightColor.emplace_back(pl.second->Color.b);
				lightColor.emplace_back(pl.second->Color.a);
				lightRange.emplace_back(static_cast<PointLight*>(pl.second)->Range);
			}
			pMaterial->mShader->UpdataFloat3ArrayUniform(POINT_LIGHT_POS, lightPos);
			pMaterial->mShader->UpdataFloat4ArrayUniform(POINT_LIGHT_COLOR, lightColor);
			pMaterial->mShader->UpdataFloat1ArrayUniform(POINT_LIGHT_RANGE, lightRange);
		}
		if (pCamera != nullptr)
		{
			vec3f &pos = pCamera->Transform->Position;
			pMaterial->mShader->UpdateFloatValue(CAMERA_POS, pos.x, pos.y, pos.z);
		}
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
