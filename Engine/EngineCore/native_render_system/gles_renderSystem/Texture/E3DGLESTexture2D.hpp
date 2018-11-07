//
//  Texture.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef GLES_Texture_HPP
#define GLES_Texture_HPP

#include "E3DGLESTextureDataManager.hpp"
#include <src/RenderSystem/Texture/E3DTexture2D.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class TextureFrameEffect;
	class GLES_Texture2D : public Texture2D
	{
		friend class Material;
	public:
		GLES_Texture2D();
		virtual ~GLES_Texture2D();
		virtual GLuint &GetTextureBuffer();

	public:
		virtual void SetTextureData(TextureData *tData)override;
		virtual void Create(TextureData *tData)override;

	private:
		void setTextureParam(TextureData *tData);

	protected:
		GLuint			m_nTextureUniform;
		GLuint			m_nTextureIndex;

	};
}

#endif /* Texture_hpp */
