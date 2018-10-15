//
//  E3DVertexBuffer.hpp
//	多个物体可以共用, 目的：动态渲染合批
//  Created by 潘庆云 on 2017/7/17.
//

#ifndef __E3D_GLES_RENDERER_HPP__
#define __E3D_GLES_RENDERER_HPP__

#include <src/RenderSystem/RenderObject/E3DRender.hpp>
#include "../Include/include.h"

namespace E3DEngine
{
	class GLES_Renderer : public Renderer
	{
	public:
		GLES_Renderer()
		{
			m_nDrawModule = GL_TRIANGLES;
			m_VertexBuffer = 0;
			m_IndexBuffer = 0;
			setVBOs();
		}
		virtual ~GLES_Renderer() override
		{
			if (m_VertexBuffer != 0)
			{
				glDeleteBuffers(1, &m_VertexBuffer);
				m_VertexBuffer = 0;
			}
			if (m_IndexBuffer != 0)
			{
				glDeleteBuffers(1, &m_IndexBuffer);
				m_IndexBuffer = 0;
			}
		}
	public:
		virtual void updateArrayBuffer(float deltaTime);
		virtual void FillEnd(UINT objId, uint vertexCount, uint indexCount) override;
		virtual void TransformChange() override;

		virtual void ClearVertexIndexBuffer() override;

		virtual void Render(float deltaTime) override;

		virtual void SetDrawModule(DWORD module) override;

	protected:
		void updateEngineDefineShaderValue();

		void descPointLight();

		virtual void afterRender(float deltaTime);

	private:
		void setVBOs()
		{
			glGenBuffers(1, &m_VertexBuffer);
			glGenBuffers(1, &m_IndexBuffer);
			glGenBuffers(1, &m_BatchVertexBuffer);
		}
	private:

		GLuint	m_VertexBuffer;
		GLuint	m_IndexBuffer;
		GLuint	m_BatchVertexBuffer;
		GLuint	m_VertexArrayObject;
	};

}

#endif /* E3DVertexBuffer_hpp */
