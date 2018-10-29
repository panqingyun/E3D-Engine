#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"

varying lowp vec2 v_coord;
varying vec3 normal;

void main(void)
{
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	normal = attr_normal;
	
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;
}

#Vertex_End

#Framgent_Begin

precision highp float;

varying highp vec2 v_coord;
varying vec3 normal;

uniform samplerCube skybox;

void main(void) 
{ 
    vec4 color = textureCube(skybox,normal);
	gl_FragColor = color;//texture2D(skybox, v_coord);	
}

#Framgent_End