#include "Standard.shader"

varying highp vec2 v_coord0;
varying vec4 DestinationColor;

void main(void)
{
    v_coord0 = uv0;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	initFogNeedVar(position);
	DestinationColor = getLightColor(_pos.xyz, _normal.xyz) * color;

    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
}
