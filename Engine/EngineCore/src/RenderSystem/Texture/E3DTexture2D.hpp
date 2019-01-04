//
//  Texture.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef __E3D_TEXTURE_2D_HPP__
#define __E3D_TEXTURE_2D_HPP__

#include "E3DTexture.hpp"

namespace E3DEngine
{
	class TextureFrameEffect;
	class E3D_EXPORT_DLL Texture2D : public Texture
	{
		friend class Material;
	public:
		Texture2D();
		virtual ~Texture2D();

	public:
		TextureFrameEffect * TextureEffect;
		
	public:
		virtual void SetTextureData(Texture2dData *tData);
		virtual void Create(Texture2dData *tData);
		virtual void CreateBehaviour() override;
		Texture2dData *GetTextureData();
		void SetIsReadWrite(bool bReadWrite);

	protected:
		Texture2dData	*m_pTextureData;
		bool			m_bIsReadWrite;
	};
}

#endif /* Texture_hpp */
