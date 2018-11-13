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
varying vec2 v_coord;
void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	DestinationColor = color;
	initFogNeedVar(position);
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;
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
	gl_FragColor = mixFogColor(texture2D(myTexture0, v_coord) * DestinationColor, vec4(1.0,1.0,1.0,1.0));	
}

#Framgent_End