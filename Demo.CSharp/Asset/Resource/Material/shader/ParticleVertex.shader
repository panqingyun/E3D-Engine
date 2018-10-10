#include "Standard.shader"
varying vec4 DestinationColor;
varying lowp vec2 v_coord;
varying vec3 cameraRight;
uniform float particleSize;

void main(void)
{
    DestinationColor = color;
    v_coord = inputTextureCoordinate;
	vec3 cameraRightInWorldspace = normalize(vec3(_e3d_matView[0][0], _e3d_matView[1][0], _e3d_matView[2][0]));
	vec3 cameraUpInWorldspace = normalize(vec3(_e3d_matView[0][1], _e3d_matView[1][1], _e3d_matView[2][1]));
	
	vec3 pos = transformPosition;
	pos += cameraRightInWorldspace * particleSize * tangent.x;
	pos += cameraUpInWorldspace * particleSize * tangent.y;
	
	mat4 transMatrix = getTransformMatrix(pos, transformRotate,transformScale);
	
    gl_Position = _e3d_matProj * _e3d_matView * _e3d_matModel  * transMatrix * vec4(0.0,0.0,0.0,1.0);//* BillboardMatrix();* roateMatrix * scaleMat *
}
