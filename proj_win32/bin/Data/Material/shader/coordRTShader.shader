#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
}

#include "Standard.shader"
varying lowp vec4 DestinationColor; // 1
varying highp vec2 v_coord;
void main(void)
{	
	DestinationColor =  color;	
    v_coord = inputTextureCoordinate;
    gl_Position =  _e3d_getMVPMatrix() *  vec4(position ,1.0);
}

#Vertex_End

#Framgent_Begin

precision highp float;
varying lowp vec4 DestinationColor; // 1
varying highp vec2 v_coord;
uniform sampler2D myTexture0;
void main(void) 
{ // 2
	gl_FragColor = DestinationColor * texture2D(myTexture0, v_coord) ;
}

#Framgent_End