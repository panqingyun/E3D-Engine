#pragma once
#include "E3DVertex.h"

class E3D_EXPORT_DLL VertexManager
{
public:
	static std::vector<Vertex> &GetVertex(std::string name);
	static std::vector<unsigned int> &GetIndex(std::string name);
	static void Add(std::vector<Vertex> vertex, std::vector<unsigned int> index, std::string name);

private:
	VertexManager() {}
	static VertexManager &instance()
	{
		static VertexManager _ins;
		return _ins;
	}
private:
	std::map<std::string, std::vector<Vertex>> mMapVertex;
	std::map<std::string, std::vector<unsigned int>> mMapIndex;
};