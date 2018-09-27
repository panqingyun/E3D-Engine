#include "Standard.shader"

varying highp vec3 vPosition;
varying highp vec3 mCameraPos;
varying vec4 DestinationColor;

void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	DestinationColor = color;
	vPosition = (_e3d_matModel * vec4(position ,1.0)).xyz;
	
	mCameraPos = _e3d_CameraPos;
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
