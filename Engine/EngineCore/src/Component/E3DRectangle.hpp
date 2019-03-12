//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
#ifndef E3Drectangle_hpp
#define E3Drectangle_hpp

#include <stdio.h>
#include "E3DComponent.hpp"
#include "..\Source\ClassFactory.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Rectangle : public Component
	{
		DECLARE_CLASS(Rectangle)
	public:
		Rectangle();
		virtual void Awake() override;
	private:
		void createShape(float width, float height);
	};
}

#endif /* E3Drectangle_hpp */
