varying vec3 ReflectDir;
varying vec4 vertColor;
varying vec3 lightDir;
varying vec4 lightColor;

varying vec4 vPos;
varying vec4 v_Pos;
varying vec3 vNrm;
varying vec3 eyePosition;
varying vec2 UV;

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
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _pos = _e3d_matModel * vec4(position, 1.0);
	vec3 eyeDir = normalize(_pos.xyz - _e3d_CameraPos.xyz);
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	vertColor = color;
#ifdef USING_DIRECTIONAL_LIGHT	
	lightDir = _e3d_WorldSpaceLightDirection;
	lightColor = _e3d_WorldSpaceLightColor;
#endif
	eyePosition = _e3d_CameraPos.xyz;
	vPos = _pos; // 顶点位置
	vNrm = normalize(_normal.xyz); // 顶点法线
	UV = inputTextureCoordinate;
    gl_Position = _e3d_getMVPMatrix() * vec4(position, 1.0);
}

#End

#Framgent_Shader
#ifdef __GLES__
precision highp float;
#endif

#include "FragmentShaderInc.glsl"

uniform samplerCube skybox;
uniform float fresnelBias;
uniform float etaRatio;

const float PI = 3.141592653;
const float F0 = 0.05;
const float fresnelPower = 2.0;

vec4 lerp(vec4 a, vec4 b, float s)
{
	return vec4(a+(b-a)*s);
}


float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return  ggx1 * ggx2;
}

// NDF
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = pow(a, 3.0);
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float rand(float x, float y)
{
	return fract(cos(x * (12.9898) + y * (4.1414)) * 43758.5453);
}

vec2 sampling_equirectangular_map(vec3 n) {
    float u = atan(n.z, n.x);
    u = (u + PI) / (2.0 * PI);

    float v = asin(n.y);
    v = (v * 2.0 + PI) / (2.0 * PI);

    return vec2(u, v);
}

vec4 getLightColor(vec3 position, vec3 normal)
{
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	vec3 V = normalize(eyePosition - position);
	vec3 H = normalize(V + L);
	vec3 R = reflect(-V, N); // 反射
	
	float diffuse = max(dot(N, L), 0.0) / PI;
	//float ambent = textureCube(skybox, R).r;
	float roughness = 0.4;// rand(UV.x, UV.y) * ambent; // 随机一个粗糙度
	// ambent = clamp((ambent - 0.5 ) * 8.0 , 1.0, 4.0) / 2.0;
	// ambent = pow(ambent, 4.0);
	float _F = pow(F0 + (1.0 - F0) * (1.0 - dot(N, V)), fresnelPower);
	float _V = GeometrySmith(N, V, L, roughness) / 4.0 * max(dot(N, L), 0.0) * max(dot(N, V), 0.0);
	float _D =  DistributionGGX(N, H,roughness);
	vec3 specular = _V * _D;
	vec4 reflecColor = textureCube(skybox, R);
	//vec3 ambSpec = ambent * _V * _D;

	return vec4(lightColor * specular + lightColor * diffuse, 1.0) * (1.0 - _F) + _F * reflecColor + vec4(0.1) ;
}

vec4 FresnelShading(void)
{
	// 计算入射，反射，折射
	vec3 N = normalize(vNrm); // 法线
	vec3 I = normalize(vPos.xyz-eyePosition); // 入射
	vec3 R = reflect(I, N); // 反射
	vec3 T = refract(I, N, etaRatio); // 折射
	// 反射因子计算
	float fresnel = fresnelBias+ F0 * pow(min(0.0, 1.0-dot(I, N)), fresnelPower);
	// 获得反射环境色
	vec4 reflecColor = textureCube(skybox, R);
	reflecColor.a = 1.0;
	// 计算折射环境色
	vec4 refracColor;
	refracColor.rgb = textureCube(skybox, T).rgb;
	refracColor.a = 1.0;
	// 颜色合成
	vec4 cout = lerp(refracColor, reflecColor, fresnel);
	cout.a = fresnel*0.5+0.5;
	return cout;
}

void main(void) 
{ 
	vec4 freColor = FresnelShading();
	vec4 lcolor = getLightColor(vPos, vNrm);
	gl_FragColor = lcolor  * vec4(vertColor.rgb, vertColor.a);
}

#End