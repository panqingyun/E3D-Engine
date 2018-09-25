#ifndef __E3D_MATERIAL_MANAGER_HPP__
#define __E3D_MATERIAL_MANAGER_HPP__

#include "E3DMaterial.hpp"

namespace E3DEngine
{
	class EX_PORT MaterialManager : public IManager
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
