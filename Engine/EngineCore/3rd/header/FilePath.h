/* FilePath.h
 *
 * Virtual Vision Engine . Copyright (C) 2012 Abdallah DIB.
 * All rights reserved. Email: Abdallah.dib@virtual-vison.net
 * Web: <http://www.virutal-vision.net/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef FILE_PATH_INCLUDED
#define FILE_PATH_INCLUDED

#include "types.h"
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include "vvision.h"

namespace vvision
{
#define PNG_READ_SUCCESS 0
#define PNG_ERROR_NO_FILE 1
#define PNG_ERROR_NOT_PNG 2
#define PNG_ERROR_CREATE_PNG_STRUCT 3
#define PNG_ERROR_CREATE_INFO_STRUCT 4
#define PNG_ERROR_JMP 5
#define PNG_READ_HEADER 4

    /** Get the full path of a file in the filesystem.
     * @param filename the name of the file
     * @return the path to the given file
     */
    string getPath(const char8 *filename);
    string getPath(const string& filename);
    
    /** Reads every byte from the file specified by a given path.
     * @param filepath the path obtained from getPath, check getPath
     * @return the files content, u should delete the path from outside
     */
    string getContentFromPath(const char8 *filepath);
	string getContentFromPath(const string& filepath);
	unsigned char * getContent(const char* filepath);
    
    /**
     * load a png/jpg image
     * @param filename the image file name, this function calls getPath implicitly ..
     * @param widht/height the image width and height
     * @return the data pointer to the image. dont forget to free memory by calling free.
     */
   /* char8* LoadImage(const char8* filename, int32 *width, int32 *height, int &bpp);
    char8* LoadImage(const string& filename, int32 *width, int32 *height, int &bpp);*/
	
	std::string GetFolder(std::string fullPath);

	/**
	 * Get the main bundle path
	 */
	string getMainBundlePath();
#ifndef __IOS__
	/*char8* LoadImageW(const string& filename, int32 *width, int32 *height, int &bpp);
	int png_read(const char* filename, png_datap data);*/
#endif
}

#endif
