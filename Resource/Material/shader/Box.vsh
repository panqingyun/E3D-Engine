varying vec4 DestinationColor;

void main(void)
{	
	mat4 transMatrix	= mat4(1.0,				0.0,					0.0,					0.0,
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
	mat4 scaleMatatrix	= mat4(transformScale.x	, 0.0			  ,		0.0				,	0.0,
								0.0				, transformScale.y,		0.0				,	0.0,
								0.0				, 0.0			  ,		transformScale.z,	0.0,
								0.0				, 0.0			  ,		0.0				,	1.0
							);
	
	mat4 roateMatrix = roateMatX * roateMatY * roateMatZ;	
	vec4 interpolatedPosition = transMatrix * roateMatrix * scaleMatatrix * vec4(position ,1.0);
	
	DestinationColor = _e3d_getLightColor() * color;
	//------------------------------------------------------------------
	
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
