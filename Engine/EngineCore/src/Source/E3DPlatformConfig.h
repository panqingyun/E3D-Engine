#ifndef __E3D_PLATFORM_H__
#define __E3D_PLATFORM_H__

#define PLATFORM_WIN32 0
#define PLATFORM_ANDROID 1
#define PLATFORM_IOS 2

#ifdef WIN32
#define TARGET_PLATFORM PLATFORM_WIN32
#endif
#ifdef __ANDROID__
#define TARGET_PLATFORM PLATFORM_ANDROID
#endif
#ifdef __IOS__
#define TARGET_PLATFORM PLATFORM_IOS
#endif

unsigned int GetPlatform();

#endif