#include "Standard.shader"

varying lowp vec2 v_coord;


void main(void)
{
    v_coord = inputTextureCoordinate;
	// vec4 interpolatedPosition = vec4(position ,1.0);	
	// vec4 _pos = _e3d_matModel * interpolatedPosition;
	// mat4 rotateMatrix = getRotateMatrix();
	// vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	// DestinationColor = getLightColor(_pos.xyz, _normal.xyz);
    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
}
