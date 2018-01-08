#include "UIWidget.h"

namespace E3DEngine
{
	namespace UI
	{
		Widget::Widget(float width, float height)
		{
			m_fWidth = width;
			m_fHeight = height;
		}

		void Widget::setWidth(float width)
		{
			m_fWidth = width;
		}

		void Widget::setHeight(float height)
		{
			m_fHeight = height;
		}

		void Widget::setPosition(float x, float y)
		{
			m_vecPosition.x = x;
			m_vecPosition.y = y;
		}

	}
}

