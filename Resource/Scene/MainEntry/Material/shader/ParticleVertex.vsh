attribute vec3 position;
attribute vec4 color;
attribute vec2 inputTextureCoordinate;
attribute vec3 transformPosition;
attribute vec3 transformRotate;
attribute vec3 transformScale;
attribute float fShaderIndex;
varying vec4 DestinationColor;

varying lowp vec2 v_coord;
uniform vec3 worldCameraPosition;
uniform vec3 worldCameraUp;
varying float shaderIndex;
mat4 BillboardMatrix()
{
    vec3 forward = normalize(position - worldCameraPosition);
    vec3 side = cross( forward, worldCameraUp );
    
    mat4 result;
    result[0] = vec4( side, 0.0 );
    result[1] = vec4( worldCameraUp, 0.0 );
    result[2] = vec4( forward.x, 0.0, forward.z, 0.0 );
    result[3] = vec4( 0.0, 0.0, 0.0, 1.0 );
    return result;
}

void main(void)
{
    DestinationColor = color;
    v_coord = inputTextureCoordinate;
	mat4 transform	= mat4(1.0,					0.0,					0.0,					0.0,
						   0.0,					1.0,					0.0,					0.0,
						   0.0,					0.0,					1.0,					0.0,
						   transformPosition.x,	transformPosition.y,	transformPosition.z,	1.0);
	
	mat4 roateMatX	= mat4(1.0, 0.0,						0.0,					0.0,
						   0.0, cos(transformRotate.x),	sin(transformRotate.x),		0.0,
						   0.0, -sin(transformRotate.x),	cos(transformRotate.x),	0.0,
						   0.0, 0.0,						0.0, 1.0);
	
	mat4 roateMatY	= mat4(cos(transformRotate.y),	0.0, -sin(transformRotate.y),	0.0,
						   0.0,						1.0, 0.0,						0.0,
						   sin(transformRotate.y),	0.0, cos(transformRotate.y),	0.0,
						   0.0,						0.0, 0.0,						1.0);
	
	mat4 roateMatZ	= mat4(cos(transformRotate.z) ,	sin(transformRotate.z),	0.0, 0.0,
						   -sin(transformRotate.z),	cos(transformRotate.z),	0.0, 0.0,
						   0.0,						0.0,					1.0, 0.0,
						   0.0,						0.0,					0.0, 1.0);
	mat4 scaleMat	= mat4(transformScale.x	, 0.0			  ,		0.0				,	0.0,
						   0.0				, transformScale.y,		0.0				,	0.0,
						   0.0				, 0.0			  ,		transformScale.z,	0.0,
						   0.0				, 0.0			  ,		0.0				,	1.0
						   );
	
	mat4 roateMatrix = roateMatX * roateMatY * roateMatZ;
	
	shaderIndex = fShaderIndex;
	vec4 interpolatedPosition = transform * roateMatrix * scaleMat * vec4(position ,1.0);
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
