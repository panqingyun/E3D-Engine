#include "Standard.shader"

varying lowp vec2 v_coord;

void main(void)
{
    v_coord = inputTextureCoordinate;
	
    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
}
