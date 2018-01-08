//
//  E3DCubeMapTexture.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DCubeMapTexture.hpp"
#include "../E3DRenderSystem.hpp"

namespace E3DEngine
{
	void * CubeMapTexture::createImageData(std::string imageName, int *width, int *height)
	{
		stImageData * data = GetRenderSystem()->GetTextureDataManager()->CreateTextureData(imageName);
		*width	= data->width;
		*height = data->height;
		return data->data;
	}
	
	void CubeMapTexture::CreateCubeMapTexture(int textureEnum,
											  std::string xPName,
											  std::string xNName,
											  std::string yPName,
											  std::string yNName,
											  std::string zPName,
											  std::string zNName)
	{
		
	}
	
	void CubeMapTexture::ActiveBindTexture()
	{
		
	}
}
