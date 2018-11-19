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
varying vec3 lightDir;

varying vec4 vPos;
varying vec4 v_Pos;
varying vec3 vNrm;
varying vec3 eyePosition;
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
	v_Pos = _e3d_lightMatProj * _e3d_lightMatView * _pos;
	v_Pos = biasMatrix* (v_Pos / v_Pos.w );
	lightDir = _e3d_WorldSpaceLightDirection;
#endif
	initFogNeedVar(position);
	eyePosition = _e3d_CameraPos.xyz;
	vPos = _pos; // 顶点位置
	vNrm = normalize(_normal.xyz); // 顶点法线
    gl_Position = _e3d_getMVPMatrix() * vec4(position, 1.0);
}

#Vertex_End

#Framgent_Begin
#ifdef __GLES__
precision highp float;
#endif
#include "Fragment.shader"
varying vec3 ReflectDir;

uniform samplerCube skybox;
varying vec4 vertColor;

varying vec4 vPos;
varying vec4 v_Pos;
varying vec3 vNrm;
varying vec3 eyePosition;
varying vec3 lightDir;

uniform float fresnelBias;
uniform float etaRatio;

const float fresnelScale = 0.1;
const float fresnelPower = 5.0;

vec4 lerp(vec4 a, vec4 b, float s)
{
	return vec4(a+(b-a)*s);
}


vec4 FresnelShading(void)
{
	// 计算入射，反射，折射
	vec3 N = normalize(vNrm); // 法线
	vec3 I = normalize(vPos.xyz-eyePosition); // 入射
	//vec3 R = reflect(I, N); // 反射
	vec3 R = reflect(I, N); // 反射
	//vec3 T = refract(I, N, etaRatio); // 折射
	vec3 T = refract(I, N, etaRatio); // 折射
	// 反射因子计算
	float fresnel = fresnelBias+fresnelScale*pow(min(0.0, 1.0-dot(I, N)), fresnelPower);
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
	float bias = max(0.008 * (1.0 - dot(vNrm, lightDir)), 0.0008);
	float shadowColor = getShadowColor(v_Pos, bias);
	gl_FragColor = FresnelShading() * vec4(vertColor.rgb * shadowColor, vertColor.a);
}

#Framgent_End