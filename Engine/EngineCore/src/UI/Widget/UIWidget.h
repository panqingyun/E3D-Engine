#ifndef __UI_WIDGET_H__
#define __UI_WIDGET_H__

#include "../../Source/Interface.h"
#include "../../Source/E3DDelegate.h"
#include "../../Object/E3DRectangle.hpp"

namespace E3DEngine
{
	namespace UI
	{
		class Widget : public Ref, public IActor
		{
		public:
			Widget(float width, float height);

		public:
			event EventDelegates Click;
			event EventDelegates Touch;
			event EventDelegates Drag;

		public:
			virtual void setWidth(float width);
			virtual void setHeight(float height);
			virtual void setPosition(float x, float y);

		private: 
			float m_fWidth;
			float m_fHeight;
			vec3f m_vecPosition;
		};
	}
}

#endif
