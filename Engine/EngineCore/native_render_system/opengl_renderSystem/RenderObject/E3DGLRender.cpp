//
//  E3DVertexBuffer.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DGLRender.hpp"
#include <src/Camera/E3DCamera.h>
#include <src/Object/E3DTransform.hpp>
#include <src/RenderSystem/E3DRenderSystem.hpp>
#include <src/Scene/E3DSceneManager.hpp>
#include <src/Light/E3DLight.hpp>
#include "../../../src/Source/E3DDebug.h"
#include "../Shader/E3DGLShader.hpp"
#include "../Material/E3DGLMaterial.hpp"
#include "../../../src/Source/Application.h"
#include "../E3DGL_RenderSystem.h"

namespace E3DEngine
{
	
	void GL_Renderer::updateArrayBuffer()
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

	void GL_Renderer::TransformChange()
	{
		if (!mBatchVertex.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			BatchVertex * vert = (BatchVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
			memcpy(vert, mBatchVertex.data(), sizeof(BatchVertex)* mBatchVertex.size());
			glUnmapBuffer(GL_ARRAY_BUFFER);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), mBatchVertex.data(), GL_STREAM_DRAW);
		}
	}

	void GL_Renderer::RemoveInRenderer(UINT objId)
	{
		BatchRenderer::RemoveInRenderer(objId);
		if (IsStaticDraw)
		{
			fillVertexToGPU();
		}
	}

	void GL_Renderer::FillEnd(UINT objId, uint vertexCount, uint indexCount)
	{
		BatchRenderer::FillEnd(objId, vertexCount, indexCount);
		if (pMaterial == nullptr)
		{
			assert(false);
		}
		fillVertexToGPU();
	}

	void GL_Renderer::fillVertexToGPU()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
		pMaterial->UpdateShader(STATIC_VERTEX);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)* Indices.size(), Indices.data(), GL_STREAM_DRAW);
		if (!mBatchVertex.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), mBatchVertex.data(), GL_STREAM_DRAW);
			pMaterial->UpdateShader(DYNAMIC_VERTEX);
		}
		m_nIndexSize = (DWORD)Indices.size();
		if (!IsStaticDraw)
		{
			Vertices.clear();
			Indices.clear();
		}
	}

	void GL_Renderer::ClearVertexIndexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), nullptr, GL_STREAM_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* Indices.size(), nullptr, GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_BatchVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(BatchVertex)* mBatchVertex.size(), nullptr, GL_STREAM_DRAW);
	}


	void GL_Renderer::SetDrawModule(DWORD module)
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

	void GL_Renderer::Render()
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
#ifdef __E3D_EDITOR__
		if (m_IsSelected)
		{
			glClearStencil(0);
			glClear(GL_STENCIL_BUFFER_BIT);
		}
#endif
		if (pCamera->GetIsShadowCamera())
		{
			glDepthMask(GL_TRUE);
		}
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		// 绘制图形
		glDrawElements(m_nDrawModule, (int)m_nIndexSize, GL_UNSIGNED_INT, nullptr);
		afterRender();
#ifdef __E3D_EDITOR__
		drawSelectFrame();
#endif
	}


	void GL_Renderer::ChangeColor(Color4 color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		Vertex *verts = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
		for (int i = 0; i < m_vertexCount; i++)
		{
			verts[i].SetColor(color.r, color.g, color.b, color.a);
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GL_Renderer::updateEngineDefineShaderValue()
	{
		pMaterial->mShader->UpdateMatrix4Value(PROJ_MATRIX, pCamera->GetProjectionMatrix());
		pMaterial->mShader->UpdateMatrix4Value(VIEW_MATRIX, pCamera->GetViewMatrix());
		pMaterial->mShader->UpdateFloatValue(_Time, Application::GetTimeSinceStart());
		pMaterial->mShader->UpdateMatrix4Value(MODEL_MATRIX, transform->WorldMatrix);
		pMaterial->mShader->UpdateFloatValue(ROTATION_VEC, transform->RotationEuler.x  * M_PI / 180, transform->RotationEuler.y * M_PI / 180, transform->RotationEuler.z * M_PI / 180);
		pMaterial->mShader->UpdateFloatValue(SCALE_VEC, transform->Scale.x, transform->Scale.y, transform->Scale.z);

		DirectionLight * dlight = (DirectionLight *)SceneManager::GetCurrentScene()->GetDirectionalLight();
		if (dlight != nullptr)
		{
			Color4 color = dlight->mGameObject->Color;
			if (!dlight->mGameObject->IsActive)
			{
				color.r = 0; color.g = 0; color.b = 0; color.a = 1;
			}
			pMaterial->mShader->UpdateFloatValue(LIGHT_COLOR, color.r, color.g, color.b, color.a);
			vec3f direction = dlight->GetDirection();
			pMaterial->mShader->UpdateFloatValue(LIGHT_DIR, direction.x, direction.y, direction.z);
			if (object_cast<bool>(Light::GetCreateShadow(dlight)))
			{
				pMaterial->GetShader()->UpdateMatrix4Value(LIGHT_PROJ_MAT, dlight->GetShadowCamera()->GetProjectionMatrix());
				pMaterial->GetShader()->UpdateMatrix4Value(LIGHT_VIEW_MAT, dlight->GetShadowCamera()->GetViewMatrix());
				pMaterial->GetShader()->UpdateSampler2D(LIGHT_DEPTH_TEX, dlight->GetShadowCamera()->GetRenderTexture(),pMaterial->GetTextureCount());
			}
		}

		descPointLight();		

		if (pCamera != nullptr)
		{
			vec3f &pos = pCamera->Transform->Position;
			pMaterial->mShader->UpdateFloatValue(CAMERA_POS, pos.x, pos.y, pos.z);
		}
	}


	void GL_Renderer::descPointLight()
	{
		std::map<UINT, Light*>& plights = SceneManager::GetCurrentScene()->GetPointLights();

		std::vector<float> lightPos;
		std::vector<float> lightColor;
		std::vector<float> lightRange;

		for (auto & pl : plights)
		{			
			if (pl.second->mGameObject->IsActive)
			{
				lightPos.emplace_back(pl.second->Transform->Position.x);
				lightPos.emplace_back(pl.second->Transform->Position.y);
				lightPos.emplace_back(pl.second->Transform->Position.z);
				lightColor.emplace_back(pl.second->mGameObject->Color.r);
				lightColor.emplace_back(pl.second->mGameObject->Color.g);
				lightColor.emplace_back(pl.second->mGameObject->Color.b);
				lightColor.emplace_back(pl.second->mGameObject->Color.a);
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

	void GL_Renderer::afterRender()
	{
		if (pMaterial == nullptr)
		{
			return;
		}
		static_cast<GL_Material*>(pMaterial)->DisableVertexAttrib(STATIC_VERTEX);
		if (!mBatchVertex.empty())
		{
			static_cast<GL_Material*>(pMaterial)->DisableVertexAttrib(DYNAMIC_VERTEX);
		}
		pMaterial->InvalidMaterial();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}


	void GL_Renderer::setVBOs()
	{
		glGenBuffers(1, &m_VertexBuffer);
		glGenBuffers(1, &m_IndexBuffer);
		glGenBuffers(1, &m_BatchVertexBuffer);
	}

#ifdef __E3D_EDITOR__
	void GL_Renderer::drawSelectFrame()
	{
		if (m_IsSelected && !pCamera->GetIsShadowCamera())
		{
			vec3f scale = transform->GetScale();
			Shader *pShader = pMaterial->GetShader();
			pMaterial->mShader = GL_RenderSystem::GetRenderSystem()->GetShaderManager()->GetShader("../Data/Material/shader/frame.shader");
			updateEngineDefineShaderValue();
			pMaterial->UseMaterial();
			updateArrayBuffer();
			glEnable(GL_STENCIL_TEST);
			glStencilMask(0x00);
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			//glDepthMask(GL_FALSE);
			glEnable(GL_DEPTH_TEST);
			glDrawElements(m_nDrawModule, (int)m_nIndexSize, GL_UNSIGNED_INT, nullptr);
			afterRender();
			pMaterial->mShader = pShader;
		}
	}
#endif
}
