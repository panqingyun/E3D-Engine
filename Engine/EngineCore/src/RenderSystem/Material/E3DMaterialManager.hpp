#ifndef __E3D_MATERIAL_MANAGER_HPP__
#define __E3D_MATERIAL_MANAGER_HPP__

#include "E3DMaterial.hpp"

namespace E3DEngine
{
	class E3D_EXPORT_DLL MaterialManager : public IManager
	{
	public:
		MaterialManager();
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
		Material * CreateMaterial(std::string path, int id);

		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Cleanup();

	protected:
		virtual Material * createMatrerial();

	protected:
		std::map<int, Material*>		 m_mapIDMaterials;
		std::map<std::string, DWORD>	 m_BlendFactorMap;
	};
}

#endif /* E3DMaterialManager_hpp */
