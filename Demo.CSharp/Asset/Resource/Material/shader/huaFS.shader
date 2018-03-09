precision highp float;
#include "Fragment.shader"
varying highp vec2 v_coord;
uniform sampler2D myTexture0;
varying vec4 DestinationColor;

void main(void) 
{ 
	gl_FragColor = mixFogColor(texture2D(myTexture0, v_coord) * DestinationColor);
}
