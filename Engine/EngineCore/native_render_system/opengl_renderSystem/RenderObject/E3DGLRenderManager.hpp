#ifndef E3D_GL_RENDER_BufferManager_hpp
#define E3D_GL_RENDER_BufferManager_hpp

#include <src/Source/Interface.h>
#include <src/RenderSystem/RenderObject/E3DRender.hpp>
#include "../Include/Include.h"
#include <src/RenderSystem/RenderObject/E3DRenderManager.hpp>

namespace E3DEngine
{
	class GL_RendererManager : public RendererManager
	{
	public:
		virtual Renderer * GetRenderer(int materialID, int vertexSize, RENDER_TYPE type = NORMAL, bool isStatic = false) override;

		virtual void AddRenderer(int materialID, Renderer * rd);
		virtual Renderer * GenRender() override;
		virtual void Cleanup() override;

	private:
		Renderer * newRenderer(RENDER_TYPE type, int materialID);

	private:
		std::map<int, Renderer*> m_mapVertexBuffers;
		std::map<int, int> m_mapMaterialID2RendererID;
	};
}

#endif /* E3DVertexBufferManager_hpp */
