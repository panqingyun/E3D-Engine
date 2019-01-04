//
//  Texture.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef GL_Texture_HPP
#define GL_Texture_HPP

#include "E3DGLTextureDataManager.hpp"
#include <src/RenderSystem/Texture/E3DTexture2D.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class TextureFrameEffect;
	class GL_Texture2D : public Texture2D
	{
		friend class Material;
	public:
		GL_Texture2D();
		virtual ~GL_Texture2D();
		virtual GLuint &GetTextureBuffer();

	public:
		virtual void Create(Texture2dData *tData) override;
		virtual void SetTextureData(Texture2dData *tData)override;

	private:
		void setTextureParam(Texture2dData *tData);

	protected:
		GLuint			m_nTextureUniform;

	};
}

#endif /* Texture_hpp */
