precision highp float;
varying highp vec4 DestinationColor; // 1
varying highp vec2 v_coord;
uniform sampler2D myTexture0;
void main(void) 
{ // 2
	gl_FragColor = DestinationColor * texture2D(myTexture0, v_coord);	
}
