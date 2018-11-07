#ifndef __E3D_MATERIAL_MANAGER_HPP__
#define __E3D_MATERIAL_MANAGER_HPP__

#include "E3DMaterial.hpp"

namespace E3DEngine
{
	enum BlendFactor
	{
		ZERO = 0, 
		ONE = 1, 
		SRC_COLOR = 2, 
		ONE_MINUS_SRC_COLOR = 3, 
		SRC_ALPHA = 4, 
		ONE_MINUS_SRC_ALPHA = 5,
		DST_ALPHA = 6, 
		ONE_MINUS_DST_ALPHA = 7,
		DST_COLOR = 8, 
		ONE_MINUS_DST_COLOR = 9,
	};

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
		Material * CreateMaterial(MaterialConfig *config);
		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Cleanup();

	protected:
		virtual Material * createMatrerial();

	protected:
		std::map<int, Material*>		 m_mapIDMaterials;
		std::map<std::string, std::map<int, Material*>> m_mapConfigMaterial;
		std::map<int, DWORD>			 m_BlendFactorMap;
	};
}

#endif /* E3DMaterialManager_hpp */
