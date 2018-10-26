
#ifndef E3D_GLES_MaterialManager_hpp
#define E3D_GLES_MaterialManager_hpp

#include "src/Source/Interface.h"
#include <src/RenderSystem/Material/E3DMaterialManager.hpp>

namespace E3DEngine
{
	class GLES_MaterialManager : public MaterialManager
	{
	public:
		GLES_MaterialManager();
		~GLES_MaterialManager() = default; 

	protected:
		virtual Material * createMatrerial();
	};
}

#endif
