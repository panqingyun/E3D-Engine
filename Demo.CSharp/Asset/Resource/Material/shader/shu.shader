varying vec2 v_coord;
varying vec4 DestinationColor;
varying vec4 v_Pos;
#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	NORMAL:attr_normal;
}

#include "Standard.shader"
vec4 _WindDir = vec4(0.4,0.1,0.3,0.2);

const  mat4 biasMatrix = mat4(0.5 , 0.0 , 0.0 , 0.0 ,
                       0.0 , 0.5 , 0.0 , 0.0 ,
                       0.0 , 0.0 , 0.5 , 0.0 ,
                       0.5 , 0.5 , 0.5 , 1.0 ) ;
void main(void)
{
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	DestinationColor = color;
	initFogNeedVar(_pos.xyz);
	float power = _WindDir.w;
	_WindDir.w = 0.0;
#ifdef USING_DIRECTIONAL_LIGHT	
	v_Pos = _e3d_lightMatProj * _e3d_lightMatView * _pos;
	v_Pos = biasMatrix* (v_Pos / v_Pos.w );
#endif
	vec3 dir =  normalize(_e3d_matModel*_WindDir).xyz;
	vec3 _vPos = position + dir * (sin(_Time + _e3d_matModel[3][2]) + 1.0) * power * pow(position.z / 100.0, 2.0); //摇动
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz, 2.0) * color;
    gl_Position = _e3d_getMVPMatrix() * vec4(_vPos ,1.0);
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif
#include "Fragment.shader"
uniform sampler2D myTexture0;

void main(void) 
{ 
	vec4 color = texture2D(myTexture0, v_coord);
	//float shadow = getShadowColor(v_Pos, 0.001);
	if(color.a < 0.3)
	{
		discard;
	}
	else
	{		
		gl_FragColor = mixFogColor( DestinationColor * color , vec4(1.0,1.0,1.0,1.0));
	}
}

#Framgent_End