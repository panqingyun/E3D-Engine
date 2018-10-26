
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//

#include "E3DRectangle.hpp"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Source/E3DVertexManager.h"

namespace E3DEngine
{
	void Rectangle::CreateShape(float width, float height)
	{
		VertexBufferName = "Rectangle";
		if (VertexManager::GetVertex(VertexBufferName).empty())
		{
			std::vector<Vertex> vecVertex;
			vecVertex.resize(4);
			vecVertex[0].SetPosition(-width / 2, height / 2, 0);
			vecVertex[0].SetNormal(0, 0, 1);
			vecVertex[0].SetColor(1, 1, 1, 1);
			vecVertex[0].SettextureCoord1(0, 1);
			vecVertex[1].SetPosition(-width / 2, -height / 2, 0);
			vecVertex[1].SetNormal(0, 0, 1);
			vecVertex[1].SetColor(1, 1, 1, 1);
			vecVertex[1].SettextureCoord1(0, 0);
			vecVertex[2].SetPosition(width / 2, -height / 2, 0);
			vecVertex[2].SetNormal(0, 0, 1);
			vecVertex[2].SetColor(1, 1, 1, 1);
			vecVertex[2].SettextureCoord1(1, 0);
			vecVertex[3].SetPosition(width / 2, height / 2, 0);
			vecVertex[3].SetNormal(0, 0, 1);
			vecVertex[3].SetColor(1, 1, 1, 1);
			vecVertex[3].SettextureCoord1(1, 1);

			std::vector<UINT> vecIndex;
			vecIndex.resize(6);
			vecIndex[0] = 0;
			vecIndex[1] = 1;
			vecIndex[2] = 2;
			vecIndex[3] = 2;
			vecIndex[4] = 3;
			vecIndex[5] = 0;
			VertexManager::Add(vecVertex, vecIndex, VertexBufferName);
		}
		CreateBehaviour();
	}
}
