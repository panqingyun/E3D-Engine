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
		virtual void AddRenderer(int materialID, Renderer * rd);
		virtual Renderer * GenRender() override;
		virtual void Cleanup() override;

	protected:
		virtual Renderer * newRenderer(RENDER_TYPE type, int materialID) override;
	};
}

#endif /* E3DVertexBufferManager_hpp */
