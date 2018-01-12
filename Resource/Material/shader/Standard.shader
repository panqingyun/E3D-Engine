vec3 lightposition;	//光源位置
vec4 ambient;		//环境光颜色
vec4 lightcolor;	//光源颜色
float Ns;			//高光系数
float attenuation;	//光线的衰减系数

vec4 getLightColor(vec3 position, vec3 normal)
{
	//--------------------------------------------------------------
	//--- 光照
	lightposition = vec3(50.0, 50.0, 50.0);
	ambient = vec4(0.5, 0.5, 0.5, 1.0);
	lightcolor = vec4(1.0, 1.0, 1.0, 1.0);
	Ns = 10.0;
	attenuation = 0.1;
	vec4 interpolatedPosition = vec4(position, 1.0);
	vec3 N = normalize((vec4(normal, 1.0)).xyz);
	vec3 L = normalize(lightposition - interpolatedPosition.xyz);
	vec3 V = normalize(_e3d_cameraPos - interpolatedPosition.xyz);
	vec3 H = normalize(V + L);
	vec3 diffuse = vec3((lightcolor * max(dot(N, L), 0.0)).xyz);
	vec3 specular = vec3((lightcolor * pow(max(dot(N, H), 0.0), Ns) * attenuation).xyz);
	vec4 _des_color = vec4(clamp((diffuse + specular), 0.0, 1.0), 1.0);
	return (_des_color + ambient);
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

mat4 getBillboardMatrix(vec3 position, vec3 worldCameraPosition, vec3 worldCameraUp)
{
    vec3 forward = normalize(position - worldCameraPosition);
    vec3 side = cross( forward, worldCameraUp );
    
    mat4 result;
    result[0] = vec4( side, 0.0 );
    result[1] = vec4( worldCameraUp, 0.0 );
    result[2] = vec4( forward.x, 0.0, forward.z, 0.0 );
    result[3] = vec4( 0.0, 0.0, 0.0, 1.0 );
    return result;
}

mat4 getTransformRotateMatrix(vec3 transformRotate)
{
	mat4 roateMatX	= mat4(1.0, 0.0,						0.0,					0.0,
						   0.0, cos(transformRotate.x),	sin(transformRotate.x),		0.0,
						   0.0, -sin(transformRotate.x),	cos(transformRotate.x),	0.0,
						   0.0, 0.0,						0.0, 1.0);
	
	mat4 roateMatY	= mat4(cos(transformRotate.y),	0.0, -sin(transformRotate.y),	0.0,
						   0.0,						1.0, 0.0,						0.0,
						   sin(transformRotate.y),	0.0, cos(transformRotate.y),	0.0,
						   0.0,						0.0, 0.0,						1.0);
	
	mat4 roateMatZ	= mat4(cos(transformRotate.z) ,	sin(transformRotate.z),	0.0, 0.0,
						   -sin(transformRotate.z),	cos(transformRotate.z),	0.0, 0.0,
						   0.0,						0.0,					1.0, 0.0,
						   0.0,						0.0,					0.0, 1.0);
	return roateMatX * roateMatY * roateMatZ;
}

mat4 getTransformMatrix(vec3 transformPosition, vec3 transformRotate, vec3 transformScale)
{
	mat4 translate	= mat4(1.0,					0.0,					0.0,					0.0,
						   0.0,					1.0,					0.0,					0.0,
						   0.0,					0.0,					1.0,					0.0,
						   transformPosition.x,	transformPosition.y,	transformPosition.z,	1.0);
	
	
	mat4 scaleMat	= mat4(transformScale.x	, 0.0			  ,		0.0				,	0.0,
						   0.0				, transformScale.y,		0.0				,	0.0,
						   0.0				, 0.0			  ,		transformScale.z,	0.0,
						   0.0				, 0.0			  ,		0.0				,	1.0
						   );
	
	mat4 roateMatrix = getTransformRotateMatrix(transformRotate);
	
	return translate * roateMatrix * scaleMat;
}