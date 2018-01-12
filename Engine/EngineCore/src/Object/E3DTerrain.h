#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "E3DGameObject.h"

namespace E3DEngine
{
	// TODO  根据高度图生成地形
	class Terrain : public GameObject
	{
	public:
		Terrain()
		{
			CreateBehaviour();
		}
		void Create(const char * heightMapFileName);
		virtual void SetMaterial(Material * material);

	protected:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue() override;
	};
}

#endif
