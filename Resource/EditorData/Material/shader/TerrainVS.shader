#include "Standard.shader"
varying lowp vec2 v_coord;
varying vec4 DestinationColor;
void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getTransformRotateMatrix(_e3d_Rotation);
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	DestinationColor = getLightColor(position, _normal.xyz) * color;
	v_coord = inputTextureCoordinate;
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
