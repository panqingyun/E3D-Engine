precision highp float;
varying highp vec2 v_coord;
uniform sampler2D myTexture0;
varying vec4 DestinationColor;
void main(void) 
{ 
	gl_FragColor = DestinationColor * texture2D(myTexture0, v_coord);	
}

