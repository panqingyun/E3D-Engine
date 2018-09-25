// 
//  E3DCubeMapTexture.hpp
// 
//  Created by 潘庆云 on 2017/5/9.

#ifndef __E3D_CUBE_MAP_TEXTURE_HPP__
#define __E3D_CUBE_MAP_TEXTURE_HPP__

#include "E3DTexture.hpp"

namespace E3DEngine
{
	class EX_PORT CubeMapTexture : public Texture
	{
	public:
		void CreateCubeMapTexture(int textureEnum, std::string xPName,
												   std::string xNName,
								  std::string yPName,std::string yNName,std::string zPName,std::string ZNName);
	
		virtual void ActiveBindTexture() override;

	protected:
		void * createImageData(std::string imageName, int * width, int * height);

		int m_nImageWidth;
		int m_nImageHeight;
		int m_nTextureUniform;
	};
}

#endif /* E3DCubeMapTexture_hpp */
