precision highp float;
varying lowp vec2 v_coord;
uniform sampler2D myTexture0;
void main(void) 
{ 
	gl_FragColor = texture2D(myTexture0, v_coord);	
}
