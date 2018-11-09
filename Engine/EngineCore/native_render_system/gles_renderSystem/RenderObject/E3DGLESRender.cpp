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
#include "../../../src/Source/E3DDebug.h"
#include "../../../src/Source/Application.h"

namespace E3DEngine
{
	
	void GLES_Renderer::updateArrayBuffer()
	{
		if (pMaterial == nullptr)
		{
			return;
		}

		ES2::BindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		pMaterial->UpdateShader(STATIC_VERTEX);
		if (!mBatchVertex.empty())
		{
			ES2::BindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			pMaterial->UpdateShader(DYNAMIC_VERTEX);
		}
		ES2::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	}

	void GLES_Renderer::TransformChange()
	{
		if (!mBatchVertex.empty())
		{
			ES2::BindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			ES2::BufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), mBatchVertex.data(), GL_STREAM_DRAW);
		}
	}

	void GLES_Renderer::RemoveInRenderer(UINT objId)
	{
		Renderer::RemoveInRenderer(objId);
		if (IsStaticDraw)
		{
			fillVertexToGPU();
		}
	}

	void GLES_Renderer::FillEnd(UINT objId, uint vertexCount, uint indexCount)
	{
		Renderer::FillEnd(objId, vertexCount, indexCount);
		if (pMaterial == nullptr)
		{
			assert(false);
		}
		fillVertexToGPU();		
	}

	void GLES_Renderer::fillVertexToGPU()
	{
		ES2::BindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		ES2::BufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
		pMaterial->UpdateShader(STATIC_VERTEX);
		ES2::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		ES2::BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)* Indices.size(), Indices.data(), GL_STATIC_DRAW);
		if (!mBatchVertex.empty())
		{
			ES2::BindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			ES2::BufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), mBatchVertex.data(), GL_STREAM_DRAW);
			pMaterial->UpdateShader(DYNAMIC_VERTEX);
		}

		m_nIndexSize = (DWORD)Indices.size();
		if (!IsStaticDraw)
		{
#ifndef __E3D_EDITOR__
			Indices.clear();
			Vertices.clear();
#endif
		}
	}

	void GLES_Renderer::ClearVertexIndexBuffer()
	{
		ES2::BindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		ES2::BufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), nullptr, GL_STATIC_DRAW);
		ES2::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		ES2::BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* m_nIndexSize, nullptr, GL_STATIC_DRAW);
		ES2::BindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
		ES2::BufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), nullptr, GL_STREAM_DRAW);
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

	void GLES_Renderer::ChangeColor(Color4 color)
	{
#ifdef __E3D_EDITOR__
		ES2::BindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		for (int i = 0; i < m_vertexCount; i++)
		{
			Vertices[i].SetColor(color.r, color.g, color.b, color.a);
		}
		ES2::BufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
#endif
	}

	void GLES_Renderer::Render()
	{
		if (pMaterial == nullptr)
		{
			return;
		}

		if (!m_IsActive || m_nIndexSize == 0)
		{
			return;
		}

		updateEngineDefineShaderValue();

		pMaterial->UseMaterial();

		updateArrayBuffer();
			// 绘制图形
		ES2::DrawElements(m_nDrawModule, (int)m_nIndexSize, GL_UNSIGNED_INT, nullptr);
		afterRender();
	}

	void GLES_Renderer::updateEngineDefineShaderValue()
	{
		pMaterial->mShader->UpdateMatrix4Value(PROJ_MATRIX, pCamera->GetProjectionMatrix());
		pMaterial->mShader->UpdateMatrix4Value(VIEW_MATRIX, pCamera->GetViewMatrix());
		pMaterial->mShader->UpdateMatrix4Value(MODEL_MATRIX, transform->WorldMatrix);
		pMaterial->mShader->UpdateFloatValue(_Time, Application::GetTimeSinceStart());
		pMaterial->mShader->UpdateFloatValue(ROTATION_VEC, transform->RotationEuler.x  * M_PI / 180, transform->RotationEuler.y * M_PI / 180, transform->RotationEuler.z * M_PI / 180);

		DirectionLight * dlight = (DirectionLight *)SceneManager::GetCurrentScene()->GetDirectionalLight();
		if (dlight != nullptr)
		{
			Color4 color = dlight->Color;
			if (!dlight->IsActive)
			{
				color.r = 0; color.g = 0; color.b = 0; color.a = 1;
			}
			pMaterial->mShader->UpdateFloatValue(LIGHT_COLOR, color.r, color.g, color.b, color.a);
			vec3f direction = dlight->GetDirection();
			pMaterial->mShader->UpdateFloatValue(LIGHT_DIR, direction.x, direction.y, direction.z);
		}

		descPointLight();		

		if (pCamera != nullptr)
		{
			vec3f &pos = pCamera->Transform->Position;
			pMaterial->mShader->UpdateFloatValue(CAMERA_POS, pos.x, pos.y, pos.z);
		}
	}


	void GLES_Renderer::descPointLight()
	{
		std::map<UINT, Light*>& plights = SceneManager::GetCurrentScene()->GetPointLights();

		std::vector<float> lightPos;
		std::vector<float> lightColor;
		std::vector<float> lightRange;

		for (auto & pl : plights)
		{			
			if (pl.second->IsActive)
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
			else
			{
				lightColor.emplace_back(0);
				lightColor.emplace_back(0);
				lightColor.emplace_back(0);
				lightColor.emplace_back(1);
			}
		}

		if (!plights.empty())
		{
			pMaterial->mShader->UpdataFloat3ArrayUniform(POINT_LIGHT_POS, lightPos);
			pMaterial->mShader->UpdataFloat4ArrayUniform(POINT_LIGHT_COLOR, lightColor);
			pMaterial->mShader->UpdataFloat1ArrayUniform(POINT_LIGHT_RANGE, lightRange);
		}
	}

	void GLES_Renderer::afterRender()
	{
		if (pMaterial == nullptr)
		{
			return;
		}
		pMaterial->InvalidMaterial();
		ES2::Disable(GL_STENCIL_TEST);
		ES2::BindBuffer(GL_ARRAY_BUFFER, 0);
		ES2::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		ES2::DepthMask(GL_TRUE);
		ES2::Disable(GL_BLEND);
	}


}
