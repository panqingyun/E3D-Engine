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
		virtual BatchRenderer * CreateRender(Material* material)		= 0;
		virtual BatchRenderer * GenRender()								= 0;
		virtual void AddRenderer(int materialID, BatchRenderer * rd)	= 0;
		virtual BatchRenderer * GetRenderer(int materialID, int vertexSize, RENDER_TYPE type = NORMAL, bool isStatic = false);
		virtual void Cleanup();

	protected:
		virtual BatchRenderer * newRenderer(RENDER_TYPE type, int materialID) = 0;
	protected:
		std::map<int, BatchRenderer*> m_mapVertexBuffers;
		std::map<int, int> m_mapMaterialID2RendererID;
	};
}

#endif /* E3DVertexBufferManager_hpp */
