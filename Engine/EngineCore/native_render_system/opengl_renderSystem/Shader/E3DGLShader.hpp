//
//  Shader.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef GLES_Shader_hpp
#define GLES_Shader_hpp

#include <src/RenderSystem/Shader/E3DShader.hpp>
#include "../Include/Include.h"

#define IF_AVAILABLE(value) if((int)value != -1)

namespace E3DEngine
{
	enum
	{
		LOCATION_ATTRIB_VERTEX,
		LOCATION_ATTRIB_COLOR,
		LOCATION_ATTRIB_NORMAL,
		LOCATION_ATTRIB_TEXTURE0,
		LOCATION_ATTRIB_TEXTURE1,
		LOCATION_ATTRIB_TEXTURE2,
		LOCATION_ATTRIB_TEXTURE3,
		LOCATION_ATTRIB_TEXTURE4,
		LOCATION_ATTRIB_TEXTURE5,
		LOCATION_ATTRIB_TEXTURE6,
		LOCATION_ATTRIB_TEXTURE7,
		LOCATION_ATTRIB_TANGENT,
		LOCATION_ATTRIB_BONES_INDICES,
		LOCATION_ATTRIB_BONES_WEIGHTS,
		LOCATION_ATTRIB_TRANSFORM_POSITION,
		LOCATION_ATTRIB_TRANSFORM_SCALE,
		LOCATION_ATTRIB_TRANSFORM_ROTETION,
		LOCATION_ATTRIB_DYNAMIC_COLOR,
		LOCATION_ATTRIB_FRAGMENT_INDEX,

	};

	struct Attribute
	{
		std::string  AttribType;		// 如 vec3
		std::string  TypeName;			// 语义 如 POSITION 代表这个属性是用来做什么的
		std::string  VarName;			// Shader里面的变量名
		uint		 AttributeLoaction;		// 变量的位置，使用glGetAttribLocation获取到的值
		int			 StartPosition;		// 在顶点数据结构中的起始位置
		uint		 VarType;			// 数据类型，如 GL_FLOAT
		uint		 Normalized;		// 是否归一化
		uint		 VertexStructSize;	// 顶点结构大小
		uint		 AttributeSize;		// 该属性的大小
		uint		 BindLocation;		// 绑定到Shader中的位置
	};

	class GLES_Shader : public Shader
	{
	public:
		GLES_Shader()
		{

		}
		virtual ~GLES_Shader();
	public:
		GLuint			ShaderProgram;

	public:
		virtual GLint	LoadSelfDefUniform(std::string name);
		virtual GLuint	LoadSelfDefAttribuate(std::string name);

		virtual void	UpdateProgramUniformValue();
		virtual void	LoadShader(const char* vertexShader, const char * fragmentShader);
		virtual void	UseProgram();
		virtual void	UseNullProgram();
		virtual void    SetProgramUniform(){ }
		virtual void	DeleteShader();
		virtual void	UpdateAttribPointerValue(UINT vertexType);
		virtual void	EnableVertexAttribArray(UINT vertexType);
		virtual void	InitShaderVar();

		void AddAttriList(Attribute attri, bool isStatic);
		
	private:
		int location;
	protected:
		virtual GLuint	compileShader(const char*  shaderName, GLenum shaderType);
		virtual void	compileShaders();
		virtual void	loadAttribLocation(UINT vertexType);
		virtual void	loadUniformLocation();
		virtual void	bindAttribLoaction(UINT vertexType);

	protected:
		std::vector<Attribute> staticAttributeList;
		std::vector<Attribute> dynamicAttributeList;
	};
}

#endif /* Shader_hpp */
