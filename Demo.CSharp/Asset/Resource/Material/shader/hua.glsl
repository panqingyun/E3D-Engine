varying vec2 v_coord;
varying vec4 DestinationColor;
varying vec3 normal;
varying vec3 vPosition;

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
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	InitLightVar(_pos);
	DestinationColor = color;
	vPosition = (_e3d_matModel * vec4(_pos.xyz ,1.0)).xyz;
	normal = _normal.xyz;
    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
}

#End

#Framgent_Shader

#ifdef __GLES__
precision highp float;
#endif
#include "FragmentShaderInc.glsl"
uniform sampler2D myTexture0;

void main(void) 
{
	float shdow = getShadowColor(0.0);
	vec4 color = texture2D(myTexture0, v_coord) * getLightColor(vPosition,normal,10.0, shdow);
	
	
	gl_FragColor = color; //mixFogColor(vec4(color.rgb, 1.0), vec4(1.0,1.0,1.0,1.0), vCameraPos,vPosition);
}

#End