//
//  TextureDataManager.hpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#ifndef GL_TextureDataManager_HPP
#define GL_TextureDataManager_HPP

#include <src/RenderSystem/Texture/E3DTextureDataManager.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	class GL_TextureDataManager : public TextureDataManager
	{
	protected:
		virtual Render2Texture* createRender2Texture() override;
		virtual Texture *createTexture2D(Texture2dData *data) override;
		virtual Texture *createCubeTexture(std::string filePath, int selectID) override;
	};
}

#endif /* TextureDataManager_hpp */
