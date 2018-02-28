# Install script for directory: C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/Debug/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/Release/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/MinSizeRel/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/RelWithDebInfo/assimp-vc140-mt.lib")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.3.1" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/Debug/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/Release/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/MinSizeRel/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/build/code/RelWithDebInfo/assimp-vc140-mt.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/anim.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/ai_assert.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/camera.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/color4.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/color4.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/config.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/defs.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/cfileio.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/light.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/material.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/material.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/matrix3x3.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/matrix3x3.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/matrix4x4.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/matrix4x4.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/mesh.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/postprocess.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/quaternion.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/quaternion.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/scene.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/metadata.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/texture.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/types.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/vector2.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/vector2.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/vector3.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/vector3.inl"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/version.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/cimport.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/importerdesc.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/Importer.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/IOStream.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/IOSystem.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/Logger.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/LogStream.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/NullLogger.hpp"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/cexport.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/Exporter.hpp"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/panqingyun/Downloads/assimp-3.3.1/assimp-3.3.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

