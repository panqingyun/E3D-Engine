#include "Standard.shader"
varying vec4 DestinationColor;
varying lowp vec2 v_coord;
uniform vec3 worldCameraPosition;
uniform vec3 worldCameraUp;
varying float shaderIndex;


void main(void)
{
    DestinationColor = color;
    v_coord = inputTextureCoordinate;
	
	shaderIndex = fShaderIndex;
	vec4 interpolatedPosition = getTransformMatrix(transformPosition,transformRotate,transformScale) * vec4(position ,1.0);
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
