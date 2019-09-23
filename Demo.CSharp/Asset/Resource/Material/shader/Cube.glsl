varying vec2 v_coord;
varying vec4 DestinationColor;
varying vec3 normal;
varying vec4 vPosition;

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
	vPosition = _e3d_matModel * interpolatedPosition;
#ifdef USING_DIRECTIONAL_LIGHT
	InitLightVar(vPosition);
#endif
	DestinationColor = color;
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
	//float bias = max(0.0005 * (1.0 - dot(normal, lightDir)), 0.0009);
	float shdow = getShadowColor(0.0);
	vec4 color = texture2D(myTexture0, v_coord) * getLightColor(vPosition, normal, 10.0, shdow);
	
	gl_FragColor = DestinationColor * vec4(color.rgb, 1.0);
}

#End