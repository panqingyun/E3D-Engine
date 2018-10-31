#include "E3DES2Loader.h"
#include <assert.h>

namespace E3DEngine
{
	namespace ES2
	{
#define __String(x) #x

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

		void LoadESLibrary()
		{
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

		}

		void ActiveTexture(GLenum texture)
		{
			_glActiveTexture(texture);
		}

		void AttachShader(GLuint program, GLuint shader)
		{
			_glAttachShader(program, shader);
		}

		void BindAttribLocation(GLuint program, GLuint index, const char* name)
		{
			_glBindAttribLocation(program, index, name);
		}

		void BindBuffer(GLenum target, GLuint buffer)
		{
			_glBindBuffer(target, buffer);
		}

		void BindFramebuffer(GLenum target, GLuint framebuffer)
		{
			_glBindFramebuffer(target, framebuffer);
		}

		void BindRenderbuffer(GLenum target, GLuint renderbuffer)
		{
			_glBindRenderbuffer(target, renderbuffer);
		}

		void BindTexture(GLenum target, GLuint texture)
		{
			_glBindTexture(target, texture);
		}

		void BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
		{
			_glBlendColor(red, green, blue, alpha);
		}

		void BlendEquation(GLenum mode)
		{
			_glBlendEquation(mode);
		}

		void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
		{
			_glBlendEquationSeparate(modeRGB, modeAlpha);
		}

		void BlendFunc(GLenum sfactor, GLenum dfactor)
		{
			_glBlendFunc(sfactor, dfactor);
		}

		void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
		{
			_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
		}

		void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
		{
			_glBufferData(target, size, data, usage);
		}

		void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
		{
			_glBufferSubData(target, offset, size, data);
		}

		GLenum CheckFramebufferStatus(GLenum target)
		{
			return _glCheckFramebufferStatus(target);
		}

		void Clear(GLbitfield mask)
		{
			_glClear(mask);
		}

		void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
		{
			_glClearColor(red, green, blue, alpha);
		}

		void ClearDepthf(GLclampf depth)
		{
			_glClearDepthf(depth);
		}

		void ClearStencil(GLint s)
		{
			_glClearStencil(s);
		}

		void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
		{
			_glColorMask(red, green, blue, alpha);
		}

		void CompileShader(GLuint shader)
		{
			_glCompileShader(shader);
		}

		void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
		{
			_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
		}

		void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
		{
			_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
		}

		void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
		{
			_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
		}

		void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
		{
			_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
		}

		GLuint CreateProgram()
		{
			return _glCreateProgram();
		}

		GLuint CreateShader(GLenum type)
		{
			return _glCreateShader(type);
		}

		void CullFace(GLenum mode)
		{
			_glCullFace(mode);
		}

		void DeleteBuffers(GLsizei n, const GLuint* buffers)
		{
			_glDeleteBuffers(n, buffers);
		}

		void DeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
		{
			_glDeleteFramebuffers(n, framebuffers);
		}

		void DeleteTextures(GLsizei n, const GLuint* textures)
		{
			_glDeleteTextures(n, textures);
		}

		void DeleteProgram(GLuint program)
		{
			_glDeleteProgram(program);
		}

		void DeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
		{
			_glDeleteRenderbuffers(n, renderbuffers);
		}

		void DeleteShader(GLuint shader)
		{
			_glDeleteShader(shader);
		}

		void DetachShader(GLuint program, GLuint shader)
		{
			_glDetachShader(program, shader);
		}

		void DepthFunc(GLenum func)
		{
			_glDepthFunc(func);
		}

		void DepthMask(GLboolean flag)
		{
			_glDepthMask(flag);
		}

		void DepthRangef(GLclampf zNear, GLclampf zFar)
		{
			_glDepthRangef(zNear, zFar);
		}

		void Disable(GLenum cap)
		{
			_glDisable(cap);
		}

		void DisableVertexAttribArray(GLuint index)
		{
			_glDisableVertexAttribArray(index);
		}

		void DrawArrays(GLenum mode, GLint first, GLsizei count)
		{
			_glDrawArrays(mode, first, count);
		}

		void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
		{
			_glDrawElements(mode, count, type, indices);
		}

		void Enable(GLenum cap)
		{
			_glEnable(cap);
		}

		void EnableVertexAttribArray(GLuint index)
		{
			_glEnableVertexAttribArray(index);
		}

		void Finish()
		{
			_glFinish();
		}

		void Flush()
		{
			_glFlush();
		}

		void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
		{
			_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
		}

		void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
		{
			_glFramebufferTexture2D(target, attachment, textarget, texture, level);
		}

		void FrontFace(GLenum mode)
		{
			_glFrontFace(mode);
		}

		void GenBuffers(GLsizei n, GLuint* buffers)
		{
			_glGenBuffers(n, buffers);
		}

		void GenerateMipmap(GLenum target)
		{
			_glGenerateMipmap(target);
		}

		void GenFramebuffers(GLsizei n, GLuint* framebuffers)
		{
			_glGenFramebuffers(n, framebuffers);
		}

		void GenRenderbuffers(GLsizei n, GLuint* renderbuffers)
		{
			_glGenRenderbuffers(n, renderbuffers);
		}

		void GenTextures(GLsizei n, GLuint* textures)
		{
			_glGenTextures(n, textures);
		}

		void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
		{
			_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
		}

		void GetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
		{
			_glGetActiveUniform(program, index, bufsize, length, size, type, name);
		}

		void GetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
		{
			_glGetAttachedShaders(program, maxcount, count, shaders);
		}

		int  GetAttribLocation(GLuint program, const char* name)
		{
			return _glGetAttribLocation(program, name);
		}

		void GetBooleanv(GLenum pname, GLboolean* params)
		{
			_glGetBooleanv(pname, params);
		}

		void GetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
		{
			_glGetBufferParameteriv(target, pname, params);
		}

		GLenum GetError()
		{
			return _glGetError();
		}

		void GetFloatv(GLenum pname, GLfloat* params)
		{
			_glGetFloatv(pname, params);
		}

		void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
		{
			_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
		}

		void GetIntegerv(GLenum pname, GLint* params)
		{
			_glGetIntegerv(pname, params);
		}

		void GetProgramiv(GLuint program, GLenum pname, GLint* params)
		{
			_glGetProgramiv(program, pname, params);
		}

		void GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
		{
			_glGetProgramInfoLog(program, bufsize, length, infolog);
		}

		void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
		{
			_glGetRenderbufferParameteriv(target, pname, params);
		}

		void GetShaderiv(GLuint shader, GLenum pname, GLint* params)
		{
			_glGetShaderiv(shader, pname, params);
		}

		void GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
		{
			_glGetShaderInfoLog(shader, bufsize, length, infolog);
		}

		void GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
		{
			_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
		}

		void GetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
		{
			_glGetShaderSource(shader, bufsize, length, source);
		}

		const GLubyte* glGetString(GLenum name)
		{
			return _glglGetString(name);
		}

		void GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
		{
			_glGetTexParameterfv(target, pname, params);
		}

		void GetTexParameteriv(GLenum target, GLenum pname, GLint* params)
		{
			_glGetTexParameteriv(target, pname, params);
		}

		void GetUniformfv(GLuint program, GLint location, GLfloat* params)
		{
			_glGetUniformfv(program, location, params);
		}

		void GetUniformiv(GLuint program, GLint location, GLint* params)
		{
			_glGetUniformiv(program, location, params);
		}

		int  GetUniformLocation(GLuint program, const char* name)
		{
			return _glGetUniformLocation(program, name);
		}

		void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
		{
			_glGetVertexAttribfv(index, pname, params);
		}

		void GetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
		{
			_glGetVertexAttribiv(index, pname, params);
		}

		void GetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
		{
			_glGetVertexAttribPointerv(index, pname, pointer);
		}

		void Hint(GLenum target, GLenum mode)
		{
			_glHint(target, mode);
		}

		GLboolean IsBuffer(GLuint buffer)
		{
			return _glIsBuffer(buffer);
		}

		GLboolean IsEnabled(GLenum cap)
		{
			return _glIsEnabled(cap);
		}

		GLboolean IsFramebuffer(GLuint framebuffer)
		{
			return _glIsFramebuffer(framebuffer);
		}

		GLboolean IsProgram(GLuint program)
		{
			return _glIsProgram(program);
		}

		GLboolean IsRenderbuffer(GLuint renderbuffer)
		{
			return _glIsRenderbuffer(renderbuffer);
		}

		GLboolean IsShader(GLuint shader)
		{
			return _glIsShader(shader);
		}

		GLboolean IsTexture(GLuint texture)
		{
			return _glIsTexture(texture);
		}

		void LineWidth(GLfloat width)
		{
			_glLineWidth(width);
		}

		void LinkProgram(GLuint program)
		{
			_glLinkProgram(program);
		}

		void PixelStorei(GLenum pname, GLint param)
		{
			_glPixelStorei(pname, param);
		}

		void PolygonOffset(GLfloat factor, GLfloat units)
		{
			_glPolygonOffset(factor, units);
		}

		void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
		{
			_glReadPixels(x, y, width, height, format, type, pixels);
		}

		void ReleaseShaderCompiler()
		{
			_glReleaseShaderCompiler();
		}

		void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
		{
			_glRenderbufferStorage(target, internalformat, width, height);
		}

		void SampleCoverage(GLclampf value, GLboolean invert)
		{
			_glSampleCoverage(value, invert);
		}

		void Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			_glScissor(x, y, width, height);
		}

		void ShaderBinary(GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length)
		{
			_glShaderBinary(n, shaders, binaryformat, binary, length);
		}

		void ShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
		{
			_glShaderSource(shader, count, string, length);
		}

		void StencilFunc(GLenum func, GLint ref, GLuint mask)
		{
			_glStencilFunc(func, ref, mask);
		}

		void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
		{
			_glStencilFuncSeparate(face, func, ref, mask);
		}

		void StencilMask(GLuint mask)
		{
			_glStencilMask(mask);
		}

		void StencilMaskSeparate(GLenum face, GLuint mask)
		{
			_glStencilMaskSeparate(face, mask);
		}

		void StencilOp(GLenum fail, GLenum zfail, GLenum zpass)
		{
			_glStencilOp(fail, zfail, zpass);
		}

		void StencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
		{
			_glStencilOpSeparate(face, fail, zfail, zpass);
		}

		void TexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
		{
			_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		}

		void TexParameterf(GLenum target, GLenum pname, GLfloat param)
		{
			_glTexParameterf(target, pname, param);
		}

		void TexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
		{
			_glTexParameterfv(target, pname, params);
		}

		void TexParameteri(GLenum target, GLenum pname, GLint param)
		{
			_glTexParameteri(target, pname, param);
		}

		void TexParameteriv(GLenum target, GLenum pname, const GLint* params)
		{
			_glTexParameteriv(target, pname, params);
		}

		void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
		{
			_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
		}

		void Uniform1f(GLint location, GLfloat x)
		{
			_glUniform1f(location, x);
		}

		void Uniform1fv(GLint location, GLsizei count, const GLfloat* v)
		{
			_glUniform1fv(location, count, v);
		}

		void Uniform1i(GLint location, GLint x)
		{
			_glUniform1i(location, x);
		}

		void Uniform1iv(GLint location, GLsizei count, const GLint* v)
		{
			_glUniform1iv(location, count, v);
		}

		void Uniform2f(GLint location, GLfloat x, GLfloat y)
		{
			_glUniform2f(location, x, y);
		}

		void Uniform2fv(GLint location, GLsizei count, const GLfloat* v)
		{
			_glUniform2fv(location, count, v);
		}

		void Uniform2i(GLint location, GLint x, GLint y)
		{
			_glUniform2i(location, x, y);
		}

		void Uniform2iv(GLint location, GLsizei count, const GLint* v)
		{
			_glUniform2iv(location, count, v);
		}

		void Uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
		{
			_glUniform3f(location, x, y, z);
		}

		void Uniform3fv(GLint location, GLsizei count, const GLfloat* v)
		{
			_glUniform3fv(location, count, v);
		}

		void Uniform3i(GLint location, GLint x, GLint y, GLint z)
		{
			_glUniform3i(location, x, y, z);
		}

		void Uniform3iv(GLint location, GLsizei count, const GLint* v)
		{
			_glUniform3iv(location, count, v);
		}

		void Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
			_glUniform4f(location, x, y, z, w);
		}

		void Uniform4fv(GLint location, GLsizei count, const GLfloat* v)
		{
			_glUniform4fv(location, count, v);
		}

		void Uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
		{
			_glUniform4i(location, x, y, z, w);
		}

		void Uniform4iv(GLint location, GLsizei count, const GLint* v)
		{
			_glUniform4iv(location, count, v);
		}

		void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
		{
			_glUniformMatrix2fv(location, count, transpose, value);
		}

		void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
		{
			_glUniformMatrix3fv(location, count, transpose, value);
		}

		void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
		{
			_glUniformMatrix4fv(location, count, transpose, value);
		}

		void UseProgram(GLuint program)
		{
			_glUseProgram(program);
		}

		void ValidateProgram(GLuint program)
		{
			_glValidateProgram(program);
		}

		void VertexAttrib1f(GLuint indx, GLfloat x)
		{
			_glVertexAttrib1f(indx, x);
		}

		void VertexAttrib1fv(GLuint indx, const GLfloat* values)
		{
			_glVertexAttrib1fv(indx, values);
		}

		void VertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
		{
			_glVertexAttrib2f(indx, x, y);
		}

		void VertexAttrib2fv(GLuint indx, const GLfloat* values)
		{
			_glVertexAttrib2fv(indx, values);
		}

		void VertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
		{
			_glVertexAttrib3f(indx, x, y, z);
		}

		void VertexAttrib3fv(GLuint indx, const GLfloat* values)
		{
			_glVertexAttrib3fv(indx, values);
		}

		void VertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
			_glVertexAttrib4f(indx, x, y, z, w);
		}

		void VertexAttrib4fv(GLuint indx, const GLfloat* values)
		{
			_glVertexAttrib4fv(indx, values);
		}

		void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
		{
			_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
		}

		void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			_glViewport(x, y, width, height);
		}


	}
}