precision highp float;
#include "Fragment.shader"
varying highp vec2 v_coord;
uniform sampler2D myTexture0;
varying vec4 DestinationColor;

void main(void) 
{ 
	vec4 color = mixFogColor(texture2D(myTexture0, v_coord) * DestinationColor,vec4(1.0,1.0,1.0,1.0));
	
	if(color.a < 0.1)
	{
		discard;
	}
	else
	{
		gl_FragColor = color;
	}
}
