precision highp float;
varying lowp vec4 DestinationColor; 
varying lowp vec2 v_coord;

varying vec3 cameraRight;
uniform sampler2D myTexture0;
void main(void) 
{

	vec4 color = texture2D(myTexture0, v_coord);
	color.a = color.a * DestinationColor.a;
	gl_FragColor = vec4(DestinationColor.rgb, color.a);
	
}
