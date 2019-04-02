varying vec2 v_coord;
varying vec4 DestinationColor;
varying vec3 normal;
varying vec3 lightDir;

varying vec4 v_Pos;

#Vertex_Shader

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "VertexShaderInc.glsl"

const  mat4 biasMatrix = mat4(0.5 , 0.0 , 0.0 , 0.0 ,
                       0.0 , 0.5 , 0.0 , 0.0 ,
                       0.0 , 0.0 , 0.5 , 0.0 ,
                       0.5 , 0.5 , 0.5 , 1.0 ) ;

void main(void)
{
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
#ifdef USING_DIRECTIONAL_LIGHT
	v_Pos = _e3d_lightMatProj * _e3d_lightMatView * _pos;
	v_Pos = (v_Pos / v_Pos.w + 1.0) * 0.5;
	lightDir = _e3d_WorldSpaceLightDirection;
#endif
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz, 100.0) * color;
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
	float bias = max(0.0005 * (1.0 - dot(normal, lightDir)), 0.0009);
	vec4 color = texture2D(myTexture0, v_coord) * getShadowColor(v_Pos, 0.0);	
	
	gl_FragColor = DestinationColor * vec4(color.rgb, 1.0);
}

#End