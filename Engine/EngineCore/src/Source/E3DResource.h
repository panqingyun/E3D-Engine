#pragma once
#include "EngineDelegate.h"

namespace E3DEngine
{
	struct FileInfo
	{
		std::string FullName;
		std::string Name;
		int Size;
		FileInfo(std::string path, std::string name, int size)
		{
			Name = name;
			FullName.assign(path).append("\\").append(name);
			Size = size;
		}
	};

	class Resource : public IObject
	{
	public:
		static void GetFiles(std::string path, std::vector<FileInfo>& files, std::string extension);
	};
}