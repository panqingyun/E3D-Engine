#pragma once
#include "E3DGameObject.h"

namespace E3DEngine
{
	class Line : public GameObject
	{
	public:
		Line(vec3f start, vec3f end);
		~Line();

		virtual void TransferRender() override;
	private:

	};

}