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

varying vec4 v_Pos;

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
	v_Pos = _e3d_lightMatProj * _e3d_lightMatView * _pos;
	v_Pos = (v_Pos / v_Pos.w + 1.0) * 0.5;
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz) * color;
    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
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
varying vec4 v_Pos;
					   
void main(void) 
{
	vec4 color = texture2D(myTexture0, v_coord) * getShadowColor(v_Pos, 0.0005);	
	
	gl_FragColor = DestinationColor * vec4(color.rgb, 1.0);
}

#Framgent_End