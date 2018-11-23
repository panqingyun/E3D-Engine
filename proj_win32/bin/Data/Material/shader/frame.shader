#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"

varying vec4 DestinationColor;

void main(void)
{	
	mat3 scale = mat3(vec3(_e3d_Scale.x, 	0.0,			0.0),
				vec3(0.0, 			_e3d_Scale.y,	0.0),
				vec3(0.0,	 		0.0,			_e3d_Scale.z)
	);
	mat4 _scale = mat4(vec4(1.0 /  _e3d_Scale.x, 	0.0,			0.0 , 0.0),
				vec4(0.0, 			1.0 /_e3d_Scale.y,	0.0 , 0.0),
				vec4(0.0,	 		0.0,			1.0 /_e3d_Scale.z , 0.0),
				vec4(0.0,	 		0.0,			0.0 , 1.0)
	);
	
	float tx = position.x / abs(position.x) / 5.0;
	float ty = position.y / abs(position.y) / 5.0;
	float tz = position.z / abs(position.z) / 5.0;
	vec3 tPos = scale * position + vec3(tx, ty, tz);
	
	vec4 _position = vec4(tPos ,1.0);
	//vec4 interpolatedPosition = vec4(position ,1.0);
	DestinationColor =  color;
	
    gl_Position = _e3d_getMVPMatrix()* _scale * _position ;
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif
varying vec4 DestinationColor; // 1
void main(void) 
{ // 2
	gl_FragColor = vec4(1.0,0.15,0.06,1.0);
}

#Framgent_End