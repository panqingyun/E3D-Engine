
varying highp vec3 vPosition;
varying highp vec3 mCameraPos;

const vec4  ambient = vec4(0.8, 0.8, 0.8, 1.0);		//环境光颜色
const float Ns = 1.0;			//高光系数
const float attenuation = 1.0;	//光线的衰减系数

void initFogNeedVar(vec3 _pos)
{
	vPosition = (_e3d_matModel * vec4(_pos ,1.0)).xyz;
	mCameraPos = _e3d_CameraPos;
}

vec4 getPointLightColor(vec3 position, vec3 normal)
{
	vec4 lightColor = vec4(0.0,0.0,0.0,1.0);
	
#ifdef USING_POINT_LIGHT
	vec3 N = normalize((vec4(normal, 1.0)).xyz);
	vec3 V = normalize(_e3d_CameraPos - position);
	for (int i = 0; i < _e3d_PointLightCount; i++)
	{
		if(distance(_e3d_PointLightPos[i] , position) < _e3d_PointLightRange[i])
		{
			vec3 L = normalize(_e3d_PointLightPos[i] - position);
			vec3 H = normalize(V + L);
			vec3 diffuse = vec3((_e3d_PointLightColor[i] * max(dot(N, L), 0.0)).xyz);
			vec3 specular = vec3((_e3d_PointLightColor[i] * pow(max(dot(N, H), 0.0), Ns) * attenuation).xyz);
			
			lightColor = lightColor + vec4(clamp((diffuse + specular), 0.0, 1.0), 1.0);
		}
	}
#endif
	return lightColor;
}

vec4 getLightColor(vec3 position, vec3 normal)
{
	vec4 lightColor = vec4(0.0,0.0,0.0,1.0);
#ifdef USING_DIRECTIONAL_LIGHT
	//--- 光照
	vec3 N = normalize((vec4(normal, 1.0)).xyz);
	vec3 L = normalize(_e3d_WorldSpaceLightDirection);
	vec3 V = normalize(_e3d_CameraPos - position);
	vec3 H = normalize(V + L);
	vec3 diffuse = vec3((_e3d_WorldSpaceLightColor * max(dot(N, L), 0.0)).xyz);
	vec3 specular = vec3((_e3d_WorldSpaceLightColor * pow(max(dot(N, H), 0.0), Ns) * attenuation).xyz);
	lightColor = vec4(clamp((diffuse + specular), 0.0, 1.0), 1.0);
#endif
#ifdef USING_POINT_LIGHT
	lightColor = lightColor + getPointLightColor(position, normal);
#endif
	return (lightColor + ambient);
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
/*
uniform struct Light {
    vec4 lightPosition;
    vec4 lightColor;
    vec4 lightDirection;
    vec2 lightSize;
    float lightIntensity;
    int  lightDistAttenCurveType;
    float lightDistAttenCurveParams[5];
    int  lightAngleAttenCurveType;
    float lightAngleAttenCurveParams[5];
} allLights[MAX_LIGHTS];

vec3 apply_areaLight(Light light)
{
    vec3 N = normalize(normal.xyz);
    vec3 right = normalize((viewMatrix * worldMatrix * vec4(1.0f, 0.0f, 0.0f, 0.0f)).xyz);
    vec3 pnormal = normalize((viewMatrix * worldMatrix * light.lightDirection).xyz);
    vec3 ppos = (viewMatrix * worldMatrix * light.lightPosition).xyz;
    vec3 up = normalize(cross(pnormal, right));
    right = normalize(cross(up, pnormal));

    //width and height of the area light:
    float width = light.lightSize.x;
    float height = light.lightSize.y;

    //project onto plane and calculate direction from center to the projection.
    vec3 projection = projectOnPlane(v.xyz, ppos, pnormal);// projection in plane
    vec3 dir = projection - ppos;

    //calculate distance from area:
    vec2 diagonal = vec2(dot(dir,right), dot(dir,up));
    vec2 nearest2D = vec2(clamp(diagonal.x, -width, width), clamp(diagonal.y, -height, height));
    vec3 nearestPointInside = ppos + right * nearest2D.x + up * nearest2D.y;

    vec3 L = nearestPointInside - v.xyz;

    float lightToSurfDist = length(L);
    L = normalize(L);

    // distance attenuation
    float atten = apply_atten_curve(lightToSurfDist, light.lightDistAttenCurveType, light.lightDistAttenCurveParams);

    vec3 linearColor = vec3(0.0f);

    float pnDotL = dot(pnormal, -L);

    if (pnDotL > 0.0f && isAbovePlane(v.xyz, ppos, pnormal)) //looking at the plane
    {
        //shoot a ray to calculate specular:
        vec3 V = normalize(-v.xyz);
        vec3 R = normalize(2.0f * dot(V, N) *  N - V);
        vec3 R2 = normalize(2.0f * dot(L, N) *  N - L);
        vec3 E = linePlaneIntersect(v.xyz, R, ppos, pnormal);

        float specAngle = clamp(dot(-R, pnormal), 0.0f, 1.0f);
        vec3 dirSpec = E - ppos;
        vec2 dirSpec2D = vec2(dot(dirSpec, right), dot(dirSpec, up));
        vec2 nearestSpec2D = vec2(clamp(dirSpec2D.x, -width, width), clamp(dirSpec2D.y, -height, height));
        float specFactor = 1.0f - clamp(length(nearestSpec2D - dirSpec2D), 0.0f, 1.0f);

        if (usingDiffuseMap)
        {
            linearColor = ambientColor.rgb + light.lightIntensity * atten * light.lightColor.rgb * (texture(diffuseMap, uv).rgb * dot(N, L) * pnDotL + specularColor.rgb * pow(clamp(dot(R2, V), 0.0f, 1.0f), specularPower) * specFactor * specAngle); 
        }
        else
        {
            linearColor = ambientColor.rgb + light.lightIntensity * atten * light.lightColor.rgb * (diffuseColor.rgb * dot(N, L) * pnDotL + specularColor.rgb * pow(clamp(dot(R2, V), 0.0f, 1.0f), specularPower) * specFactor * specAngle); 
        }
    }

    return linearColor;
}*/