
varying vec3 vPosition;
varying vec3 mCameraPos;

vec4 mixFogColor(vec4 _in_fragColor, vec4 _in_FogColor)
{
	float dist = abs(distance(mCameraPos, vPosition));
	float maxDist = 300.0;
	float minDist = 1.0;
    float fogFactor = (maxDist - dist) / (maxDist - minDist);  
    fogFactor = clamp( fogFactor, 0.0, 1.0 );  
	
    vec4 mColor = mix( _in_FogColor, _in_fragColor, fogFactor );  
  
    return mColor;
}

// 模糊
vec4 dip_filter(mat3 _filter, vec2 _xy, sampler2D myTexture, float TexSize)
{
	mat3 _filter_pos_delta_x=mat3(vec3(-1.0, 0.0, 1.0), vec3(0.0, 0.0 ,1.0) ,vec3(1.0,0.0,1.0));
    mat3 _filter_pos_delta_y=mat3(vec3(-1.0,-1.0,-1.0),vec3(-1.0,0.0,0.0),vec3(-1.0,1.0,1.0));
	vec4 final_color = vec4(0.0, 0.0, 0.0, 0.0);
	for(int i = 0; i< 3; i++)
	{
		vec3 _ixy_new_x = _filter_pos_delta_x[i];
		vec3 _ixy_new_y = _filter_pos_delta_y[i];
		vec3 _ifilter = _filter[i];
			
		for(int j = 0; j< 3; j++)
		{
			vec2 _xy_new = vec2(_xy.x + _ixy_new_x[j], _xy.y + _ixy_new_y[j]);
			vec2 _uv_new = vec2(_xy_new.x / TexSize, _xy_new.y / TexSize);
			final_color = final_color + texture2D(myTexture, _uv_new) * _ifilter[j];
		}
	}
	return final_color;
}


vec4 getShadowColor(vec4 pos)
{
	vec4 shadowColor = vec4(1.0, 1.0 ,1.0 ,1.0);
	//float depth = texture(_e3d_lightDepthTex, pos.xy).r;
	float bias = 0.0;
	float texSize = 4096.0;
	
	vec2 intXY = vec2(pos.x * texSize, pos.y * texSize);
	mat3 _smooth_fil = mat3(1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0);
	vec4 tmp = dip_filter(_smooth_fil, intXY , _e3d_lightDepthTex, texSize);
	
	if(pos.z - bias > tmp.r) // 
	{
		shadowColor = shadowColor * 0.5;
	}	
	
	return shadowColor;
}
