#include "Standard.shader"

varying vec2 v_coord;
varying vec4 DestinationColor;

void main(void)
{
    v_coord = inputTextureCoordinate;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	v_coord = inputTextureCoordinate;
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz);
	initFogNeedVar(position);
    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
}
