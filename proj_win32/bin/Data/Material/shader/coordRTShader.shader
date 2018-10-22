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
	mat4 viewMat = _e3d_matView;
	viewMat[3] = vec4(0, 0, 0, 1);
	
    gl_Position = _e3d_matProj * _e3d_matView * _e3d_matModel * interpolatedPosition;
}

#Vertex_End

#Framgent_Begin

precision highp float;
varying lowp vec4 DestinationColor; // 1
void main(void) 
{ // 2
	gl_FragColor = DestinationColor;
}

#Framgent_End