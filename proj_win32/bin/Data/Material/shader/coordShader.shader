#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"

varying vec4 DestinationColor;

void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);
	DestinationColor =  color;
	
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif
varying vec4 DestinationColor; // 1
void main(void) 
{ // 2
	gl_FragColor = DestinationColor;
}

#Framgent_End