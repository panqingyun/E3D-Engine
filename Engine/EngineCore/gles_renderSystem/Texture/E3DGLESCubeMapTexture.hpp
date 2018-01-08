//
//  E3DCubeMapTexture.hpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#ifndef E3D_GLES_CubeMapTexture_hpp
#define E3D_GLES_CubeMapTexture_hpp

#include <src/RenderSystem/Texture/E3DCubeMapTexture.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class GLES_CubeMapTexture : public CubeMapTexture
	{
	public:
		void CreateCubeMapTexture(int textureEnum, std::string xPName,
												   std::string xNName,
								  std::string yPName,std::string yNName,std::string zPName,std::string ZNName);
	
		virtual void ActiveBindTexture() override;
	};
}

#endif /* E3DCubeMapTexture_hpp */
