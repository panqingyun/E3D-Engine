// 
//  E3DCubeMapTexture.hpp
// 
//  Created by 潘庆云 on 2017/5/9.

#ifndef __E3D_CUBE_MAP_TEXTURE_HPP__
#define __E3D_CUBE_MAP_TEXTURE_HPP__

#include "E3DTexture.hpp"

namespace E3DEngine
{
	class CubeMapTextureConfig;
	class E3D_EXPORT_DLL CubeMapTexture : public Texture
	{
	public:
		void Create(std::string fileName, int selectID);
	
		virtual void ActiveBindTexture() override;

	protected:
		void createTexture(CubeMapTextureConfig *cubeMap);
		virtual void createCubeMap(TextureData *up, TextureData *down, TextureData *left, TextureData *right, TextureData *front, TextureData *back);

	};
}

#endif /* E3DCubeMapTexture_hpp */
