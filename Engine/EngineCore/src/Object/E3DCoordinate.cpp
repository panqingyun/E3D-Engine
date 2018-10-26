#include "E3DCoordinate.h"
#include "../RenderSystem/RenderObject/E3DRender.hpp"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "E3DTransform.hpp"
#include "E3DGameObject.h"
#include "../Camera/E3DCamera.h"
#include "../Source/E3DDebug.h"
#include "../Source/E3DVertexManager.h"

namespace E3DEngine
{
	Coordinate::Coordinate()
	{
		VertexBufferName = "Coordinate";
		if (VertexManager::GetVertex(VertexBufferName).empty())
		{
			std::vector<Vertex> vecVertex;
			vecVertex.resize(6);
			// x r
			vecVertex[0].SetPosition(0, 0, 0);
			vecVertex[0].SetColor(1, 0, 0, 1);
			vecVertex[1].SetPosition(10, 0, 0);
			vecVertex[1].SetColor(1, 0, 0, 1);
			// y g
			vecVertex[2].SetPosition(0, 0, 0);
			vecVertex[2].SetColor(0, 1, 0, 1);
			vecVertex[3].SetPosition(0, 10, 0);
			vecVertex[3].SetColor(0, 1, 0, 1);
			// z b
			vecVertex[4].SetPosition(0, 0, 0);
			vecVertex[4].SetColor(0, 0, 1, 1);
			vecVertex[5].SetPosition(0, 0, 10);
			vecVertex[5].SetColor(0, 0, 1, 1);

			std::vector<UINT> vecIndex;
			vecIndex.resize(9);
			UINT index[9] =
			{
				0, 1, 0,
				2, 2, 3,
				4, 5, 4
			};

			memcpy(vecIndex.data(), index, sizeof(UINT) * 9);

			VertexManager::Add(vecVertex, vecIndex, VertexBufferName);
		}
		mSceneObjectType = TP_Line;
		CreateBehaviour();
	}

	void Coordinate::TransferRender()
	{
		m_pRenderer->SetDrawModule(eDM_LINES);
	}
}