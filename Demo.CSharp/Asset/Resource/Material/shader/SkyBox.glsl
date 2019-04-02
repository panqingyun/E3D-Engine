varying vec3 ReflectDir;
varying vec4 vertColor;

#Vertex_Shader
#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "VertexShaderInc.glsl"

void main(void)
{
	ReflectDir = normalize(position);
	vertColor = color;	
    gl_Position = _e3d_getMVPMatrix() * vec4(position, 1.0);
}

#End

#Framgent_Shader
#ifdef __GLES__
precision highp float;
#endif
uniform samplerCube skybox;
void main(void) 
{ 
	vec4 color = textureCube(skybox,ReflectDir) * vertColor;
	gl_FragColor = color;
}

#End