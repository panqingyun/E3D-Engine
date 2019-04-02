varying vec3 ReflectDir;
varying vec4 vertColor;

varying vec4 vPos;
varying vec3 vNrm;
varying vec3 eyePosition;
varying vec2 v_Coord;
varying float time;
varying vec4 v_InLightPos;

varying vec3 lightDir;
varying vec4 lightColor;

#Vertex_Shader
#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

const float _WaveScale = 0.1;
vec4 _2StreamVelo = vec4(-12.5, 42.7,-15.8,-0.34);
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

const  mat4 biasMatrix = mat4(0.5 , 0.0 , 0.0 , 0.0 ,
                       0.0 , 0.5 , 0.0 , 0.0 ,
                       0.0 , 0.0 , 0.5 , 0.0 ,
                       0.5 , 0.5 , 0.5 , 1.0 ) ;
					   

mat4 getRotateMatrix(vec3 rotate)
{
	mat4 roateMatX	= mat4(1.0, 0.0,0.0,0.0,
						   0.0, cos(rotate.x),sin(rotate.x),0.0,
						   0.0, -sin(rotate.x),cos(rotate.x),0.0,
						   0.0, 0.0,0.0, 1.0);
	
	mat4 roateMatY	= mat4(cos(rotate.y),0.0, -sin(rotate.y),0.0,
						   0.0,	1.0, 0.0,0.0,
						   sin(rotate.y),0.0, cos(rotate.y),0.0,
						   0.0,	0.0, 0.0,1.0);
	
	mat4 roateMatZ	= mat4(cos(rotate.z) ,	sin(rotate.z),	0.0, 0.0,
						   -sin(rotate.z),	cos(rotate.z),	0.0, 0.0,
						   0.0,						0.0,					1.0, 0.0,
						   0.0,						0.0,					0.0, 1.0);
	return roateMatX * roateMatY * roateMatZ;
}



void main(void)
{
	mat4 rotateMatrix = getRotateMatrix(_e3d_Rotation);
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);	
	eyePosition = _e3d_CameraPos.xyz;
	vPos =  _e3d_matModel * vec4(position, 1.0);; // 顶点位置
	vNrm = normalize(_normal.xyz); // 顶点法线
	//vec3 posi = gerstner(position.x, position.y ,position.z);
	
#ifdef USING_DIRECTIONAL_LIGHT
	lightDir = _e3d_WorldSpaceLightDirection;
	lightColor = _e3d_WorldSpaceLightColor;
	v_InLightPos = _e3d_lightMatProj * _e3d_lightMatView * vPos;
	v_InLightPos = biasMatrix* (v_InLightPos / v_InLightPos.w );
#else
	lightDir = vec3(0.0,0.0,0.0);
#endif
	time = _Time;
	vec4 _pos = _e3d_matModel * vec4(position, 1.0);
	
	v_Coord = inputTextureCoordinate;// * _WaveScale + (_2StreamVelo * time).xy ;//vPos.xzxz * _WaveScale + (_2StreamVelo * time) * 0.1;
	vertColor = color;
    gl_Position = _e3d_getMVPMatrix() * vec4(position, 1.0);
}

#End

#Framgent_Shader
#ifdef __GLES__
precision highp float;
#endif
uniform sampler2D waterTex;
uniform sampler2D waterNormal;
uniform samplerCube skybox;
uniform float fresnelBias;
uniform float etaRatio;

const vec3  ambient = vec3(0.8, 0.8, 0.8);		//环境光颜色
const float Ns = 30.0;			//高光系数
const float attenuation = 10.0;	//光线的衰减系数

const float _BumpDepth = 1.0;
const float _ReflScale = 3.598;
const float fresnelScale = 0.7;
const float fresnelPower = 1.0;

float near_clip = 1.0;
float ampify = 5.0;
float ks = 1.0;

vec4 lerp(vec4 a, vec4 b, float s)
{
	return vec4(a+(b-a)*s);
}


vec4 getLightColor(vec3 position, vec3 normal)
{
	//--- 光照 Blinn Phong 模型
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	vec3 V = normalize(eyePosition - position);
	vec3 H = normalize(V + L);
	float diffuse = max(dot(N, L), 0.0);
	
	float specular = pow(max(dot(N, H), 0.0), Ns);

	return vec4((lightColor * ( diffuse * 0.4 + specular * 0.3 + ambient * 0.3)).rgb, 1.0);
}


vec4 FresnelShading(vec3 normal)
{
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	vec3 V = normalize(eyePosition -  vPos.xyz);
	vec3 R = reflect(-V , N); // 反射
	// 反射因子计算
	float fresnel = fresnelScale + (1- fresnelScale) * pow(1.0 - dot(N, V), fresnelPower);
	// 获得反射环境色
	vec4 reflecColor = textureCube(skybox, R);
	reflecColor.a = 1.0;
	// 颜色合成
	vec4 cout = lerp(vertColor, reflecColor, fresnel);	
	return cout;
}

float getShadowColor(vec4 pos, float bias)
{
	float shadowColor = 1.0;
#ifndef __GLES__
#ifdef __CREATE_SHADOW__
	vec2 textSize = 1.0/ textureSize(_e3d_lightDepthTex, 0);
 	float depth = texture2D(_e3d_lightDepthTex, pos.xy).r;
	
	if(pos.z - bias > depth) // 
	{
		shadowColor = 0.5;
	}	
	else
	{
		vec4 coord1 = vec4(clamp(pos.xy - textSize, 0.0, 1.0),pos.z, pos.w );		
		vec4 coord2 = vec4(clamp(pos.xy + textSize, 0.0, 1.0),pos.z, pos.w );
		vec4 coord3 = vec4(clamp(pos.x -  textSize.x, 0.0, 1.0), clamp(pos.y + textSize.y, 0.0, 1.0) ,pos.z, pos.w );
		vec4 coord4 = vec4(clamp(pos.x +  textSize.x, 0.0, 1.0), clamp(pos.y - textSize.y, 0.0, 1.0) ,pos.z, pos.w );
		
		float depth1 =  texture2D(_e3d_lightDepthTex,coord1.xy).r;
		float depth2 =  texture2D(_e3d_lightDepthTex,coord2.xy).r;
		float depth3 =  texture2D(_e3d_lightDepthTex,coord3.xy).r;
		float depth4 =  texture2D(_e3d_lightDepthTex,coord4.xy).r;
		
		depth1 = coord1.z - bias > depth1 ?  0.5 : 1.0; 
		depth2 = coord2.z - bias > depth2 ?  0.5 : 1.0; 
		depth3 = coord3.z - bias > depth3 ?  0.5 : 1.0; 
		depth4 = coord4.z - bias > depth4 ?  0.5 : 1.0; 
		
		float mulColor = depth1* depth2 * depth3 * depth4;
		if (mulColor < 1.0)
		{
			shadowColor = (depth1+ depth2 + depth3 + depth4 ) / 4.0 * 0.9;
		}
	}
#endif
#endif
	return shadowColor;
}

void main(void) 
{ 
    float scale = 20.0; 
	float yV = mod(v_Coord.y * scale + time * 0.03, scale);
	float xV = mod( scale + v_Coord.x * scale - time * 0.02, scale);
	
	vec2 coord = vec2(v_Coord.x * scale, yV);
	vec2 coord1 = vec2(v_Coord.y * scale, xV);
	
	vec3 bump1 = texture2D( waterNormal, coord).rbg * 2.0 - 1.0;
	vec3 bump2 = texture2D( waterNormal, coord1).rbg * 2.0 - 1.0;
	
	vec3 normal =  normalize(vec3(bump1.x, _BumpDepth, bump1.z)); // 扰动法线
	vec3 normal2 =  normalize(vec3(bump2.x, _BumpDepth, bump2.z)); // 扰动法线
	
	vec3 normalVec = vec3(-normal.x, normal.z, normal.y); // 旋转法线到xz平面
	vec3 normalVec2 = vec3(normal2.x, normal2.z, normal2.y); // 旋转法线到xz平面
	
	vec4 _lightColor = getLightColor(vPos.xyz, normalVec.xyz);
	vec4 freColor1 = FresnelShading(normalVec);
	vec4 freColor2 = FresnelShading(vNrm);
	vec4 freColor3 = FresnelShading(normalVec2);	
	// float r = pow(freColor2.r, 2.0);
	// float g = pow(freColor2.g, 2.0);
	// float b = pow(freColor2.b, 2.0);
	// float sC = 1.0;//getShadowColor(v_InLightPos, 0.0);
	float dist = abs(distance(eyePosition, vPos.xyz));
	float maxDist = 230.0;
	float minDist = 1.0;
    float clr = (maxDist - dist) / (maxDist - minDist);  
    clr = pow(clamp( clr , 0.0, 1.0 ),2.0);    
    vec4 mColor = freColor2 * 0.4 + freColor1 * 0.3 + freColor3 * 0.3 ;
	mColor.rgb = mix((freColor1 * 0.5 + freColor3 * 0.5) , pow(mColor.rgb, vec3(1.0 / 1.5)), 1.0 - clr );
	float alpha = 1.0 - clr + 0.7;
	gl_FragColor = vec4((mColor).rgb, alpha) ;
}

#End

