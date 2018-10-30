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
		virtual void SetTexture(Texture * texture, int index = 0);
		virtual void BindTexture();
		virtual void UseProgram();		
		virtual void UseNullProgram();
		virtual void InvalidMaterial();
		virtual void UpdateShader(unsigned int vertexType);
	public:

		virtual void CreateCubeTexture( std::string dirPath,std::string xPName,
									   std::string xNName,
									   std::string yPName,std::string yNName,std::string zPName,std::string ZNName);
	protected:
		void enableStencil()override;
		virtual void openState();
		virtual void createTexture2D(TextureData& data) override;
		virtual void createTexture(Texture *texture, std::string textureUniform) override;
		virtual void createCubeTexture(std::string filePath, int selectID, std::string uniformName) override;
		
	};
}

#endif /* Material_hpp */
