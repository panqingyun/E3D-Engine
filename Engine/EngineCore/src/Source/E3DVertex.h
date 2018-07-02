#pragma once
#include "Interface.h"
#pragma pack(1) 
#define MaxBoneNumber 106.0f

enum VertexType
{
	STATIC_VERTEX = 0,
	DYNAMIC_VERTEX
};

struct Vertex
{
	Vertex()
	{
		BoneIndex[0] = MaxBoneNumber;
		BoneIndex[1] = MaxBoneNumber;
		BoneIndex[2] = MaxBoneNumber;
		BoneIndex[3] = MaxBoneNumber;

		memset(UV1, 0, sizeof(float) * 2);
		memset(UV2, 0, sizeof(float) * 2);
		memset(UV3, 0, sizeof(float) * 2);
		memset(UV4, 0, sizeof(float) * 2);
		memset(UV5, 0, sizeof(float) * 2);
		memset(UV6, 0, sizeof(float) * 2);
		memset(UV7, 0, sizeof(float) * 2);
		memset(Color, 0, sizeof(float) * 4);
		memset(BoneWeight, 0, sizeof(float) * 4);
		memset(Position, 0, sizeof(float) * 3);
		memset(Normals, 0, sizeof(float) * 3);
		memset(Tangent, 0, sizeof(float) * 3);

	}
	void SetPosition(float x, float y, float z)
	{
		Position[0] = x;
		Position[1] = y;
		Position[2] = z;
	}
	void SettextureCoord1(float u, float v)
	{
		UV1[0] = u;
		UV1[1] = v;
	}
	void SettextureCoord2(float u, float v)
	{
		UV2[0] = u;
		UV2[1] = v;
	}
	void SettextureCoord3(float u, float v)
	{
		UV3[0] = u;
		UV3[1] = v;
	}
	void SettextureCoord4(float u, float v)
	{
		UV4[0] = u;
		UV4[1] = v;
	}
	void SettextureCoord5(float u, float v)
	{
		UV5[0] = u;
		UV5[1] = v;
	}
	void SettextureCoord6(float u, float v)
	{
		UV6[0] = u;
		UV6[1] = v;
	}
	void SettextureCoord7(float u, float v)
	{
		UV7[0] = u;
		UV7[1] = v;
	}
	void SettextureCoord8(float u, float v)
	{
		UV8[0] = u;
		UV8[1] = v;
	}
	void SetNormal(float x, float y, float z)
	{
		Normals[0] = x;
		Normals[1] = y;
		Normals[2] = z;
	}
	void SetColor(float r, float g, float b, float a)
	{
		Color[0] = r;
		Color[1] = g;
		Color[2] = b;
		Color[3] = a;
	}
	void SetTangent(float x, float y, float z)
	{
		Tangent[0] = x;
		Tangent[1] = y;
		Tangent[2] = z;
	}
	void SetBoneIndexWeight(int index, float weight)
	{
		for (int i = 0; i < (int)MaxBoneNumber; i++)
		{
			if (BoneIndex[i] == MaxBoneNumber)
			{
				BoneIndex[i] = index;
				BoneWeight[i] = weight;
				break;
			}
		}
	}

	float Position[3];
	float Normals[3];
	float Color[4];
	float UV1[2];
	float UV2[2];
	float UV3[2];
	float UV4[2];
	float UV5[2];
	float UV6[2];
	float UV7[2];
	float UV8[2];
	float Tangent[3];
	float BoneIndex[4];
	float BoneWeight[4];
};

struct BatchVertex 
{
	float TranformPosition[3];
	float TransformScale[3];
	float TransformRotate[3];
	float Color[4];

	BatchVertex()
	{
		memset(TranformPosition, 0, sizeof(float) * 3);
		memset(TransformScale, 0, sizeof(float) * 3);
		memset(TransformRotate, 0, sizeof(float) * 3);
		memset(Color, 0, sizeof(float) * 3);
	}

	void SetTransformPosition(float x, float y, float z)
	{
		TranformPosition[0] = x;
		TranformPosition[1] = y;
		TranformPosition[2] = z;
	}

	void SetTransformScale(float x, float y, float z)
	{
		TransformScale[0] = x;
		TransformScale[1] = y;
		TransformScale[2] = z;
	}

	void SetTransformRotate(float x, float y, float z)
	{
		TransformRotate[0] = x;
		TransformRotate[1] = y;
		TransformRotate[2] = z;
	}

	void SetColor(float r, float g, float b, float a)
	{
		Color[0] = r;
		Color[1] = g;
		Color[2] = b;
		Color[3] = a;
	}

};
#pragma pack() 