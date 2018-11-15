//********************************** Effect 3D Engine **************************************************//
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
		DECLARE_METHOD(Terrain, int, Size)
		DECLARE_METHOD(Terrain, bool, IsEditorGrid)
		DECLARE_METHOD(Terrain, std::string, HeightMapFile)
		virtual void registProperty() override
		{
			SAVE_METHOD(Size, FT_INT);
			SAVE_METHOD(IsEditorGrid, FT_BOOLEAN);
			SAVE_METHOD(HeightMapFile, FT_STRING);
		}
	};
}

#endif
