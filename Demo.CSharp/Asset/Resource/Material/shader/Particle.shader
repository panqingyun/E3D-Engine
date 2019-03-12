varying vec4 DestinationColor;
varying vec2 v_coord;
varying vec3 cameraRight;

#Vertex_Begin

#Attribute
{
	DYNAMICCOLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	TRANSPOSITION:transformPosition;
	TRANSSCALE:transformScale;
	TRANSROTATE:transformRotate;
	TANGENT:tangent;
}

#include "Standard.shader"
uniform float particleSize;

void main(void)
{
    DestinationColor = color;
    v_coord = inputTextureCoordinate;
	vec3 cameraRightInWorldspace = normalize(vec3(_e3d_matView[0][0], _e3d_matView[1][0], _e3d_matView[2][0]));
	vec3 cameraUpInWorldspace = normalize(vec3(_e3d_matView[0][1], _e3d_matView[1][1], _e3d_matView[2][1]));
	
	vec3 pos = transformPosition;
	pos += cameraRightInWorldspace * particleSize * tangent.x;
	pos += cameraUpInWorldspace * particleSize  * tangent.y;
	
	mat4 transMatrix = getTransformMatrix(pos, transformRotate,transformScale);
	
    gl_Position = _e3d_matProj * _e3d_matView * _e3d_matModel  * transMatrix * vec4(0.0,0.0,0.0,1.0);//* BillboardMatrix();*  roateMatrix * scaleMat *
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif

uniform sampler2D myTexture0;
void main(void) 
{

	vec4 color = texture2D(myTexture0, v_coord);
	color.a = color.a * DestinationColor.a;
	gl_FragColor = vec4(DestinationColor.rgb, color.a);
	
}

#Framgent_End