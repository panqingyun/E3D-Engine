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
		virtual void Create(std::string fileName);
		virtual void SetTextureEnum(uint enumNumber);
		virtual void ActiveBindTexture();
		virtual void InvalidTexture();
		virtual void SetClampType(int tp) { }
		virtual void SetFilterType(int tp) { }
		virtual uint GetTextureEnum() { return m_nTextureEnum; }
		virtual void CreateBehaviour() override;

		uint GetTextureBuffer() { return m_nTextureBuffer; }

	public:
		virtual void SetTextureUniformName(std::string name);
		virtual void SetTextureUniformIndex(int index, UINT program) { }
		virtual std::string GetUniformName();

	protected:
		uint			m_nTextureEnum;
		unsigned int	m_nTextureBuffer;
		int				m_nTextureClampType;
		int				m_nTextureFilterType;
		std::string		m_strTextureUniformName;
	};
}

#endif /* Texture_hpp */
