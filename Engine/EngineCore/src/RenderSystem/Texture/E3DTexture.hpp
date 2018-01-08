//
//  Texture.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "src/Object/E3DGameObject.h"
#include "src/Effect/E3DEffectFactory.hpp"
#include "E3DTextureDataManager.hpp"

namespace E3DEngine
{
	class TextureFrameEffect;
	class Texture
	{
		friend class Material;
	public:
        Texture();
		virtual ~Texture();

	public:
		TextureFrameEffect * TextureEffect;
		
	public:
		virtual void Create(string fileName);
		virtual void SetTextureData(void * textureData, int width, int height);
		virtual void Create(void * textureData, int width, int height);
		virtual void SetTextureEnum(uint enumNumber);
		virtual void ActiveBindTexture();
		virtual void InvalidTexture();

	protected:
		uint			m_nTextureEnum;
		unsigned int	m_nTextureBuffer;

	};
}

#endif /* Texture_hpp */
