
varying vec2 v_coord;

#Vertex_Shader

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}
#include "VertexShaderInc.glsl"

void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);	
	v_coord = inputTextureCoordinate;
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;
}

#End

#Framgent_Shader

#ifdef __GLES__
precision highp float;
#endif

uniform sampler2D myTexture0;
const float TexSize = 1024.0;

// 模糊
vec4 dip_filter(mat3 _filter, vec2 _xy)
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
			final_color = final_color + texture(myTexture0, _uv_new) * _ifilter[j];
		}
	}
	return final_color;
}


void main(void) 
{ //texture2D(myTexture0, v_coord).rgb
	vec2 intXY = vec2(v_coord.x * TexSize, v_coord.y * TexSize);
	mat3 _smooth_fil = mat3(1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0);
	vec4 tmp = dip_filter(_smooth_fil, intXY );
	//float depth = texture(myTexture0, v_coord).r;
	gl_FragColor = vec4(tmp.r,tmp.r,tmp.r, 1.0);
}

#End