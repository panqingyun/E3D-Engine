
varying highp vec3 vPosition;
varying highp vec3 mCameraPos;

vec4 mixFogColor(vec4 shadeColor)
{
	float dist = abs(distance(mCameraPos, vPosition));
	float maxDist = 300.0;
	float minDist = 1.0;
	vec4 color = vec4(1.0,1.0,1.0,1.0);
    float fogFactor = (maxDist - dist) / (maxDist - minDist);  
    fogFactor = clamp( fogFactor, 0.0, 1.0 );  
	
    vec4 mColor = mix( color, shadeColor, fogFactor );  
  
    return mColor;
}