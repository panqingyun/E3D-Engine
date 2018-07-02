// 
//  E3DCubeMapTexture.hpp
// 
//  Created by 潘庆云 on 2017/5/9.

#ifndef E3DCubeMapTexture_hpp
#define E3DCubeMapTexture_hpp

#include "E3DTexture.hpp"

namespace E3DEngine
{
	class CubeMapTexture : public Texture
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
