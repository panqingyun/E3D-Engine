#pragma once

#include "EGL/eglplatform.h"
#include "EGL/egl.h"

#if GLES_VERSION == 2
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#elif GLES_VERSION == 3
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#endif
#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>

#include <3rd/header/vvision.h>