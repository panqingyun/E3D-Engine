//
//	按照材质ID 索引顶点缓存，同一材质ID的物体顶点都输出到同一个顶点缓存中，然后统一绘制
//  Created by 潘庆云 on 2017/7/19.
//

#ifndef E3D_GLES_RENDER_BufferManager_hpp
#define E3D_GLES_RENDER_BufferManager_hpp

#include <src/Source/Interface.h>
#include <src/RenderSystem/RenderObject/E3DRenderManager.hpp>
#include "../Include/Include.h"

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
		virtual void prepareRender(float deltaTime) override;

		virtual void TransformChange() override;

		virtual void ClearVertexIndexBuffer() override;

		virtual void Render(float deltaTime) override;

		virtual void SetDrawModule(DWORD module) override;

	protected:
		void updateEngineDefineShaderValue();
		virtual void afterRender(float deltaTime) override;

	private:
		void setVBOs()
		{
			glGenBuffers(1, &m_VertexBuffer);
			glGenBuffers(1, &m_IndexBuffer);
		}

		GLuint	m_VertexBuffer;
		GLuint	m_IndexBuffer;
		GLuint	m_VertexArrayObject;
	};

	class GLES_RendererManager : public RendererManager
	{
	public:
		virtual Renderer * CreateVertexRender(int materialID) override;
		virtual Renderer * GetRenderer(int materialID, RENDER_TYPE type = NORMAL) override;
		virtual void AddRenderer(int materialID, Renderer * rd);
		virtual Renderer * GenRender() override;
	private:
		std::map<int, Renderer*> m_mapVertexBuffers;
	};
}

#endif /* E3DVertexBufferManager_hpp */
