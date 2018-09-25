
#ifndef FILE_PATH_INCLUDED
#define FILE_PATH_INCLUDED

#include "../Utils/E3DUtil.hpp"

namespace E3DEngine
{

    /** Get the full path of a file in the filesystem.
     * @param filename the name of the file
     * @return the path to the given file
     */
    std::string getPath(const char8 *filename);
	std::string getPath(const std::string& filename);
    
    /** Reads every byte from the file specified by a given path.
     * @param filepath the path obtained from getPath, check getPath
     * @return the files content, u should delete the path from outside
     */
	std::string getContentFromPath(const char8 *filepath);
	std::string getContentFromPath(const std::string& filepath);
	unsigned char * getContent(const char* filepath);
	std::string GetFolder(std::string fullPath);
	std::string GetFileName(std::string fullPath);
}

#endif
