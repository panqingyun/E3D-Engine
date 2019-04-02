varying vec4 DestinationColor;
varying vec2 v_coord;
varying vec3 cameraRight;

#Vertex_Shader
#Attribute
{
	POSITION:position; 
	DYNAMICCOLOR:color;
	TEXTURECOORD:inputTextureCoordinate;
	TRANSPOSITION:transformPosition;
	TRANSSCALE:transformScale;
	TRANSROTATE:transformRotate;
	NORMAL:attr_normal;
	TANGENT:tangent;
}

#include "VertexShaderInc.glsl"
uniform float particleSize;

void main(void)
{
    v_coord = inputTextureCoordinate;
	// vec3 cameraRightInWorldspace = normalize(vec3(_e3d_matView[0][0], _e3d_matView[1][0], _e3d_matView[2][0]));
	// vec3 cameraUpInWorldspace = normalize(vec3(_e3d_matView[0][1], _e3d_matView[1][1], _e3d_matView[2][1]));
	
	// vec3 pos = transformPosition;
	// pos += cameraRightInWorldspace * particleSize * tangent.x;
	// pos += cameraUpInWorldspace * particleSize * tangent.y;
	
	mat4 transMatrix = getTransformMatrix(transformPosition, transformRotate,transformScale);
	vec4 _position = vec4(position.x, 0.0, position.y, 1.0);
	DestinationColor = getLightColor(_position.xyz, vec3(0.0,1.0,0.0), 10.0);
    gl_Position = _e3d_matProj * _e3d_matView * _e3d_matModel  * transMatrix * _position;//* BillboardMatrix();*  roateMatrix * scaleMat *
}

#End

#Framgent_Shader

#ifdef __GLES__
precision highp float;
#endif

uniform sampler2D myTexture0;
void main(void) 
{

	vec4 color = texture2D(myTexture0, v_coord);
	if(color.a < 0.3)
	{
		discard;
	}
	else
	{
		gl_FragColor = color * DestinationColor;
	}
}

#End