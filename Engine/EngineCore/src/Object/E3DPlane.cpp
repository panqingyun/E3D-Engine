
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//

#include "E3DPlane.h"

E3DEngine::Plane::Plane()
{
	m_EachGridWidth = 1;
	m_EachGridHeight = 1;
}

E3DEngine::Plane::~Plane()
{

}

void E3DEngine::Plane::Create(int width, int height)
{
	float xStartPos = -width / 2.0f;
	float zStartPos = -height / 2.0f;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			
		}
	}
}
