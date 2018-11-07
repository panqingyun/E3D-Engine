#ifndef _GL_METRAIL_HPP_
#define _GL_METRAIL_HPP_

#include "../Shader/E3DGLShader.hpp"
#include "../Texture/E3DGLTexture2D.hpp"
#include <src/RenderSystem/Material/E3DMaterial.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{

	class GL_Material : public Material
	{
	public:
		GL_Material();
		virtual void UseMaterial();
		virtual void Destory();
		virtual void UseProgram();		
		virtual void UseNullProgram();
		virtual void InvalidMaterial();
		virtual void UpdateShader(unsigned int vertexType);

		void DisableVertexAttrib(unsigned int vertexType);
	public:

		virtual void CreateCubeTexture( std::string dirPath,std::string xPName,
									   std::string xNName,
									   std::string yPName,std::string yNName,std::string zPName,std::string ZNName);
	protected:
		void enableStencil()override;
		virtual void openState();
		
	};
}

#endif /* Material_hpp */
