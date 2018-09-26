//
//  Util.h
//
//  Created by 潘庆云 on 2017/2/7.
//

#ifndef Util_h
#define Util_h

#include "Include.h"
#include "../Source/vmath.h"
using namespace vvision;

#ifndef WIN32 
using DWORD = unsigned int;
using WORD = unsigned short;
#endif
using ULONG = unsigned long;

#define Interface struct
#define PI 180
#define NO_POS 9999,9999,9999
#define FAR_AWAY vec3f(NO_POS)

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->release(); (p)=nullptr; } }
#endif

#ifdef __WIN32__
#	if defined( E3D_STATIC )
#		define E3D_EXPORT_DLL
#	elif defined( E3D_BUILD_DLL )
#		define E3D_EXPORT_DLL __declspec( dllexport )
#	else
#		define E3D_EXPORT_DLL __declspec( dllimport )
#	endif
#else
#	if __GNUC__ >= 4
#		define E3D_EXPORT_DLL  __attribute__ ((visibility("default")))
#	else
#		define E3D_EXPORT_DLL
#	endif
#endif

#define _Equal_
#define extends : public
#define implement : public
#define foreach for
#define is ==

#define NULL_SHADER 0
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ZERO_MEM_VAR(var) memset(&var, 0, sizeof(var))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

#ifdef _WIN32
typedef unsigned int		uint;
#endif
typedef unsigned char	uchar8;
typedef signed char		schar8;
typedef char			char8;
typedef unsigned short	ushort16;
typedef signed short	sshort16;
typedef unsigned int	uint32;
typedef signed int		sint32;
typedef  int			int32;
typedef float			float32;
typedef double			float64;

#ifndef __IOS__
#define GLchar char
#endif
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&){ }               \
	void operator=(const TypeName&) { }

#define CLEAR_MAP(key, vealue, dest_map)\
	std::map<key, value> swapMap; \
	dest_map.swap(dest_map);

#if _MSC_VER
#define snprintf _snprintf
#endif

#ifndef GLES_STRING
#define GLES_STRING(x)     #x
#endif

#ifndef BOOL
#define BOOL int
#endif

#define empty_string ""

struct Vector2
{
	float x;
	float y;
	Vector2()
	{

	}
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct Color4
{
	float r;
	float g;
	float b;
	float a;
	Color4() { }
	Color4(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};

// 随机值： fLow - fHigh
float RangeRandom(float fLow, float fHigh);
// 随机值： (-1) - (1)
float SymmetricRandom();
// 给给定的数圈定范围
float RangeNumber(float &number, float max, float min);
#endif /* Util_h */
