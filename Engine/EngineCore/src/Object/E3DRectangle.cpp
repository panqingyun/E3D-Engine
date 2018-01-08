//
//  E3Drectangle.cpp
//
//  Created by 潘庆云 on 2017/7/6.
//

#include "E3DRectangle.hpp"

namespace E3DEngine
{
	void Rectangle::CreateShape(float width, float height, bool up2down/* = false*/)
	{
		m_ZWriteEnable = false;
		/*m_BlendType = eBlendType_default;
		Vertices.resize(4);
		Vertices[0].SetPosition(-width/2, height/2, 0);
		Vertices[0].SetNormal(0, 0 , 1);
		Vertices[1].SetPosition(-width/2, -height/2, 0);
		Vertices[1].SetNormal(0, 0, 1);
		Vertices[2].SetPosition(width/2, -height/2, 0);
		Vertices[2].SetNormal(0, 0 , 1);
		Vertices[3].SetPosition(width/2, height/2, 0);
		Vertices[3].SetNormal(0, 0, 1);
		if (up2down)
		{
			Vertices[0].SettextureCoord(0, 1);
			Vertices[1].SettextureCoord(0, 0);
			Vertices[2].SettextureCoord(1, 0);
			Vertices[3].SettextureCoord(1, 1);
		}
		else
		{
			Vertices[0].SettextureCoord(0, 0);
			Vertices[1].SettextureCoord(0, 1);
			Vertices[2].SettextureCoord(1, 1);
			Vertices[3].SettextureCoord(1, 0);
		}

		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;
		Indices[3] = 2;
		Indices[4] = 3;
		Indices[5] = 0;*/
		
		/*setDrawModule(GL_TRIANGLES);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* Indices.size(), Indices.data(), GL_STATIC_DRAW);*/
	}
	
	/*void Rectangle::prepareRender(float deltaTime)
	{*/
		/*if (pMaterial == nullptr)
		{
			return;
		}
		pMaterial->UseProgram();
		m_nIndexSize = (DWORD)Indices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		if (m_ZWriteEnable)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
		}
		glEnable(GL_ALPHA);
		glEnable(GL_BLEND);
		if (m_BlendType == eBlendType_ONE_MINUS_SRC)
		{
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}
		else if (m_BlendType == eBlendType_default)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else if (m_BlendType == eBlendType_NONE)
		{
			glBlendFunc(GL_ONE, GL_ZERO);
		}*/
	/*}*/

	void Rectangle::SetBlendType(DWORD type)
	{
		m_BlendType = type;
	}

	void Rectangle::SetZWriteEnable(bool bEnable)
	{
		m_ZWriteEnable = bEnable;
	}

}
