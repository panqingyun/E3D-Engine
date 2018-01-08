//
//  Texture.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef GLES_Texture_HPP
#define GLES_Texture_HPP

#include "E3DGLESTextureDataManager.hpp"
#include <src/RenderSystem/Texture/E3DTexture.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class TextureFrameEffect;
	class GLES_Texture : public Texture
	{
		friend class Material;
	public:
		GLES_Texture();
		virtual ~GLES_Texture();
		virtual GLuint &GetTextureBuffer();

	public:
		virtual void SetTextureUniformName(std::string name);
		virtual void Create(std::string fileName);
		virtual void SetTextureUniformLocation(int i, GLuint ProgramHandle);
		virtual void SetTextureData(void * textureData, int width, int height)override;
		virtual void Create(void * textureData, int width, int height)override;
		virtual void SetTextureEnum(unsigned int enumNumber);
		virtual void ActiveBindTexture()override;
		virtual void InvalidTexture()override;

	public:
		GLuint			m_nTextureUniform;
		std::string		m_strTextureUniformName;
		GLuint			m_nTextureIndex;

	};
}

#endif /* Texture_hpp */
