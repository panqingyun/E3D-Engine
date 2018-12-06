
#ifndef E3D_GL_MaterialManager_hpp
#define E3D_GL_MaterialManager_hpp

#include "src/Source/Interface.h"
#include <src/RenderSystem/Material/E3DMaterialManager.hpp>

namespace E3DEngine
{
	class GL_MaterialManager : public MaterialManager
	{
	public:
		GL_MaterialManager();
		virtual ~GL_MaterialManager() = default;

	protected:
		virtual Material * createMatrerial() override;
	};
}

#endif
