//
//  E3DCubeMapTexture.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DGLESCubeMapTexture.hpp"
#include <src/Source/E3DDebug.h>

namespace E3DEngine
{		
	void GLES_CubeMapTexture::ActiveBindTexture()
	{
		ES2::BindTexture(GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);
		ES2::ActiveTexture(m_nTextureIndex);
		ES2::Uniform1i(m_nTextureUniform, m_nTextureIndex);
	}

	void GLES_CubeMapTexture::SetTextureUniformIndex(int i, GLuint ProgramHandle)
	{
		m_nTextureUniform = ES2::GetUniformLocation(ProgramHandle, m_strTextureUniformName.c_str());
		ES2::Uniform1i(m_nTextureUniform, i);
		m_nTextureIndex = i;
	}

	void GLES_CubeMapTexture::InvalidTexture()
	{
		ES2::BindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void GLES_CubeMapTexture::createCubeMap(TextureData *up, TextureData *down, TextureData *left, TextureData *right, TextureData *front, TextureData *back)
	{
		ES2::GenTextures(1, &m_nTextureBuffer);
		{
			// Allocate and bind an OpenGL texture
			ES2::Enable(GL_TEXTURE_CUBE_MAP);
			//ES2::ActiveTexture(textureEnum);
			ES2::BindTexture(GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);
			changeRgbModule(up); changeRgbModule(down); changeRgbModule(left);
			changeRgbModule(right); changeRgbModule(front); changeRgbModule(back);
			ES2::TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, right->rgbModule, right->width, right->height, 0, right->rgbModule, GL_UNSIGNED_BYTE, right->imgData);
			ES2::TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, left->rgbModule, left->width, left->height, 0, left->rgbModule, GL_UNSIGNED_BYTE, left->imgData);
			ES2::TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, up->rgbModule,  up->width, up->height, 0, up->rgbModule, GL_UNSIGNED_BYTE, up->imgData);
			ES2::TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, down->rgbModule, down->width, down->height, 0, down->rgbModule, GL_UNSIGNED_BYTE, down->imgData);
			ES2::TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, back->rgbModule, back->width, back->height, 0, back->rgbModule, GL_UNSIGNED_BYTE, back->imgData);
			ES2::TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, front->rgbModule, front->width, front->height, 0, front->rgbModule, GL_UNSIGNED_BYTE, front->imgData);
			ES2::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			ES2::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			ES2::BindTexture(GL_TEXTURE_CUBE_MAP, 0);
			ES2::GenerateMipmap(GL_LINEAR_MIPMAP_LINEAR);//GL_LINEAR_MIPMAP_LINEAR
		}
	}


	void GLES_CubeMapTexture::changeRgbModule(TextureData *data)
	{
		DWORD  rgbModule = 0;
		if (data->rgbModule == PixelFormat::R8G8B8)
		{
			rgbModule = GL_RGB;
		}
		else if (data->rgbModule == PixelFormat::R8G8B8A8)
		{
			rgbModule = GL_RGBA;
		}
		else
		{
			// TODO
		}
		data->rgbModule = rgbModule;
	}

}
