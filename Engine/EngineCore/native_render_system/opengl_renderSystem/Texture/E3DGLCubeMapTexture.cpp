//
//  E3DCubeMapTexture.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DGLCubeMapTexture.hpp"
#include <src/Source/E3DDebug.h>

namespace E3DEngine
{		
	void GL_CubeMapTexture::ActiveBindTexture()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);
		glActiveTexture(m_nTextureIndex);
		glUniform1i(m_nTextureUniform, m_nTextureIndex);
	}

	void GL_CubeMapTexture::SetTextureUniformIndex(int i, GLuint ProgramHandle)
	{
		m_nTextureUniform = glGetUniformLocation(ProgramHandle, m_strTextureUniformName.c_str());
		glUniform1i(m_nTextureUniform, i);
		m_nTextureIndex = i;
	}

	void GL_CubeMapTexture::InvalidTexture()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void GL_CubeMapTexture::createCubeMap(TextureData *up, TextureData *down, TextureData *left, TextureData *right, TextureData *front, TextureData *back)
	{
		glGenTextures(1, &m_nTextureBuffer);
		{
			// Allocate and bind an OpenGL texture
			glEnable(GL_TEXTURE_CUBE_MAP);
			//glActiveTexture(textureEnum);
			changeRgbModule(up); changeRgbModule(down); changeRgbModule(left);
			changeRgbModule(right); changeRgbModule(front); changeRgbModule(back);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, right->rgbModule, right->width, right->height, 0, right->rgbModule, GL_UNSIGNED_BYTE, right->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, left->rgbModule, left->width, left->height, 0, left->rgbModule, GL_UNSIGNED_BYTE, left->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, up->rgbModule,  up->width, up->height, 0, up->rgbModule, GL_UNSIGNED_BYTE, up->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, down->rgbModule, down->width, down->height, 0, down->rgbModule, GL_UNSIGNED_BYTE, down->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, back->rgbModule, back->width, back->height, 0, back->rgbModule, GL_UNSIGNED_BYTE, back->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, front->rgbModule, front->width, front->height, 0, front->rgbModule, GL_UNSIGNED_BYTE, front->imgData);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			glGenerateMipmap(GL_LINEAR_MIPMAP_LINEAR);//GL_LINEAR_MIPMAP_LINEAR
		}
	}


	void GL_CubeMapTexture::changeRgbModule(TextureData *data)
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
