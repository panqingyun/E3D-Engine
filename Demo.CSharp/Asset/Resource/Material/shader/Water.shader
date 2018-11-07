#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"

uniform float time;
varying vec3 ReflectDir;
varying vec4 vertColor;

varying vec4 vPos;
varying vec3 vNrm;
varying vec3 eyePosition;

const int n = 3;
const int m = 2;
vec2 thetas = vec2(0.38,1.42);
mat3 amplitudes = mat3(
	vec3(0.2, 0.2,0),
	vec3(0.3, 0.50,0),
	vec3(0.2, 0.6,0)
);
 const vec3 omegas = vec3(3.27,3.31,3.42);
 const vec3 waveNums = vec3(1.091,1.118,1.1935);

vec3 gerstner(float x, float y, float z)
{
	for (int i = 0; i < n; i++)
	{
		vec3 _amplitudes = amplitudes[i];
		for (int j = 0; j < m; j++)
		{
			x = x - cos(thetas[j]) * _amplitudes[j] * sin(waveNums[i] * (x * cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
            y = y + _amplitudes[j] * cos(waveNums[i] * (x * cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
            z = z - sin(thetas[j]) * _amplitudes[j] * sin(waveNums[i] * (x * cos(thetas[j]) + z * sin(thetas[j])) - omegas[i] * time);
		}
	}
	return vec3(x, y, z);
}


void main(void)
{
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);	
	eyePosition = _e3d_CameraPos.xyz;
	vPos =  _e3d_matModel * vec4(position, 1.0);; // 顶点位置
	vNrm = normalize(_normal.xyz); // 顶点法线
	vec3 posi = gerstner(position.x, position.y ,position.z);
	
	vec4 _pos = _e3d_matModel * vec4(posi, 1.0);
	
	vertColor =  getLightColor(_pos.xyz, _normal.xyz) * color;
    gl_Position = _e3d_getMVPMatrix() * vec4(position.x, posi.y*0.1, position.z, 1.0);
}

#Vertex_End

#Framgent_Begin
#ifdef __GLES__
precision highp float;
#endif
varying vec3 ReflectDir;

uniform samplerCube skybox;
varying vec4 vertColor;

varying vec4 vPos;
varying vec3 vNrm;
varying vec3 eyePosition;

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
	gl_FragColor = vec4((FresnelShading() * vertColor).xyz, 0.8);
}

#Framgent_End

