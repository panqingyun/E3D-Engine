precision highp float;
#include "Fragment.shader"
varying highp vec2 v_coord;
uniform sampler2D myTexture0;
varying vec4 DestinationColor;

void main(void) 
{ 
	vec4 color = texture2D(myTexture0, v_coord);
	
	if(color.a < 0.1)
	{
		discard;
	}
	else
	{
		vec4 fogColor = mixFogColor(color,vec4(1.0,1.0,1.0,1.0));
		gl_FragColor = fogColor * DestinationColor;
	}
}
