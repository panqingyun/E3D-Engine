precision highp float;
varying lowp vec4 DestinationColor; // 1
void main(void) 
{ // 2
	gl_FragColor = DestinationColor;
}
