//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
#ifndef E3Drectangle_hpp
#define E3Drectangle_hpp

#include <stdio.h>
#include "E3DRenderObject.hpp"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Rectangle : public GameObject
	{
	public:
		void CreateShape(float width, float height);
		virtual void SetActive(bool isActive) override;
	};
}

#endif /* E3Drectangle_hpp */
