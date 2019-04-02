const float r1 = 1.0;
const float r2 = 1.0 / 256.0;
const float r3 = 1.0 / (256.0 * 256.0);
const float r4 = 1.0 / (256.0 * 256.0 * 256.0);

float unpackDepth(const in vec4 rgbaDepth) 
{
    const vec4 bitShift = vec4(r1, r2, r3, r4);
    float depth = dot(rgbaDepth, bitShift);
    return depth;
}

float texture2DCompare(sampler2D depths, vec2 uv, float compare, float bias)
{
    float depth = unpackDepth(texture2D(depths, uv));
    return step(compare,depth);
}

vec4 mixFogColor(vec4 _in_fragColor, vec4 _in_FogColor, vec3 cameraPos,vec3 position)
{
	float dist = abs(distance(cameraPos, position));
	float maxDist = 1500.0;
	float minDist = 1.0;
    float fogFactor = (maxDist - dist) / (maxDist - minDist);  
    fogFactor = clamp( fogFactor, 0.0, 1.0 );  
	
    vec4 mColor = mix( _in_FogColor, _in_fragColor, fogFactor );  
  
    return mColor;
}

float texture2DShadowLerp(sampler2D depths, vec2 uv, float compare, float bias)
{
    float size = textureSize(depths, 0).x;
	vec2 texelSize = vec2(1.0) / vec2(size, size);
    vec2 centroidUV = floor(uv * size + 0.5) / size;
    vec2 f = fract(uv * size + 0.5);
    float lb = texture2DCompare(depths, centroidUV + texelSize * vec2(0.0, 0.0), compare ,bias);
    float lt = texture2DCompare(depths, centroidUV + texelSize * vec2(0.0, 1.0), compare ,bias);
    float rb = texture2DCompare(depths, centroidUV + texelSize * vec2(1.0, 0.0), compare ,bias);
    float rt = texture2DCompare(depths, centroidUV + texelSize * vec2(1.0, 1.0), compare ,bias);
    float a = mix(lb, lt, f.y);
    float b = mix(rb, rt, f.y);
    float c = mix(a, b, f.x);
    return c;
}

float PCFLerp(sampler2D depths, vec2 uv, float compare, float bias) 
{	
	vec2 textSize = 1.0/ textureSize(depths, 0);
    float result = 0.0;
    for(int x = -1; x <= 1; x++)
	{
        for(int y = -1; y <= 1; y++)
		{
            vec2 off = textSize * vec2(x,y);
            result += texture2DShadowLerp(depths, uv + off, compare, bias);
        }
    }
    return result / 9.0;
}

float getShadowColor(vec4 pos, float bias)
{
	float shadowColor = 1.0;
#ifndef __GLES__
#ifdef __CREATE_SHADOW__
	shadowColor = clamp(PCFLerp(_e3d_lightDepthTex, pos.xy, pos.z + bias , bias) + 0.3, 0.3, 1.0);
#endif
#endif
	return shadowColor;
}
