precision highp float;
varying lowp vec4 DestinationColor; // 1
varying lowp vec2 v_coord;
varying lowp float shaderIndex;
uniform sampler2D myTexture0;
void main(void) { // 2

	if (shaderIndex < 0.5)
	{
		gl_FragColor = texture2D(myTexture0, v_coord);
	}
	else if (shaderIndex < 1.5)
	{
		 gl_FragColor = texture2D(myTexture0, v_coord);
	}
	else if (shaderIndex < 2.5)
	{
		 vec4 color = texture2D(myTexture0, v_coord);
		color = color*DestinationColor;
		gl_FragColor = color;//vec4(DestinationColor.rgb, color.a); // 3
	}
	else if (shaderIndex < 3.5)
	{
		vec4 color = texture2D(myTexture0, v_coord);
		color.a = color.a * DestinationColor.a;
		gl_FragColor = vec4(DestinationColor.rgb, color.a);
	}
	//gl_FragColor = texture2D(myTexture0, v_coord);
}
