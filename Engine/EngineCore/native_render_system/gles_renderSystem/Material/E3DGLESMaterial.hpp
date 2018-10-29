//
//  Material.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef _GLES_METRAIL_HPP_
#define _GLES_METRAIL_HPP_

#include "../Shader/E3DGLESShader.hpp"
#include "../Texture/E3DGLESTexture2D.hpp"
#include <src/RenderSystem/Material/E3DMaterial.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{

	class GLES_Material : public Material
	{
	public:
		GLES_Material();
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
