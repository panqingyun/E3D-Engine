
varying vec4 DestinationColor; // 1
varying  vec3 vPosition;
varying vec3 mCameraPos;

void main(void) 
{ 
	// 虚化远处的网格
	float dist = abs(distance(mCameraPos, vPosition));
	float maxDist = 800.0;
	float minDist = 1.0;
    float factor = (maxDist - dist) / (maxDist - minDist);  
    factor = clamp( factor, 0.0, 1.0 );  
	
    vec4 mColor = mix( vec4(0.0,0.0,0.0,0.5), DestinationColor, factor );  
	gl_FragColor = mColor;
}
