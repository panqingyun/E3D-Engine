
varying highp vec3 vPosition;
varying highp vec3 mCameraPos;

vec4 mixFogColor(vec4 _in_fragColor, vec4 _in_FogColor)
{
	float dist = abs(distance(mCameraPos, vPosition));
	float maxDist = 400.0;
	float minDist = 1.0;
    float fogFactor = (maxDist - dist) / (maxDist - minDist);  
    fogFactor = clamp( fogFactor, 0.0, 1.0 );  
	
    vec4 mColor = mix( _in_FogColor, _in_fragColor, fogFactor );  
  
    return mColor;
}