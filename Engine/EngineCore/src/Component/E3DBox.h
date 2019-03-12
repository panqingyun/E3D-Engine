
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-11-28 PanQingyun. All rights reserved. ************************//

#pragma once

#include "E3DComponent.hpp"
#include "../Source/E3DVertex.h"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	class BatchRenderer;
	class E3D_EXPORT_DLL Box : public Component
	{
		DECLARE_CLASS(Box)
	public:
		Box();
		virtual void Awake() override;
	protected:
		void fillVertex();

	};
}