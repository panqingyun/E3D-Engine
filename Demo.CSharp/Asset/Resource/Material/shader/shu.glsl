varying vec2 v_coord;
varying vec4 DestinationColor;
varying vec3 vPosition;
varying vec3 vNormal;

#Vertex_Shader
#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "VertexShaderInc.glsl"
vec4 _WindDir = vec4(0.4,0.1,0.3,0.2);

void main(void)
{
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vNormal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	DestinationColor = color;
	vPosition = (_e3d_matModel * vec4(position ,1.0)).xyz;
	vCameraPos = _e3d_CameraPos;
	InitLightVar(_pos);
	float power = _WindDir.w;
	_WindDir.w = 0.0;
	vec3 dir =  normalize(_e3d_matModel*_WindDir).xyz;
	vec3 _vPos = position + dir * (sin(_Time + _e3d_matModel[3][2]) + 1.0) * power * pow(position.z / 100.0, 2.0); //摇动
	//DestinationColor = getLightColor(_pos.xyz, _normal.xyz, 2.0) * color;
    gl_Position = _e3d_getMVPMatrix() * vec4(_vPos ,1.0);
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
	vec4 color = texture2D(myTexture0, v_coord);
	float shadow = getShadowColor(0.0);
	if(color.a < 0.3)
	{
		discard;
	}
	else
	{		
		gl_FragColor = mixFogColor( DestinationColor * color , vec4(1.0,1.0,1.0,1.0),vPosition) * getLightColor(vPosition, vNormal, 10.0, shadow);;
	}
}

#End