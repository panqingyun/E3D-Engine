precision highp float;
varying   highp vec2 v_Texcoord;
uniform   lowp  sampler2D SamplerRGB;

void main()
{
	gl_FragColor = texture2D(SamplerRGB, v_Texcoord);
}