#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
}

#include "Standard.shader"
varying vec4 DestinationColor; // 1
varying vec2 v_coord;
void main(void)
{	
	DestinationColor =  color;	
    v_coord = inputTextureCoordinate;
    gl_Position =  _e3d_getMVPMatrix() *  vec4(position ,1.0);
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif

varying vec4 DestinationColor; // 1
varying vec2 v_coord;
uniform sampler2D myTexture0;
const float TexSize = 512.0;

// 模糊
vec4 dip_filter(mat3 _filter, vec2 _xy)
{
	mat3 _filter_pos_delta_x=mat3(vec3(-1.0, 0.0, 1.0), vec3(0.0, 0.0 ,1.0) ,vec3(1.0,0.0,1.0));
    mat3 _filter_pos_delta_y=mat3(vec3(-1.0,-1.0,-1.0),vec3(-1.0,0.0,0.0),vec3(-1.0,1.0,1.0));
	vec4 final_color = vec4(0.0, 0.0, 0.0, 0.0);
	for(int i = 0; i<3; i++)
	{
		vec3 _ixy_new_x = _filter_pos_delta_x[i];
		vec3 _ixy_new_y = _filter_pos_delta_y[i];
		vec3 _ifilter = _filter[i];
			
		for(int j = 0; j<3; j++)
		{
			vec2 _xy_new = vec2(_xy.x + _ixy_new_x[j], _xy.y + _ixy_new_y[j]);
			vec2 _uv_new = vec2(_xy_new.x / TexSize, _xy_new.y / TexSize);
			final_color = final_color + texture2D(myTexture0, _uv_new) * _ifilter[j];
		}
	}
	return final_color;
}

void main(void) 
{
	vec2 intXY = vec2(v_coord.x * TexSize, v_coord.y * TexSize);
	mat3 _smooth_fil = mat3(1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0);
	vec4 tmp = dip_filter(_smooth_fil, intXY );
	gl_FragColor = vec4(1.0,1.0,1.0,1.0);// tmp;//texture2D(myTexture0, v_coord);
}

#Framgent_End