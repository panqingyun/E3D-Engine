#ifndef __E3D_RENDERMANAGER_HPP__
#define __E3D_RENDERMANAGER_HPP__

#include "src/Source/Interface.h"
#include "src/Object/E3DRenderObject.hpp"
#include "E3DRender.hpp"

namespace E3DEngine
{
	class E3D_EXPORT_DLL RendererManager : public IManager
	{
	public:
		virtual Renderer * CreateVertexRender(int materialID);
		virtual Renderer * GetRenderer(int materialID, RENDER_TYPE type = NORMAL);
		virtual Renderer * GenRender();
		virtual void AddRenderer(int materialID, Renderer * rd);
		virtual void Cleanup();
	protected:
		std::map<int, Renderer*> m_mapVertexBuffers;
	};
}

#endif /* E3DVertexBufferManager_hpp */
