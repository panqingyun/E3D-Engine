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

	enum TextureType
	{
		eTEXTURE_2D,
		eRENDER_TEXTURE,
		eCUBMAP_TEXTURE,
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

	enum PixelFormat
	{
		Unknow,
		L8,			// 1 byte pixel format, 1 byte luminance
		L8A8,		// 2 byte pixel format, 1 byte luminance, 1 byte alpha
		R8G8B8,		// 24-bit pixel format, 8 bits for red, green and blue.
		R8G8B8A8	// 32-bit pixel format, 8 bits for red, green, blue and alpha.
	};

	typedef enum
	{
		RENDER_BUFFER,
		RENDER_TO_TEXTURE,
		RENDER_DEPTH,
	} RenderTargeType;

	enum MultiSample
	{
		MULTISAMPLE_NONE = 0,
		MULTISAMPLE_X1 = 1,
		MULTISAMPLE_X2 = 2,
		MULTISAMPLE_X3 = 3,
		MULTISAMPLE_X4 = 4
	};

	struct E3D_EXPORT_DLL TextureData
	{
		std::string fileName;
		std::string uniformName;

		unsigned int rgbModule;
		int		width;
		int		height;
		int		configID;

		TextureData()
		{
			width = 0;
			height = 0;
			rgbModule = 0;
			configID = 0;
		}

	};

	struct Texture2dData : public TextureData
	{
		CLAMP_TYPE clampType;
		FILTER_TYPE filterType;
		void *	imgData;
		bool	useMipMap;
		Texture2dData()
		{
			clampType = CLAMP_TYPE::CLAMP_TO_EDGE;
			filterType = FILTER_TYPE::LINEAR;
			imgData = nullptr;
			useMipMap = false;
		}

		~Texture2dData()
		{
			if (imgData != nullptr)
			{
				free(imgData);
			}
		}
	};

	struct RenderTextureData : public TextureData
	{
		int		target;
		int		multiSampleLevel;
		RenderTextureData()
		{
			multiSampleLevel = 0;
			target = 0;
		}
	};

	class Render2Texture;
	class Texture;
	class E3D_EXPORT_DLL TextureDataManager : public IManager
	{
	public:
		// -----------------------------------------------
		// 创建RTT
		//-----------------------------------------------
		Render2Texture* CreateRender2Texture(TextureData *data);

		Render2Texture* CreateRender2TextureSingleThread(TextureData *data);

		// -----------------------------------------------
		// 创建图像数据
		// @return 图像内部数据RGB
		// @param 图片名字
		//-----------------------------------------------
		virtual Texture2dData * GetTextureDataFromFile(std::string imageName, Texture2dData * InData = nullptr);

		Texture *GetTexture(TextureType type, TextureData* tData);

		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Cleanup();

	protected:
		virtual Render2Texture* createRender2Texture()							= 0;
		virtual Texture *createTexture2D(Texture2dData *data)					= 0;
		virtual Texture *createCubeTexture(std::string filePath, int selectID)	= 0;
	protected:
		std::map<std::string, Texture*> m_mapTextures;
	};
}

#endif /* TextureDataManager_hpp */
