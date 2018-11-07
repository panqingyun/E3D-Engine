//
//  E3DCubeMapTexture.hpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#ifndef E3D_GL_CubeMapTexture_hpp
#define E3D_GL_CubeMapTexture_hpp

#include <src/RenderSystem/Texture/E3DCubeMapTexture.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class GL_CubeMapTexture : public CubeMapTexture
	{
	public:
		~GL_CubeMapTexture();
	protected:
		virtual void createCubeMap(TextureData *up, TextureData *down, TextureData *left, TextureData *right, TextureData *front, TextureData *back) override;
		void changeRgbModule(TextureData *data);

	protected:
		GLuint			m_nTextureUniform;
		GLuint			m_nTextureIndex;
	};
}

#endif /* E3DCubeMapTexture_hpp */
