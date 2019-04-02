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
	class GLES_Renderer : public BatchRenderer
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
				_GL_ES_2::DeleteBuffers(1, &m_VertexBuffer);
				m_VertexBuffer = 0;
			}
			if (m_IndexBuffer != 0)
			{
				_GL_ES_2::DeleteBuffers(1, &m_IndexBuffer);
				m_IndexBuffer = 0;
			}
		}
	public:
		virtual void updateArrayBuffer();
		virtual void FillEnd(UINT objId, uint vertexCount, uint indexCount) override;

		virtual void TransformChange() override;
		virtual void RemoveInRenderer(UINT objId) override;
		virtual void ClearVertexIndexBuffer() override;

		virtual void Render() override;

		virtual void SetDrawModule(DWORD module) override;
		virtual void ChangeColor(Color4 color) override;
	protected:
		void updateEngineDefineShaderValue();

		void descPointLight();
		void fillVertexToGPU();

		virtual void afterRender();
		void drawSelectFrame();

	private:
		void setVBOs()
		{
			_GL_ES_2::GenBuffers(1, &m_VertexBuffer);
			_GL_ES_2::GenBuffers(1, &m_IndexBuffer);
			_GL_ES_2::GenBuffers(1, &m_BatchVertexBuffer);
		}
	private:

		GLuint	m_VertexBuffer;
		GLuint	m_IndexBuffer;
		GLuint	m_BatchVertexBuffer;
		GLuint	m_VertexArrayObject;
	};

}

#endif /* E3DVertexBuffer_hpp */
