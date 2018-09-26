//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "E3DGameObject.h"

namespace E3DEngine
{
	// TODO  根据高度图生成地形
	class E3D_EXPORT_DLL Terrain : public GameObject
	{
	public:
		Terrain();
		void Create(const char * heightMapFileName);
		void Create(int size);
		virtual void SetMaterial(Material * material);
		virtual void PrepareUpdate(float deltaTime);
		void SetIsEditorGrid(bool isEditor);

	protected:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;

	private:
		bool m_bIsEditorGrid;
		int lastSize;
	};
}

#endif
