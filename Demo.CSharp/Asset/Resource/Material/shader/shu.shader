#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"
varying vec2 v_coord;
varying vec4 DestinationColor;
vec4 _WindDir = vec4(0.4,0.1,0.3,0.2);

void main(void)
{
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	DestinationColor = color;
	
	float power = _WindDir.w;
	_WindDir.w = 0.0;
	vec3 dir =  normalize(_e3d_matModel*_WindDir).xyz;
	vec3 _vPos = position + dir * (sin(_Time + _e3d_matModel[3][2]) + 1.0) * power * pow(position.z / 100.0, 2.0); //摇动
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz) * color;
    gl_Position = _e3d_getMVPMatrix() * vec4(_vPos ,1.0);
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif
#include "Fragment.shader"
varying vec2 v_coord;
uniform sampler2D myTexture0;
varying vec4 DestinationColor;

void main(void) 
{ 
	vec4 color = texture2D(myTexture0, v_coord);
	
	if(color.a < 0.3)
	{
		discard;
	}
	else
	{
		gl_FragColor = DestinationColor * color;
	}
}

#Framgent_End