/* types.h
 *
 * Virtual Vision Engine . Copyright (C) 2012 Abdallah DIB.
 * All rights reserved. Email: Abdallah.dib@virtual-vison.net
 * Web: <http://www.virutal-vision.net/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef VVISION_base_h
#define VVISION_base_h

#include "vmath.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
//#define VvisionLog (0)

using namespace std;

namespace vvision
{    
    /** shader attribute index*/
    enum
    {
        /** vertex attrib*/
        ATTRIB_VERTEX,
        
        /** color attrib*/
        ATTRIB_COLOR,
        
        /** normal attrib*/
        ATTRIB_NORMAL,
        
        /** texture 0 coord attrib*/
        ATTRIB_TEXTURE0,
        
        /** texture 1 coord attrib*/
        ATTRIB_TEXTURE1,
        
        /** tangent coord attrib*/
        ATTRIB_TANGENT,
        
        /** bone index attrib*/
        ATTRIB_BONES_INDICES,
        
        /** bone weight attrib*/
        ATTRIB_BONES_WEIGHTS,
        
        /** attrib number*/
        NUM_ATTRIBUTES
    };
    
    /* 8 bit unsigned variable.*/
    typedef unsigned char		uchar8;
    
    /* 8 bit signed variable.*/
    typedef signed char		schar8;
    
    /** 8 bit character variable. */
    typedef char			char8;
    
    /** 16 bit unsigned variable. */
    typedef unsigned short		ushort16;
    
    /** 16 bit signed variable.*/
    typedef signed short		sshort16;
    
    /** 32 bit unsigned variable.*/
    typedef unsigned int		uint32;
    
    /** 32 bit signed variable.*/
    typedef signed int		sint32;
    
    /** 32 bit signed variable.*/
    typedef  int		int32;
    
    /** 32 bit floating point variable.*/
    typedef float				float32;
    
    /** 64 bit floating point variable.*/
    typedef double				float64;
    
#define SAFE_DELETE(ptr) \
if(ptr != NULL) \
{delete ptr; ptr = NULL;}
    //maximum finite value
#define VV_MAXIMUM_FLOAT        std::numeric_limits<float32>::max( )
#define VV_MAXIMUM_DOUBLE       std::numeric_limits<float64>::max( )
#define VV_MAXIMUM_INTEGER      std::numeric_limits<int32>::max( )
#define VV_MAXIMUM_CHAR        std::numeric_limits<char8>::max( )
#define VV_MAXIMUM_SHOR_INT    std::numeric_limits<sshort16>::max( )

}

#endif
