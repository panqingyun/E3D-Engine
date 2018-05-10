#pragma once

#ifdef __IOS__ 
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include "EGL/eglplatform.h"
#include "EGL/egl.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#endif

#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>

#include <3rd/header/vvision.h>
