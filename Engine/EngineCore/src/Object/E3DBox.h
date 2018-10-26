
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-11-28 PanQingyun. All rights reserved. ************************//

#pragma once

#include "E3DGameObject.h"
#include "../Source/E3DVertex.h"

namespace E3DEngine
{
	class Renderer;
	class E3D_EXPORT_DLL Box : public GameObject
	{
	public:
		Box();
		virtual void Create(float l, float w, float h);
	protected:
		void fillVertex(float l, float h, float w);

	};
}