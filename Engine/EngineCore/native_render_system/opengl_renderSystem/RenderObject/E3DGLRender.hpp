#ifndef __E3D_GL_RENDERER_HPP__
#define __E3D_GL_RENDERER_HPP__

#include <src/RenderSystem/RenderObject/E3DRender.hpp>
#include "../Include/include.h"

namespace E3DEngine
{
	class GL_Renderer : public Renderer
	{
	public:
		GL_Renderer()
		{
			m_nDrawModule = GL_TRIANGLES;
			m_VertexBuffer = 0;
			m_IndexBuffer = 0;
			setVBOs();
		}
		virtual ~GL_Renderer() override
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

		void fillVertexToGPU();

		virtual void TransformChange() override;
		virtual void RemoveInRenderer(UINT objId) override;
		virtual void ClearVertexIndexBuffer() override;

		virtual void Render(float deltaTime) override;
		virtual void ChangeColor(Color4 color) override;
		virtual void SetDrawModule(DWORD module) override;

	protected:
		void updateEngineDefineShaderValue();

		void descPointLight();

		virtual void afterRender(float deltaTime);

	private:
		void setVBOs();
	private:

		GLuint	m_VertexBuffer;
		GLuint	m_IndexBuffer;
		GLuint	m_BatchVertexBuffer;
		GLuint	m_VertexArrayObject;
	};

}

#endif /* E3DVertexBuffer_hpp */
