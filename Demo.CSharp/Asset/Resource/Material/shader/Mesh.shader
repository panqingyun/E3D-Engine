varying vec2 v_coord0;
varying vec4 DestinationColor;
varying vec4 v_Pos;
#Vertex_Begin

#Attribute
{
	POSITION:position; 
	COLOR:color;
	TEXTURECOORD0:uv0; 
	NORMAL:attr_normal;
}

#include "Standard.shader"
const  mat4 biasMatrix = mat4(0.5 , 0.0 , 0.0 , 0.0 ,
                       0.0 , 0.5 , 0.0 , 0.0 ,
                       0.0 , 0.0 , 0.5 , 0.0 ,
                       0.5 , 0.5 , 0.5 , 1.0 ) ;

void main(void)
{
    v_coord0 = uv0;
	vec4 interpolatedPosition = vec4(position ,1.0);	
	
	mat4 rotateMatrix = getRotateMatrix();
	vec4 _normal = vec4(attr_normal.xyz, 1.0);
	
	vec4 _pos = _e3d_matModel * interpolatedPosition;
	initFogNeedVar(position);
	DestinationColor = color * 2.0;//getLightColor(_pos.xyz, _normal.xyz, 10.0) * color;
#ifdef USING_DIRECTIONAL_LIGHT
	v_Pos = _e3d_lightMatProj * _e3d_lightMatView * _pos;
	v_Pos = biasMatrix* (v_Pos / v_Pos.w );
#endif
    gl_Position = _e3d_getMVPMatrix() * vec4(position ,1.0);
}

#Vertex_End

#Framgent_Begin

#ifdef __GLES__
precision highp float;
#endif

#include "Fragment.shader"
uniform sampler2D _Splat0;
uniform sampler2D _Splat1;
uniform sampler2D _Splat2;
uniform sampler2D _Splat3;
uniform sampler2D _Control;

const float tiling0 = 35.6;
const float tiling1 = 25.0;
const float tiling2 = 20.0;
const float tiling3 = 20.0;

const float _HaveAlphaL0 = 1.0;
const float _HaveAlphaL1 = 0.0;
const float _HaveAlphaL2 = 0.0;
const float _HaveAlphaL3 = 0.0;

const float _ShininessL0 = 0.2898214;
const float _ShininessL1 = 0.078125;
const float _ShininessL2 = 0.078125;
const float _ShininessL3 = 0.078125;

void main(void) 
{ 
	float scale = 1.0;
   // vec4 _SpecColor = vec4(0.5,0.5,0.5,0.0);
	vec2 v_0 = vec2(v_coord0.x * scale * tiling0, v_coord0.y * scale * tiling0);
	vec2 v_1 = vec2(v_coord0.x * 5.0 * tiling1, v_coord0.y * 5.0 * tiling1);
	vec2 v_2 = vec2(v_coord0.x * scale * tiling2, v_coord0.y * scale * tiling2);
	vec2 v_3 = vec2(v_coord0.x * scale * tiling3, v_coord0.y * scale * tiling3);
	
	vec4 _Control_var = texture2D(_Control,v_coord0 );
	vec4 _Splat0_var = texture2D(_Splat0,v_0 );
	vec4 _Splat1_var = texture2D(_Splat1,v_1 );
	vec4 _Splat2_var = texture2D(_Splat2,v_2 );
	vec4 _Splat3_var = texture2D(_Splat3,v_3 );
	
	vec4 f_c = ((_Control_var.r*_Splat0_var) + (_Control_var.g*_Splat1_var) + (_Control_var.b*_Splat2_var) + (_Control_var.a*_Splat3_var));
	// float f_g = (_HaveAlphaL0 * _Control_var.r * _Splat0_var.a) + (_HaveAlphaL1 * _Control_var.g * _Splat1_var.a) + (_HaveAlphaL2 * _Control_var.b * _Splat2_var.a) + (_HaveAlphaL3 * _Control_var.a * _Splat3_var.a);
	// float f_s = _ShininessL0 * _Control_var.r + _ShininessL1 * _Control_var.g + _ShininessL2 * _Control_var.b + _ShininessL3 * _Control_var.a;
	// float nh = 1.0;
	// float spec = max(0.0, pow(nh, f_s * 128.0)) * f_g;
	// vec4 fs = ((f_c * _SpecColor.w) + (_SpecColor * spec)) * 2.0;
	// vec4 fc = fs + f_c ;
	
	float shadowColor = getShadowColor(v_Pos, 0.001);
	
	vec4 finalColor = mixFogColor(f_c,vec4(1.0,1.0,1.0,1.0)) * shadowColor;
	gl_FragColor = vec4(finalColor.rgb, 1.0) * DestinationColor;
}

#Framgent_End