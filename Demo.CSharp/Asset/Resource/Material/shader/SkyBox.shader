#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"

varying vec3 ReflectDir;
varying vec4 vertColor;

void main(void)
{
	ReflectDir = normalize(position);
	vertColor = color;	
    gl_Position = _e3d_getMVPMatrix() * vec4(position, 1.0);
}

#Vertex_End

#Framgent_Begin
#ifdef __GLES__
precision highp float;
#endif
varying vec3 ReflectDir;

uniform samplerCube skybox;
varying vec4 vertColor;

void main(void) 
{ 
	vec4 color = textureCube(skybox,ReflectDir) * vertColor;
	gl_FragColor = color;
}

#Framgent_End