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
//using UINT = unsigned int;
using ULONG = unsigned long;
#ifdef _WIN32
typedef unsigned int		uint
#endif
#define Interface struct
#define PI 180
#define NO_POS 9999,9999,9999
#define FAR_AWAY vec3f(NO_POS)

#define MATERIAL_CONFIG_ID   0xFFFFFFFFFFFFFFFF
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { /*if(p) { delete (p);     (p)=nullptr; }*/ }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->release(); (p)=nullptr; } }
#endif

#define EX_PORT __declspec(dllexport)

#define NULL_RETURN(OBJ)\
if (OBJ == nullptr)\
{\
	return; \
}
#define NOT_ACTIVE_RETURN(OBJ)\
if (OBJ != 0)\
{\
if (!OBJ->IsActive)\
{\
	return; \
}\
}

; typedef enum
{
	ets_NotTrig = 0, // 未触发
	ets_HasTrig = 1, // 已触发
} eTrigState;

#define _Equal_
#define extends : public
#define implement : public
#define foreach for
//#define in :
#define is ==

#define NULL_SHADER 0
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ZERO_MEM_VAR(var) memset(&var, 0, sizeof(var))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define GLCheckError() (glGetError() == GL_NO_ERROR)

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

#ifndef __out_call_function__
#define __out_call_function__
#define __out_func__
using CompleteCallback = __out_call_function__ void(*)(void * context, void * e, int width, int height, int size);
#endif

#ifndef BOOL
#define BOOL int
#endif

#define empty_string ""

enum
{
	/** vertex attrib*/
	LOCATION_ATTRIB_VERTEX,
	/** color attrib*/
	LOCATION_ATTRIB_COLOR,
	/** normal attrib*/
	LOCATION_ATTRIB_NORMAL,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE0,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE1,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE2,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE3,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE4,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE5,
	/** texture 0 coord attrib*/
	LOCATION_ATTRIB_TEXTURE6,
	/** texture 1 coord attrib*/
	LOCATION_ATTRIB_TEXTURE7,
	/** tangent coord attrib*/
	LOCATION_ATTRIB_TANGENT,
	/** bone index attrib*/
	LOCATION_ATTRIB_BONES_INDICES,
	/** bone weight attrib*/
	LOCATION_ATTRIB_BONES_WEIGHTS,

	LOCATION_ATTRIB_TRANSFORM_POSITION,	
	LOCATION_ATTRIB_TRANSFORM_SCALE,
	LOCATION_ATTRIB_TRANSFORM_ROTETION,
	LOCATION_ATTRIB_DYNAMIC_COLOR,

	LOCATION_ATTRIB_FRAGMENT_INDEX,

};

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


typedef enum
{
	IOS = 0,
	ANDROID_ = 1,
	OTHER,
}eTargetPlatform;

// 随机值： fLow - fHigh
float RangeRandom(float fLow, float fHigh);
// 随机值： (-1) - (1)
float SymmetricRandom();
// 四维向量转三维向量
vec3f V42V3(vec4f vec);
// 三维向量转四维向量
vec4f V32V4(vec3f vec);
// 给给定的数圈定范围
float RangeNumber(float &number, float max, float min);
// 将AssimpMatrix 转为 mat4f

#ifndef __EDITOR__
mat4f ConvertAiMatrix4x42Mat4f(aiMatrix4x4 mat);
#endif

template <class T> int getArrayLen(T& array)
{
	return (sizeof(array) / sizeof(array[0]) - 1);
}
long getCurrentTime();

#endif /* Util_h */
