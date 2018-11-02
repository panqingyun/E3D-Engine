//
//	按照材质ID 索引顶点缓存，同一材质ID的物体顶点都输出到同一个顶点缓存中，然后统一绘制
//  Created by 潘庆云 on 2017/7/19.
//

#ifndef E3D_GLES_RENDER_BufferManager_hpp
#define E3D_GLES_RENDER_BufferManager_hpp

#include <src/Source/Interface.h>
#include <src/RenderSystem/RenderObject/E3DRender.hpp>
#include "../Include/Include.h"
#include <src/RenderSystem/RenderObject/E3DRenderManager.hpp>

namespace E3DEngine
{
	class GLES_RendererManager : public RendererManager
	{
	public:
		virtual void AddRenderer(int materialID, Renderer * rd);
		virtual Renderer * GenRender() override;
		virtual void Cleanup() override;

	protected:
		virtual Renderer * newRenderer(RENDER_TYPE type, int materialID) override;

	private:
		std::map<int, Renderer*> m_mapVertexBuffers;
		std::map<int, int> m_mapMaterialID2RendererID;
	};
}

#endif /* E3DVertexBufferManager_hpp */
