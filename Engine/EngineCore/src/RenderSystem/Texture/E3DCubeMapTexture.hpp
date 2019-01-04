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
		CubeMapTexture();
		void Create(std::string fileName, int selectID);
	protected:
		void createTexture(CubeMapTextureConfig *cubeMap);
		virtual void createCubeMap(Texture2dData *up, Texture2dData *down, Texture2dData *left, Texture2dData *right, Texture2dData *front, Texture2dData *back) = 0;

	};
}

#endif /* E3DCubeMapTexture_hpp */
