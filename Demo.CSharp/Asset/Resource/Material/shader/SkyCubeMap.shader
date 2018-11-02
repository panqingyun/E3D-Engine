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
uniform int bSkyBox;

void main(void)
{
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _pos = _e3d_matModel * vec4(position, 1.0);
	vec3 eyeDir = normalize(_pos.xyz - _e3d_CameraPos.xyz);
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	if (bSkyBox == 1)
	{
		ReflectDir = normalize(position);
	}
	else
	{
		ReflectDir = reflect(eyeDir, normalize(_normal.xyz));
	}
	vertColor = color;
	
	initFogNeedVar(position);
	
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
	gl_FragColor = color;//texture2D(skybox, v_coord);	
}

#Framgent_End