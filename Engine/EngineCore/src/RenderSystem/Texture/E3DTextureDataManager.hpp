//
//  TextureDataManager.hpp
//
//  Created by 潘庆云 on 2017/5/24.
//

#ifndef __E3D_TEXTURE_DATA_MANAGER_HPP__
#define __E3D_TEXTURE_DATA_MANAGER_HPP__

#include "src/Source/Interface.h"

namespace E3DEngine
{	
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
		NEAREST_MIPMAP_NEAREST = 2,
		LINEAR_MIPMAP_NEAREST = 3,
		NEAREST_MIPMAP_LINEAR = 4,
		LINEAR_MIPMAP_LINEAR = 5
	};

	struct TextureData
	{
		CLAMP_TYPE clampType;
		FILTER_TYPE filterType;
		std::string fileName;
		std::string uniformName;

		unsigned int rgbModule;
		void *	imgData;
		int		width;
		int		height;
		bool	useMipMap;

		TextureData()
		{
			clampType = CLAMP_TYPE::CLAMP_TO_EDGE;
			filterType = FILTER_TYPE::LINEAR;
			imgData = nullptr;
			width = 0;
			height = 0;
			rgbModule = 0;
			useMipMap = false;
		}

		~TextureData()
		{
			free(imgData);
		}
	};

	class TextureDataManager : public IManager
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
		virtual unsigned int GetTextureBuffer(std::string imageName);

		// -----------------------------------------------
		// 创建图像数据
		// @return 图像内部数据RGB
		// @param 图片名字
		//-----------------------------------------------
		virtual TextureData * GetTextureDataFromFile(std::string imageName);

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
