#ifndef __E3D_INCLUDE_H__
#define __E3D_INCLUDE_H__

#ifdef _WIN32
#pragma unmanaged
#include <windows.h>
#include <iterator> 
#include <windows.h>
#include <corecrt_io.h>
#endif // WIN32

#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>

#ifndef __EDITOR__
#include <btBulletDynamicsCommon.h>

#include <assimp/mesh.h> 
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#endif

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>

#endif /* commonType_h */
