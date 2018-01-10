
varying vec4 DestinationColor;

void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);
	
	DestinationColor = _e3d_getLightColor() * color;
	
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
