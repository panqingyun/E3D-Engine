#Vertex_Begin

#Attribute
{
	POSITION:position;
	COLOR:color;
	NORMAL:attr_normal;
}

#include "Standard.shader"

varying vec3 vPosition;
varying vec3 mCameraPos;
varying vec4 DestinationColor;

void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = rotateMatrix * vec4(attr_normal.xyz, 1.0);
	DestinationColor = color;
	vPosition = (_e3d_matModel * vec4(position ,1.0)).xyz;
	
	mCameraPos = _e3d_CameraPos;
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif
varying vec4 DestinationColor; // 1
varying vec3 vPosition;
varying vec3 mCameraPos;

void main(void) 
{ 
	// 虚化远处的网格
	float dist = abs(distance(mCameraPos, vPosition));
	float maxDist = 800.0;
	float minDist = 1.0;
    float factor = (maxDist - dist) / (maxDist - minDist);  
    factor = clamp( factor, 0.0, 1.0 );  
	
    vec4 mColor = mix( vec4(0.0,0.0,0.0,0.0), DestinationColor, factor );  
	gl_FragColor = mColor;
}

#Framgent_End