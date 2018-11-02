#pragma once
namespace E3DEngine
{

#ifdef _WIN32
#include <windows.h>
	typedef void            GLvoid;
	typedef unsigned int    GLenum;
	typedef unsigned char   GLboolean;
	typedef unsigned int    GLbitfield;
	typedef signed char     GLbyte;
	typedef short           GLshort;
	typedef int             GLint;
	typedef int             GLsizei;
	typedef unsigned char   GLubyte;
	typedef unsigned short  GLushort;
	typedef unsigned int    GLuint;
	typedef float           GLfloat;
	typedef float           GLclampf;
	typedef int             GLfixed;
	typedef int             GLclampx;

	/* GL types for handling large vertex buffer objects */
	typedef int             GLintptr;
	typedef int             GLsizeiptr;

	/* OpenGL ES core versions */
#define GL_ES_VERSION_2_0                 1

	/* ClearBufferMask */
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

	/* Boolean */
#define GL_FALSE                          0
#define GL_TRUE                           1

	/* \todo check that this should be in core. */
#define GL_NONE                           0

	/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

	/* AlphaFunction (not supported in ES20) */
	/*      GL_NEVER */
	/*      GL_LESS */
	/*      GL_EQUAL */
	/*      GL_LEQUAL */
	/*      GL_GREATER */
	/*      GL_NOTEQUAL */
	/*      GL_GEQUAL */
	/*      GL_ALWAYS */

	/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

	/* BlendingFactorSrc */
	/*      GL_ZERO */
	/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
	/*      GL_SRC_ALPHA */
	/*      GL_ONE_MINUS_SRC_ALPHA */
	/*      GL_DST_ALPHA */
	/*      GL_ONE_MINUS_DST_ALPHA */

	/* BlendEquationSeparate */
#define GL_FUNC_ADD                       0x8006
#define GL_BLEND_EQUATION                 0x8009
#define GL_BLEND_EQUATION_RGB             0x8009    /* same as BLEND_EQUATION */
#define GL_BLEND_EQUATION_ALPHA           0x883D

	/* BlendSubtract */
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B

	/* Separate Blend Functions */
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_BLEND_COLOR                    0x8005

	/* Buffer Objects */
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895

#define GL_STREAM_DRAW                    0x88E0
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765

#define GL_CURRENT_VERTEX_ATTRIB          0x8626

	/* CullFaceMode */
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408

	/* DepthFunction */
	/*      GL_NEVER */
	/*      GL_LESS */
	/*      GL_EQUAL */
	/*      GL_LEQUAL */
	/*      GL_GREATER */
	/*      GL_NOTEQUAL */
	/*      GL_GEQUAL */
	/*      GL_ALWAYS */

	/* EnableCap */
#define GL_TEXTURE_2D                     0x0DE1
#define GL_CULL_FACE                      0x0B44
#define GL_BLEND                          0x0BE2
#define GL_DITHER                         0x0BD0
#define GL_STENCIL_TEST                   0x0B90
#define GL_DEPTH_TEST                     0x0B71
#define GL_SCISSOR_TEST                   0x0C11
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_COVERAGE                0x80A0

	/* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505

	/* FrontFaceDirection */
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

	/* GetPName */
#define GL_LINE_WIDTH                     0x0B21
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#define GL_VIEWPORT                       0x0BA2
#define GL_SCISSOR_BOX                    0x0C10
	/*      GL_SCISSOR_TEST */
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_POLYGON_OFFSET_UNITS           0x2A00
	/*      GL_POLYGON_OFFSET_FILL */
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB

	/* GetTextureParameter */
	/*      GL_TEXTURE_MAG_FILTER */
	/*      GL_TEXTURE_MIN_FILTER */
	/*      GL_TEXTURE_WRAP_S */
	/*      GL_TEXTURE_WRAP_T */

#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3

	/* HintMode */
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102

	/* HintTarget */
#define GL_GENERATE_MIPMAP_HINT            0x8192
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B

	/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_FIXED                          0x140C

	/* PixelFormat */
#define GL_DEPTH_COMPONENT                0x1902
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

	/* PixelType */
	/*      GL_UNSIGNED_BYTE */
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_5_6_5           0x8363

	/* Shaders */
#define GL_FRAGMENT_SHADER                  0x8B30
#define GL_VERTEX_SHADER                    0x8B31
#define GL_MAX_VERTEX_ATTRIBS               0x8869
#define GL_MAX_VERTEX_UNIFORM_VECTORS       0x8DFB
#define GL_MAX_VARYING_VECTORS              0x8DFC
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS   0x8B4C
#define GL_MAX_TEXTURE_IMAGE_UNITS          0x8872
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS     0x8DFD
#define GL_SHADER_TYPE                      0x8B4F
#define GL_DELETE_STATUS                    0x8B80
#define GL_LINK_STATUS                      0x8B82
#define GL_VALIDATE_STATUS                  0x8B83
#define GL_ATTACHED_SHADERS                 0x8B85
#define GL_ACTIVE_UNIFORMS                  0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH        0x8B87
#define GL_ACTIVE_ATTRIBUTES                0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH      0x8B8A
#define GL_SHADING_LANGUAGE_VERSION         0x8B8C
#define GL_CURRENT_PROGRAM                  0x8B8D

	/* StencilFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

	/* StencilOp */
	/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_INVERT                         0x150A
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508

	/* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

	/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

	/* TextureMinFilter */
	/*      GL_NEAREST */
	/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

	/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803

	/* TextureTarget */
	/*      GL_TEXTURE_2D */
#define GL_TEXTURE                        0x1702

#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C

	/* TextureUnit */
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0

	/* TextureWrapMode */
#define GL_REPEAT                         0x2901
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_MIRRORED_REPEAT                0x8370

	/* Uniform Types */
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_CUBE                   0x8B60

	/* Vertex Arrays */
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED        0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE           0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE         0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE           0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED     0x886A
#define GL_VERTEX_ATTRIB_ARRAY_POINTER        0x8645
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F

	/* Read Format */
#define GL_IMPLEMENTATION_COLOR_READ_TYPE   0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B

	/* Shader Source */
#define GL_COMPILE_STATUS                 0x8B81
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_SHADER_COMPILER                0x8DFA

	/* Shader Binary */
#define GL_PLATFORM_BINARY                0x8D63
#define GL_SHADER_BINARY_FORMATS          0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS      0x8DF9

	/* Shader Precision-Specified Types */
#define GL_LOW_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_HIGH_FLOAT                     0x8DF2
#define GL_LOW_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_HIGH_INT                       0x8DF5

	/* Framebuffer Object. */
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41

#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGB565                         0x8D62
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_STENCIL_INDEX                  0x1901
#define GL_STENCIL_INDEX8                 0x8D48

#define GL_RENDERBUFFER_WIDTH             0x8D42
#define GL_RENDERBUFFER_HEIGHT            0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE      0x8D55

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE           0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME           0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL         0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3

#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20

#define GL_FRAMEBUFFER_COMPLETE                      0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT         0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS         0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS            0x8CDA
#define GL_FRAMEBUFFER_UNSUPPORTED                   0x8CDD

#define GL_FRAMEBUFFER_BINDING            0x8CA6
#define GL_RENDERBUFFER_BINDING           0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE          0x84E8

#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506

#else
#define APIENTRY
#endif

	namespace ES2
	{
		typedef void(APIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
		typedef void(APIENTRY * PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
		typedef void(APIENTRY * PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const char* name);
		typedef void(APIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
		typedef void(APIENTRY * PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
		typedef void(APIENTRY * PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
		typedef void(APIENTRY * PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
		typedef void(APIENTRY * PFNGLBLENDCOLORPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		typedef void(APIENTRY * PFNGLBLENDEQUATIONPROC) (GLenum mode);
		typedef void(APIENTRY * PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
		typedef void(APIENTRY * PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
		typedef void(APIENTRY * PFNGLBLENDFUNCSEPARATEPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
		typedef void(APIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
		typedef void(APIENTRY * PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
		typedef GLenum(APIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
		typedef void(APIENTRY * PFNGLCLEARPROC) (GLbitfield mask);
		typedef void(APIENTRY * PFNGLCLEARCOLORPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		typedef void(APIENTRY * PFNGLCLEARDEPTHFPROC) (GLclampf depth);
		typedef void(APIENTRY * PFNGLCLEARSTENCILPROC) (GLint s);
		typedef void(APIENTRY * PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		typedef void(APIENTRY * PFNGLCOMPILESHADERPROC) (GLuint shader);
		typedef void(APIENTRY * PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
		typedef void(APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
		typedef void(APIENTRY * PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		typedef void(APIENTRY * PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		typedef GLuint(APIENTRY * PFNGLCREATEPROGRAMPROC) (void);
		typedef GLuint(APIENTRY * PFNGLCREATESHADERPROC) (GLenum type);
		typedef void(APIENTRY * PFNGLCULLFACEPROC) (GLenum mode);
		typedef void(APIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint* buffers);
		typedef void(APIENTRY * PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint* framebuffers);
		typedef void(APIENTRY * PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint* textures);
		typedef void(APIENTRY * PFNGLDELETEPROGRAMPROC) (GLuint program);
		typedef void(APIENTRY * PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint* renderbuffers);
		typedef void(APIENTRY * PFNGLDELETESHADERPROC) (GLuint shader);
		typedef void(APIENTRY * PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
		typedef void(APIENTRY * PFNGLDEPTHFUNCPROC) (GLenum func);
		typedef void(APIENTRY * PFNGLDEPTHMASKPROC) (GLboolean flag);
		typedef void(APIENTRY * PFNGLDEPTHRANGEFPROC) (GLclampf zNear, GLclampf zFar);
		typedef void(APIENTRY * PFNGLDISABLEPROC) (GLenum cap);
		typedef void(APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
		typedef void(APIENTRY * PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
		typedef void(APIENTRY * PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
		typedef void(APIENTRY * PFNGLENABLEPROC) (GLenum cap);
		typedef void(APIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
		typedef void(APIENTRY * PFNGLFINISHPROC) (void);
		typedef void(APIENTRY * PFNGLFLUSHPROC) (void);
		typedef void(APIENTRY * PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		typedef void(APIENTRY * PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		typedef void(APIENTRY * PFNGLFRONTFACEPROC) (GLenum mode);
		typedef void(APIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
		typedef void(APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target);
		typedef void(APIENTRY * PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint* framebuffers);
		typedef void(APIENTRY * PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint* renderbuffers);
		typedef void(APIENTRY * PFNGLGENTEXTURESPROC) (GLsizei n, GLuint* textures);
		typedef void(APIENTRY * PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name);
		typedef void(APIENTRY * PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name);
		typedef void(APIENTRY * PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
		typedef int (APIENTRY * PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const char* name);
		typedef void(APIENTRY * PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean* params);
		typedef void(APIENTRY * PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint* params);
		typedef GLenum(APIENTRY * PFNGLGETERRORPROC) (void);
		typedef void(APIENTRY * PFNGLGETFLOATVPROC) (GLenum pname, GLfloat* params);
		typedef void(APIENTRY * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETINTEGERVPROC) (GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufsize, GLsizei* length, char* infolog);
		typedef void(APIENTRY * PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog);
		typedef void(APIENTRY * PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
		typedef void(APIENTRY * PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufsize, GLsizei* length, char* source);
		typedef const GLubyte*(APIENTRY * PFNGLGLGETSTRINGPROC) (GLenum name);
		typedef void(APIENTRY * PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat* params);
		typedef void(APIENTRY * PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat* params);
		typedef void(APIENTRY * PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint* params);
		typedef int (APIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const char* name);
		typedef void(APIENTRY * PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat* params);
		typedef void(APIENTRY * PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint* params);
		typedef void(APIENTRY * PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void** pointer);
		typedef void(APIENTRY * PFNGLHINTPROC) (GLenum target, GLenum mode);
		typedef GLboolean(APIENTRY * PFNGLISBUFFERPROC) (GLuint buffer);
		typedef GLboolean(APIENTRY * PFNGLISENABLEDPROC) (GLenum cap);
		typedef GLboolean(APIENTRY * PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
		typedef GLboolean(APIENTRY * PFNGLISPROGRAMPROC) (GLuint program);
		typedef GLboolean(APIENTRY * PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
		typedef GLboolean(APIENTRY * PFNGLISSHADERPROC) (GLuint shader);
		typedef GLboolean(APIENTRY * PFNGLISTEXTUREPROC) (GLuint texture);
		typedef void(APIENTRY * PFNGLLINEWIDTHPROC) (GLfloat width);
		typedef void(APIENTRY * PFNGLLINKPROGRAMPROC) (GLuint program);
		typedef void(APIENTRY * PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
		typedef void(APIENTRY * PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
		typedef void(APIENTRY * PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
		typedef void(APIENTRY * PFNGLRELEASESHADERCOMPILERPROC) (void);
		typedef void(APIENTRY * PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		typedef void(APIENTRY * PFNGLSAMPLECOVERAGEPROC) (GLclampf value, GLboolean invert);
		typedef void(APIENTRY * PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
		typedef void(APIENTRY * PFNGLSHADERBINARYPROC) (GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length);
		typedef void(APIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const char** string, const GLint* length);
		typedef void(APIENTRY * PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
		typedef void(APIENTRY * PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
		typedef void(APIENTRY * PFNGLSTENCILMASKPROC) (GLuint mask);
		typedef void(APIENTRY * PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
		typedef void(APIENTRY * PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
		typedef void(APIENTRY * PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
		typedef void(APIENTRY * PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
		typedef void(APIENTRY * PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
		typedef void(APIENTRY * PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat* params);
		typedef void(APIENTRY * PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
		typedef void(APIENTRY * PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint* params);
		typedef void(APIENTRY * PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
		typedef void(APIENTRY * PFNGLUNIFORM1FPROC) (GLint location, GLfloat x);
		typedef void(APIENTRY * PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat* v);
		typedef void(APIENTRY * PFNGLUNIFORM1IPROC) (GLint location, GLint x);
		typedef void(APIENTRY * PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint* v);
		typedef void(APIENTRY * PFNGLUNIFORM2FPROC) (GLint location, GLfloat x, GLfloat y);
		typedef void(APIENTRY * PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat* v);
		typedef void(APIENTRY * PFNGLUNIFORM2IPROC) (GLint location, GLint x, GLint y);
		typedef void(APIENTRY * PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint* v);
		typedef void(APIENTRY * PFNGLUNIFORM3FPROC) (GLint location, GLfloat x, GLfloat y, GLfloat z);
		typedef void(APIENTRY * PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat* v);
		typedef void(APIENTRY * PFNGLUNIFORM3IPROC) (GLint location, GLint x, GLint y, GLint z);
		typedef void(APIENTRY * PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint* v);
		typedef void(APIENTRY * PFNGLUNIFORM4FPROC) (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		typedef void(APIENTRY * PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat* v);
		typedef void(APIENTRY * PFNGLUNIFORM4IPROC) (GLint location, GLint x, GLint y, GLint z, GLint w);
		typedef void(APIENTRY * PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint* v);
		typedef void(APIENTRY * PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		typedef void(APIENTRY * PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		typedef void(APIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		typedef void(APIENTRY * PFNGLUSEPROGRAMPROC) (GLuint program);
		typedef void(APIENTRY * PFNGLVALIDATEPROGRAMPROC) (GLuint program);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB1FPROC) (GLuint indx, GLfloat x);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB1FVPROC) (GLuint indx, const GLfloat* values);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB2FPROC) (GLuint indx, GLfloat x, GLfloat y);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB2FVPROC) (GLuint indx, const GLfloat* values);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB3FPROC) (GLuint indx, GLfloat x, GLfloat y, GLfloat z);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB3FVPROC) (GLuint indx, const GLfloat* values);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB4FPROC) (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		typedef void(APIENTRY * PFNGLVERTEXATTRIB4FVPROC) (GLuint indx, const GLfloat* values);
		typedef void(APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr);
		typedef void(APIENTRY * PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
		typedef void*(APIENTRY * PFNGLMAPBUFFEROESPROC)(GLenum target, GLenum access);
		typedef GLboolean(APIENTRY * PFNGLUNMAPBUFFEROESPROC)(GLenum target);

		void LoadESLibrary();

		void   ActiveTexture(GLenum texture);
		void   AttachShader(GLuint program, GLuint shader);
		void   BindAttribLocation(GLuint program, GLuint index, const char* name);
		void   BindBuffer(GLenum target, GLuint buffer);
		void   BindFramebuffer(GLenum target, GLuint framebuffer);
		void   BindRenderbuffer(GLenum target, GLuint renderbuffer);
		void   BindTexture(GLenum target, GLuint texture);
		void   BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		void   BlendEquation(GLenum mode);
		void   BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
		void   BlendFunc(GLenum sfactor, GLenum dfactor);
		void   BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
		void   BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
		void   BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
		GLenum CheckFramebufferStatus(GLenum target);
		void   Clear(GLbitfield mask);
		void   ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		void   ClearDepthf(GLclampf depth);
		void   ClearStencil(GLint s);
		void   ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		void   CompileShader(GLuint shader);
		void   CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
		void   CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
		void   CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		void   CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		GLuint CreateProgram(void);
		GLuint CreateShader(GLenum type);
		void   CullFace(GLenum mode);
		void   DeleteBuffers(GLsizei n, const GLuint* buffers);
		void   DeleteFramebuffers(GLsizei n, const GLuint* framebuffers);
		void   DeleteTextures(GLsizei n, const GLuint* textures);
		void   DeleteProgram(GLuint program);
		void   DeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
		void   DeleteShader(GLuint shader);
		void   DetachShader(GLuint program, GLuint shader);
		void   DepthFunc(GLenum func);
		void   DepthMask(GLboolean flag);
		void   DepthRangef(GLclampf zNear, GLclampf zFar);
		void   Disable(GLenum cap);
		void   DisableVertexAttribArray(GLuint index);
		void   DrawArrays(GLenum mode, GLint first, GLsizei count);
		void   DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
		void   Enable(GLenum cap);
		void   EnableVertexAttribArray(GLuint index);
		void   Finish(void);
		void   Flush(void);
		void   FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		void   FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		void   FrontFace(GLenum mode);
		void   GenBuffers(GLsizei n, GLuint* buffers);
		void   GenerateMipmap(GLenum target);
		void   GenFramebuffers(GLsizei n, GLuint* framebuffers);
		void   GenRenderbuffers(GLsizei n, GLuint* renderbuffers);
		void   GenTextures(GLsizei n, GLuint* textures);
		void   GetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name);
		void   GetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name);
		void   GetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
		int    GetAttribLocation(GLuint program, const char* name);
		void   GetBooleanv(GLenum pname, GLboolean* params);
		void   GetBufferParameteriv(GLenum target, GLenum pname, GLint* params);
		GLenum GetError(void);
		void   GetFloatv(GLenum pname, GLfloat* params);
		void   GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
		void   GetIntegerv(GLenum pname, GLint* params);
		void   GetProgramiv(GLuint program, GLenum pname, GLint* params);
		void   GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog);
		void   GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
		void   GetShaderiv(GLuint shader, GLenum pname, GLint* params);
		void   GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog);
		void   GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
		void   GetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source);
		const GLubyte* glGetString(GLenum name);
		void       GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
		void       GetTexParameteriv(GLenum target, GLenum pname, GLint* params);
		void       GetUniformfv(GLuint program, GLint location, GLfloat* params);
		void       GetUniformiv(GLuint program, GLint location, GLint* params);
		int        GetUniformLocation(GLuint program, const char* name);
		void       GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params);
		void       GetVertexAttribiv(GLuint index, GLenum pname, GLint* params);
		void       GetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer);
		void       Hint(GLenum target, GLenum mode);
		GLboolean  IsBuffer(GLuint buffer);
		GLboolean  IsEnabled(GLenum cap);
		GLboolean  IsFramebuffer(GLuint framebuffer);
		GLboolean  IsProgram(GLuint program);
		GLboolean  IsRenderbuffer(GLuint renderbuffer);
		GLboolean  IsShader(GLuint shader);
		GLboolean  IsTexture(GLuint texture);
		void       LineWidth(GLfloat width);
		void       LinkProgram(GLuint program);
		void       PixelStorei(GLenum pname, GLint param);
		void       PolygonOffset(GLfloat factor, GLfloat units);
		void       ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
		void       ReleaseShaderCompiler(void);
		void       RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		void       SampleCoverage(GLclampf value, GLboolean invert);
		void       Scissor(GLint x, GLint y, GLsizei width, GLsizei height);
		void       ShaderBinary(GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length);
		void       ShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length);
		void       StencilFunc(GLenum func, GLint ref, GLuint mask);
		void       StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
		void       StencilMask(GLuint mask);
		void       StencilMaskSeparate(GLenum face, GLuint mask);
		void       StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
		void       StencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
		void       TexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
		void       TexParameterf(GLenum target, GLenum pname, GLfloat param);
		void       TexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
		void       TexParameteri(GLenum target, GLenum pname, GLint param);
		void       TexParameteriv(GLenum target, GLenum pname, const GLint* params);
		void       TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
		void       Uniform1f(GLint location, GLfloat x);
		void       Uniform1fv(GLint location, GLsizei count, const GLfloat* v);
		void       Uniform1i(GLint location, GLint x);
		void       Uniform1iv(GLint location, GLsizei count, const GLint* v);
		void       Uniform2f(GLint location, GLfloat x, GLfloat y);
		void       Uniform2fv(GLint location, GLsizei count, const GLfloat* v);
		void       Uniform2i(GLint location, GLint x, GLint y);
		void       Uniform2iv(GLint location, GLsizei count, const GLint* v);
		void       Uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
		void       Uniform3fv(GLint location, GLsizei count, const GLfloat* v);
		void       Uniform3i(GLint location, GLint x, GLint y, GLint z);
		void       Uniform3iv(GLint location, GLsizei count, const GLint* v);
		void       Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		void       Uniform4fv(GLint location, GLsizei count, const GLfloat* v);
		void       Uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
		void       Uniform4iv(GLint location, GLsizei count, const GLint* v);
		void       UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		void       UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		void       UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		void       UseProgram(GLuint program);
		void       ValidateProgram(GLuint program);
		void       VertexAttrib1f(GLuint indx, GLfloat x);
		void       VertexAttrib1fv(GLuint indx, const GLfloat* values);
		void       VertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
		void       VertexAttrib2fv(GLuint indx, const GLfloat* values);
		void       VertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
		void       VertexAttrib3fv(GLuint indx, const GLfloat* values);
		void       VertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		void       VertexAttrib4fv(GLuint indx, const GLfloat* values);
		void       VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr);
		void       Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
		void*	   MapBufferOES(GLenum target, GLenum access);
		GLboolean  UnMapBufferOES(GLenum target);
	}
}