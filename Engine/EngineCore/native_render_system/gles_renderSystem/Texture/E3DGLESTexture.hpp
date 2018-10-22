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
		virtual void Create(std::string fileName, TextureData &tData);
		virtual void SetTextureUniformIndex(int i, GLuint ProgramHandle);
		virtual void SetTextureData(TextureData &tData)override;
		virtual void Create(TextureData &tData)override;
		virtual void ActiveBindTexture()override;
		virtual void InvalidTexture()override;
		virtual void SetClampType(int tp) override;
		virtual void SetFilterType(int tp) override;

	private:
		void setTextureParam(TextureData &tData);

	protected:
		GLuint			m_nTextureUniform;
		GLuint			m_nTextureIndex;

	};
}

#endif /* Texture_hpp */
