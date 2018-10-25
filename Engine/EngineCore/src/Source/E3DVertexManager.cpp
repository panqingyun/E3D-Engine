#include "E3DVertexManager.h"

std::vector<Vertex> defaultVert;
std::vector<unsigned int> defaultIndex;

std::vector<Vertex> & VertexManager::GetVertex(std::string name)
{
	VertexManager &_ins = instance();
	if (_ins.mMapVertex.find(name) != _ins.mMapVertex.end())
	{
		return _ins.mMapVertex[name];
	}
	return defaultVert;
}

std::vector<unsigned int> & VertexManager::GetIndex(std::string name)
{
	VertexManager &_ins = instance();
	if (_ins.mMapIndex.find(name) != _ins.mMapIndex.end())
	{
		return _ins.mMapIndex[name];
	}
	return defaultIndex;
}

void VertexManager::Add(std::vector<Vertex> vertex, std::vector<unsigned int> index, std::string name)
{
	VertexManager &_ins = instance();
	if (_ins.mMapIndex.find(name) == _ins.mMapIndex.end())
	{
		_ins.mMapIndex.insert(std::pair<std::string, std::vector<unsigned int>>(name, index));
	}
	if (_ins.mMapVertex.find(name) == _ins.mMapVertex.end())
	{
		_ins.mMapVertex.insert(std::pair<std::string, std::vector<Vertex>>(name, vertex));
	}
}

