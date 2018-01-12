
varying lowp vec2 v_Texcoord;

void main()
{
	v_Texcoord = inputTextureCoordinate;
	gl_Position = _e3d_getMVPMatrix() * vec4(position, 1.0);
}