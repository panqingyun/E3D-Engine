/*
 *  FilePath.cpp
 *  Virtual Vision
 *
 *  Created by Abdallah Dib Abdallah.dib@virtual-vison.net
 *  Copyright 2011 Virtual Vision. All rights reserved.
 *
 */

#include "FilePath.h"
#ifdef WIN32
#include <png.h>
#include <pnginfo.h>
#include <atlimage.h>
#include <wingdi.h>
#endif

#ifdef __ANDROID__
#include <png.h>
#include <pnginfo.h>
#endif

#ifdef __IOS__
#include <fstream>
#include <iostream>
#include <CoreFoundation/CoreFoundation.h>
#import <QuartzCore/QuartzCore.h>
#endif
#include "Helpers.h"

namespace vvision
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
		ptr = new char8[CFStringGetLength(str)+1];
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
        if(fnm.find("/") == fnm.npos)
        {
            CFBundleRef mainBundle = CFBundleGetMainBundle();
            CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
            CFStringRef str = CFURLCopyFileSystemPath(resourcesURL,
                                                      kCFURLPOSIXPathStyle);
            CFRelease(resourcesURL);
            ptr = new char8[CFStringGetLength(str)+1];
            CFStringGetCString(str,
                               ptr,
                               FILENAME_MAX,
                               kCFStringEncodingASCII);
            CFRelease(str);

            std::string res(ptr);
            res += std::string("/");
            res += std::string(filename);

            delete[] ptr;
            ptr = new char8[res.length()+1];
            strcpy(ptr, res.c_str());
        }

        else
        {
            ptr = new char8[fnm.length()+1];
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
        fseek( file, 0, SEEK_END );
        length = ftell( file );
        fseek( file, 0, SEEK_SET );
        char* buf = new char[ length + 1 ];
        buf[0] = 0;

        fread( buf, length, 1, file );
        return buf;
    }

    string getContentFromPath(const char8 *filepath)
    {
        std::string buf("");
        std::string line("");
        std::ifstream in(filepath);

        if(in.fail())
            return "";
        while(std::getline(in,line))
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

    char8* LoadImage(const char8* filename, int32 *width, int32 *height)
    {
        const char8 *filepath = filename;
		void *imageData = NULL;
#ifdef __IOS__
        CGDataProviderRef texturefiledata = CGDataProviderCreateWithFilename(filepath);

        if(!texturefiledata)
        {
            return NULL;
        }

        string extension;
        StringManipulator::GetExtensitonType(filename,extension);
        StringManipulator::ToLowerCase(extension);
        bool Ispng = StringManipulator::IsEqual(extension,"png") == 0;
        bool IsJpg = StringManipulator::IsEqual(extension,"jpg") == 0;

        CGImageRef textureImage;
        if(IsJpg)
            textureImage = CGImageCreateWithJPEGDataProvider(texturefiledata,
                                                             NULL,
                                                             true,
                                                             kCGRenderingIntentDefault);
        else if (Ispng)
            textureImage = CGImageCreateWithPNGDataProvider(texturefiledata,
                                                            NULL,
                                                            true,
                                                            kCGRenderingIntentDefault);
        else {
            cerr<<"LoadPng: unsupported image type:"<<extension<<"\n";
            CGDataProviderRelease(texturefiledata);
            return NULL;
        }

        CGDataProviderRelease(texturefiledata);
        *width = (int32)CGImageGetWidth(textureImage);
        *height = (int32)CGImageGetHeight(textureImage);
        imageData = malloc( *height * *width * 4 );
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef textureContext = CGBitmapContextCreate( imageData,
                                                            *width,
                                                            *height,
                                                            8, 4 * *width,
                                                            colorSpace,
                                                            kCGImageAlphaPremultipliedLast |
                                                            kCGBitmapByteOrder32Big );

        CGContextDrawImage( textureContext,
                           CGRectMake( 0,
                                      0,
                                      *width,
                                      *height ),
                           textureImage );

        CFRelease(textureContext);
        CGImageRelease(textureImage);
        CFRelease(colorSpace);
#endif
#ifdef __ANDROID__
		png_datap t = new png_data_t;
        int result = png_read(filename, t);
        if(result != PNG_READ_SUCCESS) {
            return NULL;
        }
        imageData = t->data;
        *width = t->width;
        *height = t->height;

#endif
		return (char8*)imageData;
    }
#ifndef __IOS__
	char8* LoadImageW(const string& filename, int32 *width, int32 *height)
	{
		string extension;
		StringManipulator::GetExtensitonType(filename, extension);
		StringManipulator::ToLowerCase(extension);
		bool Ispng = StringManipulator::IsEqual(extension, "png") == 0;
		bool Isetc = StringManipulator::IsEqual(extension, "pkm") == 0;
		void *imageData = NULL;
		if (Ispng)
		{
			png_datap t = new png_data_t;
			int result = png_read(filename.c_str(), t);
			if (result != PNG_READ_SUCCESS) {
				return NULL;
			}
			imageData = t->data;
			*width = t->width;
			*height = t->height;
		}
		else if (Isetc)
		{
			/*const int       sizeOfETCHeader = 16;
			unsigned char*  tempTextureData = getContent(filename.c_str());

			if (tempTextureData != NULL)
			{
				ETCHeader etcHeader(tempTextureData);
				imageData = tempTextureData + sizeOfETCHeader;
				*width = etcHeader.getWidth();
				*height = etcHeader.getHeight();
			}*/
		}
		return (char8*)imageData;
	}
#endif

#ifndef WIN32
    char8* LoadImage(const string& filename, int32 *width, int32 *height)
    {
        return LoadImage(filename.c_str(), width, height);
    }
#endif

	std::string GetFolder(std::string fullPath)
	{
		string folder, file;
		StringManipulator::SplitFileName(fullPath, folder, file);
		return folder;
	}

    char8* LoadImageFromTga(const char8* filename, int32 *width, int32 *height)
    {
        return NULL;
    }

#ifndef __IOS__
	void readFileCallback(png_structp png_ptr, png_bytep destination, png_size_t bytesToRead)
	{
		png_voidp io_ptr = png_get_io_ptr(png_ptr);

		if( io_ptr == 0 )
		{
			return;
		}

		png_voidp a = png_get_io_ptr(png_ptr);
		((std::istream*)a)->read((char*)destination, bytesToRead);
	}
	int png_read(const char* filename, png_datap data)
	{
		FILE *fp = fopen(filename, "rb");
		if (fp == NULL) return PNG_ERROR_NO_FILE;

		fseek(fp, 0, SEEK_END);
		int fSize = ftell(fp);
		rewind(fp);
		unsigned char* header = (unsigned char*)malloc(PNG_READ_HEADER);
		fread(header, 1, PNG_READ_HEADER, fp);
		int is_png = !png_sig_cmp(header, 0, PNG_READ_HEADER);
		if (!is_png) return PNG_ERROR_NOT_PNG;

		png_structp png_ptr;
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr) return PNG_ERROR_CREATE_PNG_STRUCT;

		png_infop info_ptr;
		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			printf("create info struct failed!\n");
			png_destroy_read_struct(&png_ptr, NULL, NULL);
			return PNG_ERROR_CREATE_INFO_STRUCT;
		}
		png_infop end_info;
		end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			printf("create end info failed!\n");
			png_destroy_read_struct(&png_ptr, NULL, NULL);
			return PNG_ERROR_CREATE_INFO_STRUCT;
		}
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			return PNG_ERROR_JMP;
		}
		png_init_io(png_ptr, fp);
		png_set_sig_bytes(png_ptr, PNG_READ_HEADER);
		// png_voidp user_chunk_ptr = png_get_user_chunk_ptr(png_ptr);
		// png_set_read_user_chunk_fn(png_ptr,user_chunk_ptr,read_chunk_callback);
		// png_set_keep_unknown_chunks(png_ptr,PNG_HANDLE_CHUNK_NEVER,NULL,0);

		//png_set_read_status_fn(png_ptr,read_row_callback);

		//low lever read
		png_read_info(png_ptr, info_ptr);
		png_uint_32 width;
		png_uint_32 height;
		int bit_depth;
		int color_type;
		png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);
		// printf("width:%d,height:%d,bit_depth:%d,color_type:%d",width,height,bit_depth,color_type);

		png_bytep raw_data = (png_bytep)malloc(width*height * 4 * sizeof(png_byte));
		// printf("row bytes:%d\n",png_get_rowbytes(png_ptr,info_ptr));

		png_bytep *row_pointers = (png_bytep*)malloc(height*sizeof(png_bytep));
		for (int i = 0; i<height; i++)
		{
			row_pointers[i] = raw_data + i* (width * 4);
		}

		png_read_image(png_ptr, row_pointers);
		data->width = width;
		data->height = height;
		data->data = (char*)raw_data;
		// printf("png_read_success\n");

		//clean
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(row_pointers);
		return PNG_READ_SUCCESS;
	}

#endif

	unsigned char * readBmp(const char *bmpName, int &bmpwidth, int &bmpheight)
	{
		int linebyte;
		unsigned char *pBmpBuf;  //存储图像数据  
		FILE *fp;
		if ((fp = fopen(bmpName, "rb")) == NULL)  //以二进制的方式打开文件  
		{
			cout << "The file " << bmpName << "was not opened" << endl;
			return nullptr;
		}
		if (fseek(fp, sizeof(BITMAPFILEHEADER), 0))  //跳过BITMAPFILEHEADE  
		{
			return nullptr;
		}
		BITMAPINFOHEADER infoHead;
		fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);   //从fp中读取BITMAPINFOHEADER信息到infoHead中,同时fp的指针移动  
		bmpwidth = infoHead.biWidth;
		bmpheight = infoHead.biHeight;
		linebyte = (bmpwidth * 24 / 8 + 3) / 4 * 4; //计算每行的字节数，24：该图片是24位的bmp图，3：确保不丢失像素  

													//cout<<bmpwidth<<" "<<bmpheight<<endl;  
		pBmpBuf = new unsigned char[linebyte*bmpheight];
		fread(pBmpBuf, sizeof(char), linebyte*bmpheight, fp);
		fclose(fp);   //关闭文件  
		return pBmpBuf;
	}

}
