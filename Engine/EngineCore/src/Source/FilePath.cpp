#include "FilePath.h"
#ifdef WIN32
#include <atlimage.h>
#include <wingdi.h>
#endif

#ifdef __IOS__
#include <fstream>
#include <iostream>
#include <CoreFoundation/CoreFoundation.h>
#import <QuartzCore/QuartzCore.h>
#endif
#include "Helpers.h"

namespace E3DEngine
{
	string getMainBundlePath()
	{
		char8 *ptr = NULL;
#ifdef __IOS__
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
		CFStringRef str = CFURLCopyFileSystemPath(resourcesURL,
			kCFURLPOSIXPathStyle);
		CFRelease(resourcesURL);
		ptr = new char8[CFStringGetLength(str) + 1];
		CFStringGetCString(str,
			ptr,
			FILENAME_MAX,
			kCFStringEncodingASCII);
		CFRelease(str);
#endif
#ifdef WIN32
		ptr = "";
#endif
		std::string res(ptr);
#ifdef __IOS__
		delete[] ptr;
#endif
		return res;
	}

	string getPath(const char8 *filename)
	{
		char8 *ptr = NULL;
		std::string fnm(filename);
#ifdef __IOS__
		if (fnm.find("/") == fnm.npos)
		{
			CFBundleRef mainBundle = CFBundleGetMainBundle();
			CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
			CFStringRef str = CFURLCopyFileSystemPath(resourcesURL,
				kCFURLPOSIXPathStyle);
			CFRelease(resourcesURL);
			ptr = new char8[CFStringGetLength(str) + 1];
			CFStringGetCString(str,
				ptr,
				FILENAME_MAX,
				kCFStringEncodingASCII);
			CFRelease(str);

			std::string res(ptr);
			res += std::string("/");
			res += std::string(filename);

			delete[] ptr;
			ptr = new char8[res.length() + 1];
			strcpy(ptr, res.c_str());
		}

		else
		{
			ptr = new char8[fnm.length() + 1];
			strcpy(ptr, fnm.c_str());
		}
#endif
		string s(ptr);
		delete[] ptr;
		return s;
	}

	string getPath(const string& filename)
	{
		return getPath(filename.c_str());
	}

	char * getFileContent(const char * filePath)
	{
		FILE * file = fopen(filePath, "rb");
		long length = 0;
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* buf = new char[length + 1];
		buf[0] = 0;

		fread(buf, length, 1, file);
		return buf;
	}

	string getContentFromPath(const char8 *filepath)
	{
		std::string buf("");
		std::string line("");
		std::ifstream in(filepath);

		if (in.fail())
			return "";
		while (std::getline(in, line))
		{
			line += std::string("\n");
			buf += line;
		}

		char8 *ptr = new char8[buf.length()];
		strcpy(ptr, buf.c_str());
		string s(ptr);
		in.close();
#ifdef __IOS__
		delete[] ptr;
#endif
		return s;
	}
	string getContentFromPath(const string& filepath)
	{
		std::string buf("");
		std::string line("");
		std::ifstream in(filepath);

		if (in.fail())
			return "";
		while (std::getline(in, line))
		{
			line += std::string("\n");
			buf += line;
		}

		in.close();
#ifdef __IOS__
		delete[] ptr;
#endif
		return buf;
	}

	unsigned char * getContent(const char * filename)
	{
		FILE *file = fopen(filename, "rb");
		if (file == NULL)
		{
			return nullptr;
		}
		fseek(file, 0, SEEK_END);
		unsigned int length = ftell(file);
		unsigned char *loaded_data = (unsigned char *)calloc(length, sizeof(unsigned char));
		if (loaded_data == NULL)
		{
			return nullptr;
		}
		fseek(file, 0, SEEK_SET);
		size_t read = fread(loaded_data, sizeof(unsigned char), length, file);
		if (read != length)
		{
			return nullptr;
		}
		fclose(file);
		return loaded_data;
	}

	std::string GetFolder(std::string fullPath)
	{
		string folder, file;
		StringManipulator::SplitFileName(fullPath, folder, file);
		return folder;
	}

	std::string GetFileName(std::string fullPath)
	{
		string folder, file;
		StringManipulator::SplitFileName(fullPath, folder, file);
		return file;
	}

}
