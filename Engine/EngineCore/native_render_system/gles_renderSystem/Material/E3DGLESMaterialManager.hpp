
#ifndef E3D_GLES_MaterialManager_hpp
#define E3D_GLES_MaterialManager_hpp

#include "src/Source/Interface.h"
#include <src/RenderSystem/Material/E3DMaterialManager.hpp>

namespace E3DEngine
{
	class GLES_MaterialManager : public MaterialManager
	{
	public:
		GLES_MaterialManager()
		{
			m_currentMaterialID = 0;
		}
		~GLES_MaterialManager()= default;

	public:
		virtual Material * GetMaterial(int id) override;
		virtual Material * GetMaterial(string path) override;
		Material * CreateMaterial(std::string path) override;
	};
}

#endif
