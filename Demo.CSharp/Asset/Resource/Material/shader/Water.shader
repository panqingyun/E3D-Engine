#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

uniform float time;
varying vec3 ReflectDir;
varying vec4 vertColor;

varying vec4 vPos;
varying vec3 vNrm;
varying vec3 eyePosition;
varying vec2 v_Coord;

varying vec3 lightDir;
varying vec4 lightColor;

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

mat4 getRotateMatrix()
{
	mat4 rotate;
	rotate[0] = _e3d_matModel[0];
	rotate[1] = _e3d_matModel[1];
	rotate[2] = _e3d_matModel[2];
	rotate[3] = vec4(0.0,0.0,0.0,1.0);
	return rotate;
}

void main(void)
{
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);	
	eyePosition = _e3d_CameraPos.xyz;
	vPos =  _e3d_matModel * vec4(position, 1.0);; // 顶点位置
	vNrm = normalize(_normal.xyz); // 顶点法线
	vec3 posi = gerstner(position.x, position.y ,position.z);
	
#ifdef USING_DIRECTIONAL_LIGHT
	lightDir = _e3d_WorldSpaceLightDirection;
	lightColor = _e3d_WorldSpaceLightColor;
#else
	lightDir = vec3(0.0,0.0,0.0);
#endif

	vec4 _pos = _e3d_matModel * vec4(posi, 1.0);
	v_Coord = inputTextureCoordinate;
	vertColor = color;
    gl_Position = _e3d_getMVPMatrix() * vec4(position.x, posi.y*0.1, position.z, 1.0);
}

#Vertex_End

#Framgent_Begin
#ifdef __GLES__
precision highp float;
#endif
varying vec3 ReflectDir;
uniform sampler2D waterTex;
uniform sampler2D waterNormal;
uniform samplerCube skybox;
varying vec4 vertColor;

varying vec3 lightDir;
varying vec4 lightColor;


varying vec4 vPos;
varying vec3 vNrm;
varying vec3 eyePosition;
varying vec2 v_Coord;

uniform float fresnelBias;
uniform float etaRatio;

const vec4  ambient = vec4(0.8, 0.8, 0.8, 1.0);		//环境光颜色
const float Ns = 1.0;			//高光系数
const float attenuation = 1.0;	//光线的衰减系数

const float fresnelScale = 0.1;
const float fresnelPower = 5.0;

vec4 lerp(vec4 a, vec4 b, float s)
{
	return vec4(a+(b-a)*s);
}


vec4 getLightColor(vec3 position, vec3 normal)
{
	//--- 光照
	vec3 N = normalize((vec4(normal, 1.0)).xyz);
	vec3 L = normalize(lightDir);
	vec3 V = normalize(eyePosition - position);
	vec3 H = normalize(V + L);
	vec3 diffuse = vec3((lightColor * max(dot(N, L), 0.0)).xyz);
	vec3 specular = vec3((lightColor * pow(max(dot(N, H), 0.0), Ns) * attenuation).xyz);
	vec4 _lightColor = vec4(clamp((diffuse + specular), 0.0, 1.0), 1.0);

	return (_lightColor + ambient);
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
	vec4 normalColor = texture2D(waterNormal, v_Coord);
	vec4 normalVec = normalize(normalColor * 2.0 - 1.0);
	normalVec = vec4(normalVec.x, normalVec.z, -normalVec.y, normalVec.w);
	vec4 _lightColor = getLightColor(vPos.xyz, normalVec.xyz);
	gl_FragColor = vec4((FresnelShading() * _lightColor * vertColor).xyz, 0.8) * texture2D(waterTex, v_Coord);
}

#Framgent_End

