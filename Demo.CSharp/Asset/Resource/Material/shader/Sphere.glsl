
varying vec4 DestinationColor;
varying vec2 v_coord;
varying vec3 v_Position;
varying vec3 normal;
varying vec4 lightColor;
varying vec3 lightDir;
varying vec3 cameraPos;

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
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	
	v_Position = _pos.xyz;
	normal = _normal.xyz;
	lightColor = _e3d_WorldSpaceLightColor;
	lightDir = _e3d_WorldSpaceLightDirection;
	cameraPos = _e3d_CameraPos;
	
	DestinationColor = color;// getPBRLight(_pos.xyz, _normal.xyz, 0.25, 0.05) * color;
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;
}

#End

#Framgent_Shader

#ifdef __GLES__
precision highp float;
#endif

#include "FragmentShaderInc.glsl"

uniform sampler2D myTexture0;

// VDF BRDF
float BRDF(vec3 position, vec3 normal, float roughness, float frenal)
{
	const float PI = 3.141592653;
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	vec3 V = normalize(cameraPos - position);
	vec3 H = normalize(V + L);	
    float a      = roughness*roughness*roughness*roughness;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	float NdotL = max(dot(N, L), 0.0);
	float NdotV = max(dot(N, V), 0.0);
    float denom = (NdotH2 * (a - 1.0) + 1.0);
    denom = PI * denom * denom;
	
	float k = pow(a + 1.0, 2.0) / 8.0;
	float GGXL = NdotL / (k + (1.0 - k) * NdotL);
	float GGXV = NdotV / (k + (1.0 - k) * NdotV);
	float _D = a / denom;	
	float _V = GGXL * GGXV ;// (4.0 * NdotL * NdotV)
	//float _F = frenal + (1.0 - frenal)*pow((1.0 - NdotV), 2.0);
	
	return  _V *_D;
}

vec4 getPBRLight(vec3 position, vec3 normal, float roughness, float frenal, float metalic)
{	
	const float PI = 3.141592653;
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	vec3 V = normalize(cameraPos - position);
	vec4 diffuse = lightColor / PI;
	float _F = frenal + (1.0 - frenal) * pow((1.0 - max(dot(N, V), 0.0)), 2.0);
	vec4 specular = lightColor * BRDF(position,normal, roughness, frenal);
	float kdiff = (1.0 - frenal) * (1.0 - metalic );
	vec4 lightColor = (diffuse + specular * frenal * _F) * max(dot(N, L), 0.0);
	
	
	return lightColor + vec4(0.3);
}

void main(void) 
{ 
	vec4 texColor =  texture2D(myTexture0, v_coord);
	float Metalic = 0.9;
	float F0 = Metalic * texColor.b + (1 - Metalic) * 0.04;
	
	vec4 L = getPBRLight(v_Position, normal, 0.25, F0, Metalic);
	gl_FragColor =  L * texColor * DestinationColor;	
}

#End