//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "E3DComponent.hpp"
#include "..\Source\ClassFactory.h"

namespace E3DEngine
{
	// TODO  根据高度图生成地形
	class E3D_EXPORT_DLL Terrain : public Component
	{
		DECLARE_CLASS(Terrain)
	public:
		Terrain();
		virtual void Awake() override;
	private:
		void createHeightMap();
		void createGrid();

	public:
		DECLARE_PROPERTY(Terrain, int, Size)
		DECLARE_PROPERTY(Terrain, bool, IsEditorGrid)
		DECLARE_PROPERTY(Terrain, std::string, HeightMapFile)
		virtual void registProperty() override
		{
			SAVE_PROPERTY(Size, FT_INT);
			SAVE_PROPERTY(IsEditorGrid, FT_BOOLEAN);
			SAVE_PROPERTY(HeightMapFile, FT_STRING);
		}
	};
}

#endif
