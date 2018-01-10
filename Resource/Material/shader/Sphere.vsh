attribute vec3 position;
attribute vec4 color;
attribute vec3 attr_normal;
varying vec4 DestinationColor;

vec3 lightposition;//光源位置
vec4 ambient;//环境光颜色
vec4 lightcolor;//光源颜色
float Ns;//高光系数
float attenuation;//光线的衰减系数

void main(void)
{	
	vec4 interpolatedPosition = vec4(position ,1.0);
	
	//--------------------------------------------------------------
	//--- 光照
	lightposition = vec3(50.0,50.0,50.0);
	ambient = vec4(0.5,0.5,0.5, 1.0);
	lightcolor = vec4(1.0,1.0,1.0,1.0);  
	Ns = 10.0;
	attenuation = 0.1;
	// _e3d_cameraPos 引擎保留字段，自动生成的代码里面会拼接好这一变量，用于表示看到这个物体的摄像机的位置
	// 其他自动生成的变量还有 
	// _e3d_matModel 表示世界矩阵（对于合批的物体这一矩阵始终是单位矩阵，此时物体的世界矩阵可以由 transMatrix * roateMatrix * scaleMatatrix 表示）
	// _e3d_matProj表示投影矩阵 _e3d_matView 表示视图矩阵，这些变量都可以直接使用
	vec3 N = normalize((vec4(attr_normal, 1.0)).xyz);
	vec3 L = normalize(lightposition - interpolatedPosition.xyz);
	vec3 V = normalize(_e3d_cameraPos - interpolatedPosition.xyz);
	vec3 H = normalize(V + L);
	vec3 diffuse = vec3((lightcolor * max(dot(N , L) , 0.0)).xyz);
	vec3 specular = vec3((lightcolor * pow(max(dot(N , H) , 0.0) , Ns) * attenuation).xyz);
	DestinationColor = vec4(clamp((diffuse + specular) , 0.0 , 1.0) , 1.0);
	DestinationColor = (DestinationColor + ambient) * color;
	//------------------------------------------------------------------
	
    gl_Position = _e3d_getMVPMatrix() * interpolatedPosition;//* BillboardMatrix();* roateMatrix * scaleMat *
}
