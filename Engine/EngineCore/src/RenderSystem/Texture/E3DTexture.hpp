//
//  Texture.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef __E3D_TEXTURE_HPP__
#define __E3D_TEXTURE_HPP__

#include "src/Object/E3DGameObject.h"
#include "src/Effect/E3DEffectFactory.hpp"
#include "E3DTextureDataManager.hpp"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Texture : public Object
	{
		friend class Material;
	public:
        Texture();
		virtual ~Texture();

	public:
		uint GetTextureBuffer();

	protected:
		unsigned int	m_nTextureBuffer;
	};
}

#endif /* Texture_hpp */
