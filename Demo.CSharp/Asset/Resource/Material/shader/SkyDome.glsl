varying vec4 DestinationColor;
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
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz) * color;
	
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;
}

#End

#Framgent_Shader
#ifdef __GLES__
precision highp float;
#endif
uniform sampler2D myTexture0;
void main(void) 
{ 
	gl_FragColor = texture2D(myTexture0, v_coord);	
}

#End