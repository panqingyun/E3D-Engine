//
//  TextureDataManager.hpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#ifndef TextureDataManager_hpp
#define TextureDataManager_hpp

#include "src/Source/Interface.h"
#include <FreeImage.h>

namespace E3DEngine
{
	struct stImageData
	{
		void *	data;
		int		width;
		int		height;
		~stImageData()
		{
			//free(data);
		}
	};
	class TextureDataManager : public IObject
	{
	public:
		// -----------------------------------------------
		// 
		//-----------------------------------------------
		virtual void Init();

		// -----------------------------------------------
		// 创建纹理缓冲区
		// @return 纹理缓冲区ID
		// @param 图片名字
		//-----------------------------------------------
		virtual unsigned int CreateTextureBuffer(std::string imageName);

		// -----------------------------------------------
		// 创建图像数据
		// @return 图像内部数据RGB
		// @param 图片名字
		//-----------------------------------------------
		virtual stImageData * CreateTextureData(std::string imageName);

		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Cleanup();
		std::string DEFAULT_TEXTURE_FILE;

	protected:
		std::map<std::string, unsigned int> m_mapTextureBuffer;
		std::map<std::string, stImageData*> m_mapTextureData;
	};
}

#endif /* TextureDataManager_hpp */
