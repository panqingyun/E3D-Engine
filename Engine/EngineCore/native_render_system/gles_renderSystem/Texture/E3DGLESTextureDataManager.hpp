//
//  TextureDataManager.hpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#ifndef GLES_TextureDataManager_HPP
#define GLES_TextureDataManager_HPP

#include <src/RenderSystem/Texture/E3DTextureDataManager.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class GLES_TextureDataManager : public TextureDataManager
	{
	public:
		virtual void Init() override;
		virtual unsigned int GetTextureBuffer(std::string imageName) override;

		virtual TextureData * GetTextureDataFromFile(std::string imageName) override;
		virtual void Cleanup() override;
	};
}

#endif /* TextureDataManager_hpp */
