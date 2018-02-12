//
//  E3DMaterialManager.hpp
//	材质管理器，使用相同的贴图和Shader的物体使用同一个材质，以方便合并渲染批次
//  Created by 潘庆云 on 2017/7/17.
//

#ifndef E3DMaterialManager_hpp
#define E3DMaterialManager_hpp

#include "E3DMaterial.hpp"

namespace E3DEngine
{
	class MaterialManager
	{
	public:
		MaterialManager() 
		{
			
		}
		virtual ~MaterialManager()= default;
		
	public:

		// -----------------------------------------------
		// 获取材质
		// @param 材质ID
		//-----------------------------------------------
		virtual Material * GetMaterial(int id);
		// -----------------------------------------------
		// 创建材质
		// @param 材质配置的路径
		//-----------------------------------------------
		virtual Material * CreateMaterial(std::string path, int id);

		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Cleanup();

	protected:
		std::map<int, Material*>		 m_mapIDMaterials;
	};
}

#endif /* E3DMaterialManager_hpp */
