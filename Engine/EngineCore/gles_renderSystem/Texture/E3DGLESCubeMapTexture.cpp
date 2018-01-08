//
//  E3DCubeMapTexture.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DGLESCubeMapTexture.hpp"

namespace E3DEngine
{	
	void GLES_CubeMapTexture::CreateCubeMapTexture(int textureEnum,
											  std::string xPName,
											  std::string xNName,
											  std::string yPName,
											  std::string yNName,
											  std::string zPName,
											  std::string zNName)
	{
		void * xpData = createImageData(xPName, &m_nImageWidth, &m_nImageHeight);
		void * xnData = createImageData(xNName, &m_nImageWidth, &m_nImageHeight);
		void * ypData = createImageData(yPName, &m_nImageWidth, &m_nImageHeight);
		void * ynData = createImageData(yNName, &m_nImageWidth, &m_nImageHeight);
		void * zpData = createImageData(zPName, &m_nImageWidth, &m_nImageHeight);
		void * znData = createImageData(zNName, &m_nImageWidth, &m_nImageHeight);
		m_nTextureEnum = textureEnum;
		glGenTextures(1, &m_nTextureBuffer);
		{
			// Allocate and bind an OpenGL texture
			glEnable(GL_TEXTURE_CUBE_MAP);
			//glActiveTexture(textureEnum);
			glBindTexture (GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);

			// Load the cube face - Positive X
			glTexImage2D ( GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						  0,
						  GL_RGBA,
						  m_nImageWidth,
						  m_nImageHeight,
						  0,
						  GL_RGBA,
						  GL_UNSIGNED_BYTE,
						  xpData );
					
			// Load the cube face - Negative X
			glTexImage2D ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						  0,
						  GL_RGBA,
						  m_nImageWidth,
						  m_nImageHeight,
						  0,
						  GL_RGBA,
						  GL_UNSIGNED_BYTE,
						  xnData );
					
			// Load the cube face - Positive Y
			glTexImage2D ( GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						  0,
						  GL_RGBA,
						  m_nImageWidth,
						  m_nImageHeight,
						  0,
					      GL_RGBA,
						  GL_UNSIGNED_BYTE,
						  ypData );
				
			// Load the cube face - Negative Y
			glTexImage2D ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						  0,
						  GL_RGBA,
						  m_nImageWidth,
						  m_nImageHeight,
						  0,
					      GL_RGBA,
						  GL_UNSIGNED_BYTE,
						  ynData );
				
			// Load the cube face - Positive Z
			glTexImage2D ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						  0,
						  GL_RGBA,
						  m_nImageWidth,
						  m_nImageHeight,
						  0,
					 
						  GL_RGBA,
						  GL_UNSIGNED_BYTE,
						  zpData );
				
			// Load the cube face - Negative Z
			glTexImage2D ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
						  0,
						  GL_RGBA,
						  m_nImageWidth,
						  m_nImageHeight,
						  0,
					 
						  GL_RGBA,
						  GL_UNSIGNED_BYTE,
						  znData );
				
			// Set the filtering mode
			glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glBindTexture (GL_TEXTURE_CUBE_MAP, 0);
			glGenerateMipmap(GL_LINEAR_MIPMAP_LINEAR);//GL_LINEAR_MIPMAP_LINEAR
		}
	}
	
	void GLES_CubeMapTexture::ActiveBindTexture()
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);
		glUniform1i(m_nTextureUniform, 3);

	}
}
