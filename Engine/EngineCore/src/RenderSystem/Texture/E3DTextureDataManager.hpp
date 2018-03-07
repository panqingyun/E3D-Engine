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
		int		rgb_mode;
		~stImageData()
		{
			//free(data);
		}
	};	
	
	enum CLAMP_TYPE
	{
		CLAMP_TO_EDGE = 0,
		REPEAT = 1,
		MIRRORED_REPEAT = 2,
	};

	enum FILTER_TYPE
	{
		LINEAR = 0,
		NEAREST = 1,
	};

	struct TextureData
	{
		CLAMP_TYPE clampType;
		FILTER_TYPE filterType;
		std::string fileName;
		std::string uniformName;
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
		virtual unsigned int CreateTextureBuffer(std::string imageName, TextureData &tData);

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
	};
}

#endif /* TextureDataManager_hpp */
