#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
}

#include "Standard.shader"
varying vec4 DestinationColor; // 1
varying vec2 v_coord;
void main(void)
{	
	DestinationColor =  color;	
    v_coord = inputTextureCoordinate;
    gl_Position =  _e3d_getMVPMatrix() *  vec4(position ,1.0);
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif

varying vec4 DestinationColor; // 1
varying vec2 v_coord;
uniform sampler2D myTexture0;

void main(void) 
{
	vec4 frameColor = texture2D(myTexture0, v_coord);
	gl_FragColor = frameColor;
}

#Framgent_End