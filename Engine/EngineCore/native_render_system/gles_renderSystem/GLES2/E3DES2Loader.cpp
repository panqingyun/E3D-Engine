#include "E3DES2Loader.h"
#include <assert.h>

namespace E3DEngine
{
	namespace _GL_ES_2
	{
#define __String(x) #x
#ifdef WIN32
		HMODULE gESModule = nullptr;
		PFNGLACTIVETEXTUREPROC _glActiveTexture;
		PFNGLATTACHSHADERPROC _glAttachShader;
		PFNGLBINDATTRIBLOCATIONPROC _glBindAttribLocation;
		PFNGLBINDBUFFERPROC _glBindBuffer;
		PFNGLBINDFRAMEBUFFERPROC _glBindFramebuffer;
		PFNGLBINDRENDERBUFFERPROC _glBindRenderbuffer;
		PFNGLBINDTEXTUREPROC _glBindTexture;
		PFNGLBLENDCOLORPROC _glBlendColor;
		PFNGLBLENDEQUATIONPROC _glBlendEquation;
		PFNGLBLENDEQUATIONSEPARATEPROC _glBlendEquationSeparate;
		PFNGLBLENDFUNCPROC _glBlendFunc;
		PFNGLBLENDFUNCSEPARATEPROC _glBlendFuncSeparate;
		PFNGLBUFFERDATAPROC _glBufferData;
		PFNGLBUFFERSUBDATAPROC _glBufferSubData;
		PFNGLCHECKFRAMEBUFFERSTATUSPROC _glCheckFramebufferStatus;
		PFNGLCLEARPROC _glClear;
		PFNGLCLEARCOLORPROC _glClearColor;
		PFNGLCLEARDEPTHFPROC _glClearDepthf;
		PFNGLCLEARSTENCILPROC _glClearStencil;
		PFNGLCOLORMASKPROC _glColorMask;
		PFNGLCOMPILESHADERPROC _glCompileShader;
		PFNGLCOMPRESSEDTEXIMAGE2DPROC _glCompressedTexImage2D;
		PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC _glCompressedTexSubImage2D;
		PFNGLCOPYTEXIMAGE2DPROC _glCopyTexImage2D;
		PFNGLCOPYTEXSUBIMAGE2DPROC _glCopyTexSubImage2D;
		PFNGLCREATEPROGRAMPROC _glCreateProgram;
		PFNGLCREATESHADERPROC _glCreateShader;
		PFNGLCULLFACEPROC _glCullFace;
		PFNGLDELETEBUFFERSPROC _glDeleteBuffers;
		PFNGLDELETEFRAMEBUFFERSPROC _glDeleteFramebuffers;
		PFNGLDELETETEXTURESPROC _glDeleteTextures;
		PFNGLDELETEPROGRAMPROC _glDeleteProgram;
		PFNGLDELETERENDERBUFFERSPROC _glDeleteRenderbuffers;
		PFNGLDELETESHADERPROC _glDeleteShader;
		PFNGLDETACHSHADERPROC _glDetachShader;
		PFNGLDEPTHFUNCPROC _glDepthFunc;
		PFNGLDEPTHMASKPROC _glDepthMask;
		PFNGLDEPTHRANGEFPROC _glDepthRangef;
		PFNGLDISABLEPROC _glDisable;
		PFNGLDISABLEVERTEXATTRIBARRAYPROC _glDisableVertexAttribArray;
		PFNGLDRAWARRAYSPROC _glDrawArrays;
		PFNGLDRAWELEMENTSPROC _glDrawElements;
		PFNGLENABLEPROC _glEnable;
		PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray;
		PFNGLFINISHPROC _glFinish;
		PFNGLFLUSHPROC _glFlush;
		PFNGLFRAMEBUFFERRENDERBUFFERPROC _glFramebufferRenderbuffer;
		PFNGLFRAMEBUFFERTEXTURE2DPROC _glFramebufferTexture2D;
		PFNGLFRONTFACEPROC _glFrontFace;
		PFNGLGENBUFFERSPROC _glGenBuffers;
		PFNGLGENERATEMIPMAPPROC _glGenerateMipmap;
		PFNGLGENFRAMEBUFFERSPROC _glGenFramebuffers;
		PFNGLGENRENDERBUFFERSPROC _glGenRenderbuffers;
		PFNGLGENTEXTURESPROC _glGenTextures;
		PFNGLGETACTIVEATTRIBPROC _glGetActiveAttrib;
		PFNGLGETACTIVEUNIFORMPROC _glGetActiveUniform;
		PFNGLGETATTACHEDSHADERSPROC _glGetAttachedShaders;
		PFNGLGETATTRIBLOCATIONPROC _glGetAttribLocation;
		PFNGLGETBOOLEANVPROC _glGetBooleanv;
		PFNGLGETBUFFERPARAMETERIVPROC _glGetBufferParameteriv;
		PFNGLGETERRORPROC _glGetError;
		PFNGLGETFLOATVPROC _glGetFloatv;
		PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC _glGetFramebufferAttachmentParameteriv;
		PFNGLGETINTEGERVPROC _glGetIntegerv;
		PFNGLGETPROGRAMIVPROC _glGetProgramiv;
		PFNGLGETPROGRAMINFOLOGPROC _glGetProgramInfoLog;
		PFNGLGETRENDERBUFFERPARAMETERIVPROC _glGetRenderbufferParameteriv;
		PFNGLGETSHADERIVPROC _glGetShaderiv;
		PFNGLGETSHADERINFOLOGPROC _glGetShaderInfoLog;
		PFNGLGETSHADERPRECISIONFORMATPROC _glGetShaderPrecisionFormat;
		PFNGLGETSHADERSOURCEPROC _glGetShaderSource;
		PFNGLGLGETSTRINGPROC _glglGetString;
		PFNGLGETTEXPARAMETERFVPROC _glGetTexParameterfv;
		PFNGLGETTEXPARAMETERIVPROC _glGetTexParameteriv;
		PFNGLGETUNIFORMFVPROC _glGetUniformfv;
		PFNGLGETUNIFORMIVPROC _glGetUniformiv;
		PFNGLGETUNIFORMLOCATIONPROC _glGetUniformLocation;
		PFNGLGETVERTEXATTRIBFVPROC _glGetVertexAttribfv;
		PFNGLGETVERTEXATTRIBIVPROC _glGetVertexAttribiv;
		PFNGLGETVERTEXATTRIBPOINTERVPROC _glGetVertexAttribPointerv;
		PFNGLHINTPROC _glHint;
		PFNGLISBUFFERPROC _glIsBuffer;
		PFNGLISENABLEDPROC _glIsEnabled;
		PFNGLISFRAMEBUFFERPROC _glIsFramebuffer;
		PFNGLISPROGRAMPROC _glIsProgram;
		PFNGLISRENDERBUFFERPROC _glIsRenderbuffer;
		PFNGLISSHADERPROC _glIsShader;
		PFNGLISTEXTUREPROC _glIsTexture;
		PFNGLLINEWIDTHPROC _glLineWidth;
		PFNGLLINKPROGRAMPROC _glLinkProgram;
		PFNGLPIXELSTOREIPROC _glPixelStorei;
		PFNGLPOLYGONOFFSETPROC _glPolygonOffset;
		PFNGLREADPIXELSPROC _glReadPixels;
		PFNGLRELEASESHADERCOMPILERPROC _glReleaseShaderCompiler;
		PFNGLRENDERBUFFERSTORAGEPROC _glRenderbufferStorage;
		PFNGLSAMPLECOVERAGEPROC _glSampleCoverage;
		PFNGLSCISSORPROC _glScissor;
		PFNGLSHADERBINARYPROC _glShaderBinary;
		PFNGLSHADERSOURCEPROC _glShaderSource;
		PFNGLSTENCILFUNCPROC _glStencilFunc;
		PFNGLSTENCILFUNCSEPARATEPROC _glStencilFuncSeparate;
		PFNGLSTENCILMASKPROC _glStencilMask;
		PFNGLSTENCILMASKSEPARATEPROC _glStencilMaskSeparate;
		PFNGLSTENCILOPPROC _glStencilOp;
		PFNGLSTENCILOPSEPARATEPROC _glStencilOpSeparate;
		PFNGLTEXIMAGE2DPROC _glTexImage2D;
		PFNGLTEXPARAMETERFPROC _glTexParameterf;
		PFNGLTEXPARAMETERFVPROC _glTexParameterfv;
		PFNGLTEXPARAMETERIPROC _glTexParameteri;
		PFNGLTEXPARAMETERIVPROC _glTexParameteriv;
		PFNGLTEXSUBIMAGE2DPROC _glTexSubImage2D;
		PFNGLUNIFORM1FPROC _glUniform1f;
		PFNGLUNIFORM1FVPROC _glUniform1fv;
		PFNGLUNIFORM1IPROC _glUniform1i;
		PFNGLUNIFORM1IVPROC _glUniform1iv;
		PFNGLUNIFORM2FPROC _glUniform2f;
		PFNGLUNIFORM2FVPROC _glUniform2fv;
		PFNGLUNIFORM2IPROC _glUniform2i;
		PFNGLUNIFORM2IVPROC _glUniform2iv;
		PFNGLUNIFORM3FPROC _glUniform3f;
		PFNGLUNIFORM3FVPROC _glUniform3fv;
		PFNGLUNIFORM3IPROC _glUniform3i;
		PFNGLUNIFORM3IVPROC _glUniform3iv;
		PFNGLUNIFORM4FPROC _glUniform4f;
		PFNGLUNIFORM4FVPROC _glUniform4fv;
		PFNGLUNIFORM4IPROC _glUniform4i;
		PFNGLUNIFORM4IVPROC _glUniform4iv;
		PFNGLUNIFORMMATRIX2FVPROC _glUniformMatrix2fv;
		PFNGLUNIFORMMATRIX3FVPROC _glUniformMatrix3fv;
		PFNGLUNIFORMMATRIX4FVPROC _glUniformMatrix4fv;
		PFNGLUSEPROGRAMPROC _glUseProgram;
		PFNGLVALIDATEPROGRAMPROC _glValidateProgram;
		PFNGLVERTEXATTRIB1FPROC _glVertexAttrib1f;
		PFNGLVERTEXATTRIB1FVPROC _glVertexAttrib1fv;
		PFNGLVERTEXATTRIB2FPROC _glVertexAttrib2f;
		PFNGLVERTEXATTRIB2FVPROC _glVertexAttrib2fv;
		PFNGLVERTEXATTRIB3FPROC _glVertexAttrib3f;
		PFNGLVERTEXATTRIB3FVPROC _glVertexAttrib3fv;
		PFNGLVERTEXATTRIB4FPROC _glVertexAttrib4f;
		PFNGLVERTEXATTRIB4FVPROC _glVertexAttrib4fv;
		PFNGLVERTEXATTRIBPOINTERPROC _glVertexAttribPointer;
		PFNGLVIEWPORTPROC _glViewport;
		PFNGLMAPBUFFEROESPROC _glMapBufferOES;
		PFNGLUNMAPBUFFEROESPROC _glUnMapBufferOES;
#endif

		void LoadESLibrary()
		{
#ifdef WIN32
			gESModule = LoadLibrary("libGLESv2.dll");
			if (gESModule == nullptr)
			{
				assert(false);
				return;
			}
			_glActiveTexture = (PFNGLACTIVETEXTUREPROC)GetProcAddress(gESModule, __String(glActiveTexture));
			_glAttachShader = (PFNGLATTACHSHADERPROC)GetProcAddress(gESModule, __String(glAttachShader));
			_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)GetProcAddress(gESModule, __String(glBindAttribLocation));
			_glBindBuffer = (PFNGLBINDBUFFERPROC)GetProcAddress(gESModule, __String(glBindBuffer));
			_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)GetProcAddress(gESModule, __String(glBindFramebuffer));
			_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)GetProcAddress(gESModule, __String(glBindRenderbuffer));
			_glBindTexture = (PFNGLBINDTEXTUREPROC)GetProcAddress(gESModule, __String(glBindTexture));
			_glBlendColor = (PFNGLBLENDCOLORPROC)GetProcAddress(gESModule, __String(glBlendColor));
			_glBlendEquation = (PFNGLBLENDEQUATIONPROC)GetProcAddress(gESModule, __String(glBlendEquation));
			_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)GetProcAddress(gESModule, __String(glBlendEquationSeparate));
			_glBlendFunc = (PFNGLBLENDFUNCPROC)GetProcAddress(gESModule, __String(glBlendFunc));
			_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)GetProcAddress(gESModule, __String(glBlendFuncSeparate));
			_glBufferData = (PFNGLBUFFERDATAPROC)GetProcAddress(gESModule, __String(glBufferData));
			_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)GetProcAddress(gESModule, __String(glBufferSubData));
			_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)GetProcAddress(gESModule, __String(glCheckFramebufferStatus));
			_glClear = (PFNGLCLEARPROC)GetProcAddress(gESModule, __String(glClear));
			_glClearColor = (PFNGLCLEARCOLORPROC)GetProcAddress(gESModule, __String(glClearColor));
			_glClearDepthf = (PFNGLCLEARDEPTHFPROC)GetProcAddress(gESModule, __String(glClearDepthf));
			_glClearStencil = (PFNGLCLEARSTENCILPROC)GetProcAddress(gESModule, __String(glClearStencil));
			_glColorMask = (PFNGLCOLORMASKPROC)GetProcAddress(gESModule, __String(glColorMask));
			_glCompileShader = (PFNGLCOMPILESHADERPROC)GetProcAddress(gESModule, __String(glCompileShader));
			_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)GetProcAddress(gESModule, __String(glCompressedTexImage2D));
			_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)GetProcAddress(gESModule, __String(glCompressedTexSubImage2D));
			_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)GetProcAddress(gESModule, __String(glCopyTexImage2D));
			_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)GetProcAddress(gESModule, __String(glCopyTexSubImage2D));
			_glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetProcAddress(gESModule, __String(glCreateProgram));
			_glCreateShader = (PFNGLCREATESHADERPROC)GetProcAddress(gESModule, __String(glCreateShader));
			_glCullFace = (PFNGLCULLFACEPROC)GetProcAddress(gESModule, __String(glCullFace));
			_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)GetProcAddress(gESModule, __String(glDeleteBuffers));
			_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)GetProcAddress(gESModule, __String(glDeleteFramebuffers));
			_glDeleteTextures = (PFNGLDELETETEXTURESPROC)GetProcAddress(gESModule, __String(glDeleteTextures));
			_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)GetProcAddress(gESModule, __String(glDeleteProgram));
			_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)GetProcAddress(gESModule, __String(glDeleteRenderbuffers));
			_glDeleteShader = (PFNGLDELETESHADERPROC)GetProcAddress(gESModule, __String(glDeleteShader));
			_glDetachShader = (PFNGLDETACHSHADERPROC)GetProcAddress(gESModule, __String(glDetachShader));
			_glDepthFunc = (PFNGLDEPTHFUNCPROC)GetProcAddress(gESModule, __String(glDepthFunc));
			_glDepthMask = (PFNGLDEPTHMASKPROC)GetProcAddress(gESModule, __String(glDepthMask));
			_glDepthRangef = (PFNGLDEPTHRANGEFPROC)GetProcAddress(gESModule, __String(glDepthRangef));
			_glDisable = (PFNGLDISABLEPROC)GetProcAddress(gESModule, __String(glDisable));
			_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)GetProcAddress(gESModule, __String(glDisableVertexAttribArray));
			_glDrawArrays = (PFNGLDRAWARRAYSPROC)GetProcAddress(gESModule, __String(glDrawArrays));
			_glDrawElements = (PFNGLDRAWELEMENTSPROC)GetProcAddress(gESModule, __String(glDrawElements));
			_glEnable = (PFNGLENABLEPROC)GetProcAddress(gESModule, __String(glEnable));
			_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetProcAddress(gESModule, __String(glEnableVertexAttribArray));
			_glFinish = (PFNGLFINISHPROC)GetProcAddress(gESModule, __String(glFinish));
			_glFlush = (PFNGLFLUSHPROC)GetProcAddress(gESModule, __String(glFlush));
			_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)GetProcAddress(gESModule, __String(glFramebufferRenderbuffer));
			_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)GetProcAddress(gESModule, __String(glFramebufferTexture2D));
			_glFrontFace = (PFNGLFRONTFACEPROC)GetProcAddress(gESModule, __String(glFrontFace));
			_glGenBuffers = (PFNGLGENBUFFERSPROC)GetProcAddress(gESModule, __String(glGenBuffers));
			_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)GetProcAddress(gESModule, __String(glGenerateMipmap));
			_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)GetProcAddress(gESModule, __String(glGenFramebuffers));
			_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)GetProcAddress(gESModule, __String(glGenRenderbuffers));
			_glGenTextures = (PFNGLGENTEXTURESPROC)GetProcAddress(gESModule, __String(glGenTextures));
			_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)GetProcAddress(gESModule, __String(glGetActiveAttrib));
			_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)GetProcAddress(gESModule, __String(glGetActiveUniform));
			_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)GetProcAddress(gESModule, __String(glGetAttachedShaders));
			_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GetProcAddress(gESModule, __String(glGetAttribLocation));
			_glGetBooleanv = (PFNGLGETBOOLEANVPROC)GetProcAddress(gESModule, __String(glGetBooleanv));
			_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)GetProcAddress(gESModule, __String(glGetBufferParameteriv));
			_glGetError = (PFNGLGETERRORPROC)GetProcAddress(gESModule, __String(glGetError));
			_glGetFloatv = (PFNGLGETFLOATVPROC)GetProcAddress(gESModule, __String(glGetFloatv));
			_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)GetProcAddress(gESModule, __String(glGetFramebufferAttachmentParameteriv));
			_glGetIntegerv = (PFNGLGETINTEGERVPROC)GetProcAddress(gESModule, __String(glGetIntegerv));
			_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetProcAddress(gESModule, __String(glGetProgramiv));
			_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)GetProcAddress(gESModule, __String(glGetProgramInfoLog));
			_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)GetProcAddress(gESModule, __String(glGetRenderbufferParameteriv));
			_glGetShaderiv = (PFNGLGETSHADERIVPROC)GetProcAddress(gESModule, __String(glGetShaderiv));
			_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetProcAddress(gESModule, __String(glGetShaderInfoLog));
			_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)GetProcAddress(gESModule, __String(glGetShaderPrecisionFormat));
			_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)GetProcAddress(gESModule, __String(glGetShaderSource));
			_glglGetString = (PFNGLGLGETSTRINGPROC)GetProcAddress(gESModule, __String(glglGetString));
			_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)GetProcAddress(gESModule, __String(glGetTexParameterfv));
			_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)GetProcAddress(gESModule, __String(glGetTexParameteriv));
			_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)GetProcAddress(gESModule, __String(glGetUniformfv));
			_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)GetProcAddress(gESModule, __String(glGetUniformiv));
			_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)GetProcAddress(gESModule, __String(glGetUniformLocation));
			_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)GetProcAddress(gESModule, __String(glGetVertexAttribfv));
			_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)GetProcAddress(gESModule, __String(glGetVertexAttribiv));
			_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)GetProcAddress(gESModule, __String(glGetVertexAttribPointerv));
			_glHint = (PFNGLHINTPROC)GetProcAddress(gESModule, __String(glHint));
			_glIsBuffer = (PFNGLISBUFFERPROC)GetProcAddress(gESModule, __String(glIsBuffer));
			_glIsEnabled = (PFNGLISENABLEDPROC)GetProcAddress(gESModule, __String(glIsEnabled));
			_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)GetProcAddress(gESModule, __String(glIsFramebuffer));
			_glIsProgram = (PFNGLISPROGRAMPROC)GetProcAddress(gESModule, __String(glIsProgram));
			_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)GetProcAddress(gESModule, __String(glIsRenderbuffer));
			_glIsShader = (PFNGLISSHADERPROC)GetProcAddress(gESModule, __String(glIsShader));
			_glIsTexture = (PFNGLISTEXTUREPROC)GetProcAddress(gESModule, __String(glIsTexture));
			_glLineWidth = (PFNGLLINEWIDTHPROC)GetProcAddress(gESModule, __String(glLineWidth));
			_glLinkProgram = (PFNGLLINKPROGRAMPROC)GetProcAddress(gESModule, __String(glLinkProgram));
			_glPixelStorei = (PFNGLPIXELSTOREIPROC)GetProcAddress(gESModule, __String(glPixelStorei));
			_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)GetProcAddress(gESModule, __String(glPolygonOffset));
			_glReadPixels = (PFNGLREADPIXELSPROC)GetProcAddress(gESModule, __String(glReadPixels));
			_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)GetProcAddress(gESModule, __String(glReleaseShaderCompiler));
			_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)GetProcAddress(gESModule, __String(glRenderbufferStorage));
			_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)GetProcAddress(gESModule, __String(glSampleCoverage));
			_glScissor = (PFNGLSCISSORPROC)GetProcAddress(gESModule, __String(glScissor));
			_glShaderBinary = (PFNGLSHADERBINARYPROC)GetProcAddress(gESModule, __String(glShaderBinary));
			_glShaderSource = (PFNGLSHADERSOURCEPROC)GetProcAddress(gESModule, __String(glShaderSource));
			_glStencilFunc = (PFNGLSTENCILFUNCPROC)GetProcAddress(gESModule, __String(glStencilFunc));
			_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)GetProcAddress(gESModule, __String(glStencilFuncSeparate));
			_glStencilMask = (PFNGLSTENCILMASKPROC)GetProcAddress(gESModule, __String(glStencilMask));
			_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)GetProcAddress(gESModule, __String(glStencilMaskSeparate));
			_glStencilOp = (PFNGLSTENCILOPPROC)GetProcAddress(gESModule, __String(glStencilOp));
			_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)GetProcAddress(gESModule, __String(glStencilOpSeparate));
			_glTexImage2D = (PFNGLTEXIMAGE2DPROC)GetProcAddress(gESModule, __String(glTexImage2D));
			_glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetProcAddress(gESModule, __String(glTexParameterf));
			_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)GetProcAddress(gESModule, __String(glTexParameterfv));
			_glTexParameteri = (PFNGLTEXPARAMETERIPROC)GetProcAddress(gESModule, __String(glTexParameteri));
			_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)GetProcAddress(gESModule, __String(glTexParameteriv));
			_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)GetProcAddress(gESModule, __String(glTexSubImage2D));
			_glUniform1f = (PFNGLUNIFORM1FPROC)GetProcAddress(gESModule, __String(glUniform1f));
			_glUniform1fv = (PFNGLUNIFORM1FVPROC)GetProcAddress(gESModule, __String(glUniform1fv));
			_glUniform1i = (PFNGLUNIFORM1IPROC)GetProcAddress(gESModule, __String(glUniform1i));
			_glUniform1iv = (PFNGLUNIFORM1IVPROC)GetProcAddress(gESModule, __String(glUniform1iv));
			_glUniform2f = (PFNGLUNIFORM2FPROC)GetProcAddress(gESModule, __String(glUniform2f));
			_glUniform2fv = (PFNGLUNIFORM2FVPROC)GetProcAddress(gESModule, __String(glUniform2fv));
			_glUniform2i = (PFNGLUNIFORM2IPROC)GetProcAddress(gESModule, __String(glUniform2i));
			_glUniform2iv = (PFNGLUNIFORM2IVPROC)GetProcAddress(gESModule, __String(glUniform2iv));
			_glUniform3f = (PFNGLUNIFORM3FPROC)GetProcAddress(gESModule, __String(glUniform3f));
			_glUniform3fv = (PFNGLUNIFORM3FVPROC)GetProcAddress(gESModule, __String(glUniform3fv));
			_glUniform3i = (PFNGLUNIFORM3IPROC)GetProcAddress(gESModule, __String(glUniform3i));
			_glUniform3iv = (PFNGLUNIFORM3IVPROC)GetProcAddress(gESModule, __String(glUniform3iv));
			_glUniform4f = (PFNGLUNIFORM4FPROC)GetProcAddress(gESModule, __String(glUniform4f));
			_glUniform4fv = (PFNGLUNIFORM4FVPROC)GetProcAddress(gESModule, __String(glUniform4fv));
			_glUniform4i = (PFNGLUNIFORM4IPROC)GetProcAddress(gESModule, __String(glUniform4i));
			_glUniform4iv = (PFNGLUNIFORM4IVPROC)GetProcAddress(gESModule, __String(glUniform4iv));
			_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)GetProcAddress(gESModule, __String(glUniformMatrix2fv));
			_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)GetProcAddress(gESModule, __String(glUniformMatrix3fv));
			_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)GetProcAddress(gESModule, __String(glUniformMatrix4fv));
			_glUseProgram = (PFNGLUSEPROGRAMPROC)GetProcAddress(gESModule, __String(glUseProgram));
			_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GetProcAddress(gESModule, __String(glValidateProgram));
			_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)GetProcAddress(gESModule, __String(glVertexAttrib1f));
			_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)GetProcAddress(gESModule, __String(glVertexAttrib1fv));
			_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)GetProcAddress(gESModule, __String(glVertexAttrib2f));
			_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)GetProcAddress(gESModule, __String(glVertexAttrib2fv));
			_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)GetProcAddress(gESModule, __String(glVertexAttrib3f));
			_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)GetProcAddress(gESModule, __String(glVertexAttrib3fv));
			_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)GetProcAddress(gESModule, __String(glVertexAttrib4f));
			_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)GetProcAddress(gESModule, __String(glVertexAttrib4fv));
			_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)GetProcAddress(gESModule, __String(glVertexAttribPointer));
			_glViewport = (PFNGLVIEWPORTPROC)GetProcAddress(gESModule, __String(glViewport));
			_glMapBufferOES = (PFNGLMAPBUFFEROESPROC)GetProcAddress(gESModule, __String(glMapBufferOES));
			_glUnMapBufferOES = (PFNGLUNMAPBUFFEROESPROC)GetProcAddress(gESModule, __String(glUnmapBufferOES));
#endif
		}

		void ActiveTexture(GLenum texture)
		{
#ifdef WIN32
			_glActiveTexture(texture);
#else
			glActiveTexture(texture);
#endif
		}

		void AttachShader(GLuint program, GLuint shader)
		{
#ifdef WIN32
			_glAttachShader(program, shader);
#else
			glAttachShader(program, shader);
#endif
		}

		void BindAttribLocation(GLuint program, GLuint index, const char* name)
		{
#ifdef WIN32
			_glBindAttribLocation(program, index, name);
#else
			glBindAttribLocation(program, index, name);
#endif
		}

		void BindBuffer(GLenum target, GLuint buffer)
		{
#ifdef WIN32
			_glBindBuffer(target, buffer);
#else
			glBindBuffer(target, buffer);
#endif
		}

		void BindFramebuffer(GLenum target, GLuint framebuffer)
		{
#ifdef WIN32
			_glBindFramebuffer(target, framebuffer);
#else
			glBindFramebuffer(target, framebuffer);
#endif
		}

		void BindRenderbuffer(GLenum target, GLuint renderbuffer)
		{
#ifdef WIN32
			_glBindRenderbuffer(target, renderbuffer);
#else
			glBindRenderbuffer(target, renderbuffer);
#endif
		}

		void BindTexture(GLenum target, GLuint texture)
		{
#ifdef WIN32
			_glBindTexture(target, texture);
#else
			glBindTexture(target, texture);
#endif
		}

		void BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
		{
#ifdef WIN32
			_glBlendColor(red, green, blue, alpha);
#else
			glBlendColor(red, green, blue, alpha);
#endif
		}

		void BlendEquation(GLenum mode)
		{
#ifdef WIN32
			_glBlendEquation(mode);
#else
			glBlendEquation(mode);
#endif
		}

		void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
		{
#ifdef WIN32
			_glBlendEquationSeparate(modeRGB, modeAlpha);
#else
			glBlendEquationSeparate(modeRGB, modeAlpha);
#endif
		}

		void BlendFunc(GLenum sfactor, GLenum dfactor)
		{
#ifdef WIN32
			_glBlendFunc(sfactor, dfactor);
#else
			glBlendFunc(sfactor, dfactor);
#endif
		}

		void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
		{
#ifdef WIN32
			_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
#else
			glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
#endif
		}

		void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
		{
#ifdef WIN32
			_glBufferData(target, size, data, usage);
#else
			glBufferData(target, size, data, usage);
#endif
		}

		void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
		{
#ifdef WIN32
			_glBufferSubData(target, offset, size, data);
#else
			glBufferSubData(target, offset, size, data);
#endif
		}

		GLenum CheckFramebufferStatus(GLenum target)
		{
#ifdef WIN32
			return _glCheckFramebufferStatus(target);
#else
			return glCheckFramebufferStatus(target);
#endif
		}

		void Clear(GLbitfield mask)
		{
#ifdef WIN32
			_glClear(mask);
#else
			glClear(mask);
#endif
		}

		void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
		{
#ifdef WIN32
			_glClearColor(red, green, blue, alpha);
#else
			glClearColor(red, green, blue, alpha);
#endif
		}

		void ClearDepthf(GLclampf depth)
		{
#ifdef WIN32
			_glClearDepthf(depth);
#else
			glClearDepthf(depth);
#endif
		}

		void ClearStencil(GLint s)
		{
#ifdef WIN32
			_glClearStencil(s);
#else
			glClearStencil(s);
#endif
		}

		void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
		{
#ifdef WIN32
			_glColorMask(red, green, blue, alpha);
#else
			glColorMask(red, green, blue, alpha);
#endif
		}

		void CompileShader(GLuint shader)
		{
#ifdef WIN32
			_glCompileShader(shader);
#else
			glCompileShader(shader);
#endif
		}

		void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
		{
#ifdef WIN32
			_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
#else
			glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
#endif
		}

		void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
		{
#ifdef WIN32
			_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
#else
			glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
#endif
		}

		void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
		{
#ifdef WIN32
			_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
#else
			glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
#endif
		}

		void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
		{
#ifdef WIN32
			_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
#else
			glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
#endif
		}

		GLuint CreateProgram()
		{
#ifdef WIN32
			return _glCreateProgram();
#else
			return glCreateProgram();
#endif
		}

		GLuint CreateShader(GLenum type)
		{
#ifdef WIN32
			return _glCreateShader(type);
#else
			return glCreateShader(type);
#endif
		}

		void CullFace(GLenum mode)
		{
#ifdef WIN32
			_glCullFace(mode);
#else
			glCullFace(mode);
#endif
		}

		void DeleteBuffers(GLsizei n, const GLuint* buffers)
		{
#ifdef WIN32
			_glDeleteBuffers(n, buffers);
#else
			glDeleteBuffers(n, buffers);
#endif
		}

		void DeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
		{
#ifdef WIN32
			_glDeleteFramebuffers(n, framebuffers);
#else
			glDeleteFramebuffers(n, framebuffers);
#endif
		}

		void DeleteTextures(GLsizei n, const GLuint* textures)
		{
#ifdef WIN32
			_glDeleteTextures(n, textures);
#else
			glDeleteTextures(n, textures);
#endif
		}

		void DeleteProgram(GLuint program)
		{
#ifdef WIN32
			_glDeleteProgram(program);
#else
			glDeleteProgram(program);
#endif
		}

		void DeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
		{
#ifdef WIN32
			_glDeleteRenderbuffers(n, renderbuffers);
#else
			glDeleteRenderbuffers(n, renderbuffers);
#endif
		}

		void DeleteShader(GLuint shader)
		{
#ifdef WIN32
			_glDeleteShader(shader);
#else
			glDeleteShader(shader);
#endif
		}

		void DetachShader(GLuint program, GLuint shader)
		{
#ifdef WIN32
			_glDetachShader(program, shader);
#else
			glDetachShader(program, shader);
#endif
		}

		void DepthFunc(GLenum func)
		{
#ifdef WIN32
			_glDepthFunc(func);
#else
			glDepthFunc(func);
#endif
		}

		void DepthMask(GLboolean flag)
		{
#ifdef WIN32
			_glDepthMask(flag);
#else
			glDepthMask(flag);
#endif
		}

		void DepthRangef(GLclampf zNear, GLclampf zFar)
		{
#ifdef WIN32
			_glDepthRangef(zNear, zFar);
#else
			glDepthRangef(zNear, zFar);
#endif
		}

		void Disable(GLenum cap)
		{
#ifdef WIN32
			_glDisable(cap);
#else
			glDisable(cap);
#endif
		}

		void DisableVertexAttribArray(GLuint index)
		{
#ifdef WIN32
			_glDisableVertexAttribArray(index);
#else
			glDisableVertexAttribArray(index);
#endif
		}

		void DrawArrays(GLenum mode, GLint first, GLsizei count)
		{
#ifdef WIN32
			_glDrawArrays(mode, first, count);
#else
			glDrawArrays(mode, first, count);
#endif
		}

		void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
		{
#ifdef WIN32
			_glDrawElements(mode, count, type, indices);
#else
			glDrawElements(mode, count, type, indices);
#endif
		}

		void Enable(GLenum cap)
		{
#ifdef WIN32
			_glEnable(cap);
#else
			glEnable(cap);
#endif
		}

		void EnableVertexAttribArray(GLuint index)
		{
#ifdef WIN32
			_glEnableVertexAttribArray(index);
#else
			glEnableVertexAttribArray(index);
#endif
		}

		void Finish()
		{
#ifdef WIN32
			_glFinish();
#else
			glFinish();
#endif
		}

		void Flush()
		{
#ifdef WIN32
			_glFlush();
#else
			glFlush();
#endif
		}

		void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
		{
#ifdef WIN32
			_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
#else
			glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
#endif
		}

		void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
		{
#ifdef WIN32
			_glFramebufferTexture2D(target, attachment, textarget, texture, level);
#else
			glFramebufferTexture2D(target, attachment, textarget, texture, level);
#endif
		}

		void FrontFace(GLenum mode)
		{
#ifdef WIN32
			_glFrontFace(mode);
#else
			glFrontFace(mode);
#endif
		}

		void GenBuffers(GLsizei n, GLuint* buffers)
		{
#ifdef WIN32
			_glGenBuffers(n, buffers);
#else
			glGenBuffers(n, buffers);
#endif
		}

		void GenerateMipmap(GLenum target)
		{
#ifdef WIN32
			_glGenerateMipmap(target);
#else
			glGenerateMipmap(target);
#endif
		}

		void GenFramebuffers(GLsizei n, GLuint* framebuffers)
		{
#ifdef WIN32
			_glGenFramebuffers(n, framebuffers);
#else
			glGenFramebuffers(n, framebuffers);
#endif
		}

		void GenRenderbuffers(GLsizei n, GLuint* renderbuffers)
		{
#ifdef WIN32
			_glGenRenderbuffers(n, renderbuffers);
#else
			glGenRenderbuffers(n, renderbuffers);
#endif
		}

		void GenTextures(GLsizei n, GLuint* textures)
		{
#ifdef WIN32
			_glGenTextures(n, textures);
#else
			glGenTextures(n, textures);
#endif
		}

		void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
		{
#ifdef WIN32
			_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
#else
			glGetActiveAttrib(program, index, bufsize, length, size, type, name);
#endif
		}

		void GetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
		{
#ifdef WIN32
			_glGetActiveUniform(program, index, bufsize, length, size, type, name);
#else
			glGetActiveUniform(program, index, bufsize, length, size, type, name);
#endif
		}

		void GetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
		{
#ifdef WIN32
			_glGetAttachedShaders(program, maxcount, count, shaders);
#else
			glGetAttachedShaders(program, maxcount, count, shaders);
#endif
		}

		int  GetAttribLocation(GLuint program, const char* name)
		{
#ifdef WIN32
			return _glGetAttribLocation(program, name);
#else
			return glGetAttribLocation(program, name);
#endif
		}

		void GetBooleanv(GLenum pname, GLboolean* params)
		{
#ifdef WIN32
			_glGetBooleanv(pname, params);
#else
			glGetBooleanv(pname, params);
#endif
		}

		void GetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetBufferParameteriv(target, pname, params);
#else
			glGetBufferParameteriv(target, pname, params);
#endif
		}

		GLenum GetError()
		{
#ifdef WIN32
			return _glGetError();
#else
			return glGetError();
#endif
		}

		void GetFloatv(GLenum pname, GLfloat* params)
		{
#ifdef WIN32
			_glGetFloatv(pname, params);
#else
			glGetFloatv(pname, params);
#endif
		}

		void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
#else
			glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
#endif
		}

		void GetIntegerv(GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetIntegerv(pname, params);
#else
			glGetIntegerv(pname, params);
#endif
		}

		void GetProgramiv(GLuint program, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetProgramiv(program, pname, params);
#else
			glGetProgramiv(program, pname, params);
#endif
		}

		void GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
		{
#ifdef WIN32
			_glGetProgramInfoLog(program, bufsize, length, infolog);
#else
			glGetProgramInfoLog(program, bufsize, length, infolog);
#endif
		}

		void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetRenderbufferParameteriv(target, pname, params);
#else
			glGetRenderbufferParameteriv(target, pname, params);
#endif
		}

		void GetShaderiv(GLuint shader, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetShaderiv(shader, pname, params);
#else
			glGetShaderiv(shader, pname, params);
#endif
		}

		void GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
		{
#ifdef WIN32
			_glGetShaderInfoLog(shader, bufsize, length, infolog);
#else
			glGetShaderInfoLog(shader, bufsize, length, infolog);
#endif
		}

		void GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
		{
#ifdef WIN32
			_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
#else
			glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
#endif
		}

		void GetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
		{
#ifdef WIN32
			_glGetShaderSource(shader, bufsize, length, source);
#else
			glGetShaderSource(shader, bufsize, length, source);
#endif
		}

		const GLubyte* glGetString(GLenum name)
		{
#ifdef WIN32
			return _glglGetString(name);
#else
			return glglGetString(name);
#endif
		}

		void GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
		{
#ifdef WIN32
			_glGetTexParameterfv(target, pname, params);
#else
			glGetTexParameterfv(target, pname, params);
#endif
		}

		void GetTexParameteriv(GLenum target, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetTexParameteriv(target, pname, params);
#else
			glGetTexParameteriv(target, pname, params);
#endif
		}

		void GetUniformfv(GLuint program, GLint location, GLfloat* params)
		{
#ifdef WIN32
			_glGetUniformfv(program, location, params);
#else
			glGetUniformfv(program, location, params);
#endif
		}

		void GetUniformiv(GLuint program, GLint location, GLint* params)
		{
#ifdef WIN32
			_glGetUniformiv(program, location, params);
#else
			glGetUniformiv(program, location, params);
#endif
		}

		int  GetUniformLocation(GLuint program, const char* name)
		{
#ifdef WIN32
			return _glGetUniformLocation(program, name);
#else
			return glGetUniformLocation(program, name);
#endif
		}

		void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
		{
#ifdef WIN32
			_glGetVertexAttribfv(index, pname, params);
#else
			glGetVertexAttribfv(index, pname, params);
#endif
		}

		void GetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
		{
#ifdef WIN32
			_glGetVertexAttribiv(index, pname, params);
#else
			glGetVertexAttribiv(index, pname, params);
#endif
		}

		void GetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
		{
#ifdef WIN32
			_glGetVertexAttribPointerv(index, pname, pointer);
#else
			glGetVertexAttribPointerv(index, pname, pointer);
#endif
		}

		void Hint(GLenum target, GLenum mode)
		{
#ifdef WIN32
			_glHint(target, mode);
#else
			glHint(target, mode);
#endif
		}

		GLboolean IsBuffer(GLuint buffer)
		{
#ifdef WIN32
			return _glIsBuffer(buffer);
#else
			return glIsBuffer(buffer);
#endif
		}

		GLboolean IsEnabled(GLenum cap)
		{
#ifdef WIN32
			return _glIsEnabled(cap);
#else
			return glIsEnabled(cap);
#endif
		}

		GLboolean IsFramebuffer(GLuint framebuffer)
		{
#ifdef WIN32
			return _glIsFramebuffer(framebuffer);
#else
			return glIsFramebuffer(framebuffer);
#endif
		}

		GLboolean IsProgram(GLuint program)
		{
#ifdef WIN32
			return _glIsProgram(program);
#else
			return glIsProgram(program);
#endif
		}

		GLboolean IsRenderbuffer(GLuint renderbuffer)
		{
#ifdef WIN32
			return _glIsRenderbuffer(renderbuffer);
#else
			return glIsRenderbuffer(renderbuffer);
#endif
		}

		GLboolean IsShader(GLuint shader)
		{
#ifdef WIN32
			return _glIsShader(shader);
#else
			return glIsShader(shader);
#endif
		}

		GLboolean IsTexture(GLuint texture)
		{
#ifdef WIN32
			return _glIsTexture(texture);
#else
			return glIsTexture(texture);
#endif
		}

		void LineWidth(GLfloat width)
		{
#ifdef WIN32
			_glLineWidth(width);
#else
			glLineWidth(width);
#endif
		}

		void LinkProgram(GLuint program)
		{
#ifdef WIN32
			_glLinkProgram(program);
#else
			glLinkProgram(program);
#endif
		}

		void PixelStorei(GLenum pname, GLint param)
		{
#ifdef WIN32
			_glPixelStorei(pname, param);
#else
			glPixelStorei(pname, param);
#endif
		}

		void PolygonOffset(GLfloat factor, GLfloat units)
		{
#ifdef WIN32
			_glPolygonOffset(factor, units);
#else
			glPolygonOffset(factor, units);
#endif
		}

		void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
		{
#ifdef WIN32
			_glReadPixels(x, y, width, height, format, type, pixels);
#else
			glReadPixels(x, y, width, height, format, type, pixels);
#endif
		}

		void ReleaseShaderCompiler()
		{
#ifdef WIN32
			_glReleaseShaderCompiler();
#else
			glReleaseShaderCompiler();
#endif
		}

		void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
		{
#ifdef WIN32
			_glRenderbufferStorage(target, internalformat, width, height);
#else
			glRenderbufferStorage(target, internalformat, width, height);
#endif
		}

		void SampleCoverage(GLclampf value, GLboolean invert)
		{
#ifdef WIN32
			_glSampleCoverage(value, invert);
#else
			glSampleCoverage(value, invert);
#endif
		}

		void Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
		{
#ifdef WIN32
			_glScissor(x, y, width, height);
#else
			glScissor(x, y, width, height);
#endif
		}

		void ShaderBinary(GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length)
		{
#ifdef WIN32
			_glShaderBinary(n, shaders, binaryformat, binary, length);
#else
			glShaderBinary(n, shaders, binaryformat, binary, length);
#endif
		}

		void ShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
		{
#ifdef WIN32
			_glShaderSource(shader, count, string, length);
#else
			glShaderSource(shader, count, string, length);
#endif
		}

		void StencilFunc(GLenum func, GLint ref, GLuint mask)
		{
#ifdef WIN32
			_glStencilFunc(func, ref, mask);
#else
			glStencilFunc(func, ref, mask);
#endif
		}

		void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
		{
#ifdef WIN32
			_glStencilFuncSeparate(face, func, ref, mask);
#else
			glStencilFuncSeparate(face, func, ref, mask);
#endif
		}

		void StencilMask(GLuint mask)
		{
#ifdef WIN32
			_glStencilMask(mask);
#else
			glStencilMask(mask);
#endif
		}

		void StencilMaskSeparate(GLenum face, GLuint mask)
		{
#ifdef WIN32
			_glStencilMaskSeparate(face, mask);
#else
			glStencilMaskSeparate(face, mask);
#endif
		}

		void StencilOp(GLenum fail, GLenum zfail, GLenum zpass)
		{
#ifdef WIN32
			_glStencilOp(fail, zfail, zpass);
#else
			glStencilOp(fail, zfail, zpass);
#endif
		}

		void StencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
		{
#ifdef WIN32
			_glStencilOpSeparate(face, fail, zfail, zpass);
#else
			glStencilOpSeparate(face, fail, zfail, zpass);
#endif
		}

		void TexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
		{
#ifdef WIN32
			_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
#else
			glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
#endif
		}

		void TexParameterf(GLenum target, GLenum pname, GLfloat param)
		{
#ifdef WIN32
			_glTexParameterf(target, pname, param);
#else
			glTexParameterf(target, pname, param);
#endif
		}

		void TexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
		{
#ifdef WIN32
			_glTexParameterfv(target, pname, params);
#else
			glTexParameterfv(target, pname, params);
#endif
		}

		void TexParameteri(GLenum target, GLenum pname, GLint param)
		{
#ifdef WIN32
			_glTexParameteri(target, pname, param);
#else
			glTexParameteri(target, pname, param);
#endif
		}

		void TexParameteriv(GLenum target, GLenum pname, const GLint* params)
		{
#ifdef WIN32
			_glTexParameteriv(target, pname, params);
#else
			glTexParameteriv(target, pname, params);
#endif
		}

		void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
		{
#ifdef WIN32
			_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
#else
			glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
#endif
		}

		void Uniform1f(GLint location, GLfloat x)
		{
#ifdef WIN32
			_glUniform1f(location, x);
#else
			glUniform1f(location, x);
#endif
		}

		void Uniform1fv(GLint location, GLsizei count, const GLfloat* v)
		{
#ifdef WIN32
			_glUniform1fv(location, count, v);
#else
			glUniform1fv(location, count, v);
#endif
		}

		void Uniform1i(GLint location, GLint x)
		{
#ifdef WIN32
			_glUniform1i(location, x);
#else
			glUniform1i(location, x);
#endif
		}

		void Uniform1iv(GLint location, GLsizei count, const GLint* v)
		{
#ifdef WIN32
			_glUniform1iv(location, count, v);
#else
			glUniform1iv(location, count, v);
#endif
		}

		void Uniform2f(GLint location, GLfloat x, GLfloat y)
		{
#ifdef WIN32
			_glUniform2f(location, x, y);
#else
			glUniform2f(location, x, y);
#endif
		}

		void Uniform2fv(GLint location, GLsizei count, const GLfloat* v)
		{
#ifdef WIN32
			_glUniform2fv(location, count, v);
#else
			glUniform2fv(location, count, v);
#endif
		}

		void Uniform2i(GLint location, GLint x, GLint y)
		{
#ifdef WIN32
			_glUniform2i(location, x, y);
#else
			glUniform2i(location, x, y);
#endif
		}

		void Uniform2iv(GLint location, GLsizei count, const GLint* v)
		{
#ifdef WIN32
			_glUniform2iv(location, count, v);
#else
			glUniform2iv(location, count, v);
#endif
		}

		void Uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
		{
#ifdef WIN32
			_glUniform3f(location, x, y, z);
#else
			glUniform3f(location, x, y, z);
#endif
		}

		void Uniform3fv(GLint location, GLsizei count, const GLfloat* v)
		{
#ifdef WIN32
			_glUniform3fv(location, count, v);
#else
			glUniform3fv(location, count, v);
#endif
		}

		void Uniform3i(GLint location, GLint x, GLint y, GLint z)
		{
#ifdef WIN32
			_glUniform3i(location, x, y, z);
#else
			glUniform3i(location, x, y, z);
#endif
		}

		void Uniform3iv(GLint location, GLsizei count, const GLint* v)
		{
#ifdef WIN32
			_glUniform3iv(location, count, v);
#else
			glUniform3iv(location, count, v);
#endif
		}

		void Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
#ifdef WIN32
			_glUniform4f(location, x, y, z, w);
#else
			glUniform4f(location, x, y, z, w);
#endif
		}

		void Uniform4fv(GLint location, GLsizei count, const GLfloat* v)
		{
#ifdef WIN32
			_glUniform4fv(location, count, v);
#else
			glUniform4fv(location, count, v);
#endif
		}

		void Uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
		{
#ifdef WIN32
			_glUniform4i(location, x, y, z, w);
#else
			glUniform4i(location, x, y, z, w);
#endif
		}

		void Uniform4iv(GLint location, GLsizei count, const GLint* v)
		{
#ifdef WIN32
			_glUniform4iv(location, count, v);
#else
			glUniform4iv(location, count, v);
#endif
		}

		void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
		{
#ifdef WIN32
			_glUniformMatrix2fv(location, count, transpose, value);
#else
			glUniformMatrix2fv(location, count, transpose, value);
#endif
		}

		void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
		{
#ifdef WIN32
			_glUniformMatrix3fv(location, count, transpose, value);
#else
			glUniformMatrix3fv(location, count, transpose, value);
#endif
		}

		void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
		{
#ifdef WIN32
			_glUniformMatrix4fv(location, count, transpose, value);
#else
			glUniformMatrix4fv(location, count, transpose, value);
#endif
		}

		void UseProgram(GLuint program)
		{
#ifdef WIN32
			_glUseProgram(program);
#else
			glUseProgram(program);
#endif
		}

		void ValidateProgram(GLuint program)
		{
#ifdef WIN32
			_glValidateProgram(program);
#else
			glValidateProgram(program);
#endif
		}

		void VertexAttrib1f(GLuint indx, GLfloat x)
		{
#ifdef WIN32
			_glVertexAttrib1f(indx, x);
#else
			glVertexAttrib1f(indx, x);
#endif
		}

		void VertexAttrib1fv(GLuint indx, const GLfloat* values)
		{
#ifdef WIN32
			_glVertexAttrib1fv(indx, values);
#else
			glVertexAttrib1fv(indx, values);
#endif
		}

		void VertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
		{
#ifdef WIN32
			_glVertexAttrib2f(indx, x, y);
#else
			glVertexAttrib2f(indx, x, y);
#endif
		}

		void VertexAttrib2fv(GLuint indx, const GLfloat* values)
		{
#ifdef WIN32
			_glVertexAttrib2fv(indx, values);
#else
			glVertexAttrib2fv(indx, values);
#endif
		}

		void VertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
		{
#ifdef WIN32
			_glVertexAttrib3f(indx, x, y, z);
#else
			glVertexAttrib3f(indx, x, y, z);
#endif
		}

		void VertexAttrib3fv(GLuint indx, const GLfloat* values)
		{
#ifdef WIN32
			_glVertexAttrib3fv(indx, values);
#else
			glVertexAttrib3fv(indx, values);
#endif
		}

		void VertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
#ifdef WIN32
			_glVertexAttrib4f(indx, x, y, z, w);
#else
			glVertexAttrib4f(indx, x, y, z, w);
#endif
		}

		void VertexAttrib4fv(GLuint indx, const GLfloat* values)
		{
#ifdef WIN32
			_glVertexAttrib4fv(indx, values);
#else
			glVertexAttrib4fv(indx, values);
#endif
		}

		void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
		{
#ifdef WIN32
			_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
#else
			glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
#endif
		}

		void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
		{
#ifdef WIN32
			_glViewport(x, y, width, height);
#else
			glViewport(x, y, width, height);
#endif
		}

		void* MapBufferOES(GLenum target, GLenum access)
		{
#ifdef WIN32
			return _glMapBufferOES(target, access);
#else
			return glMapBufferOES(target, access);
#endif
		}

		GLboolean UnMapBufferOES(GLenum target)
		{
#ifdef WIN32
			return _glUnMapBufferOES(target);
#else
			return glUnmapBufferOES(target);
#endif
		}


	}
}