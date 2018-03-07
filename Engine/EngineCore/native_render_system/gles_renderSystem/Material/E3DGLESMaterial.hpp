//
//  Material.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef _GLES_METRAIL_HPP_
#define _GLES_METRAIL_HPP_

#include "../Shader/E3DGLESShader.hpp"
#include "../Texture/E3DGLESTexture.hpp"
#include "../Texture/E3DGLESCubeMapTexture.hpp"
#include <src/Config/Table.h>
#include <src/Source/E3DDebug.h>
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
		virtual void SetTexture(Texture * texture, int index);
		virtual void BindTexture();
		virtual void UseProgram();		
		virtual void UseNullProgram();
		virtual void InvalidMaterial();
	public:
		virtual void CreateShader(ShaderConfig *cfg)
		{
			pShader = new GLES_Shader;
			pShader->SetFileRelativeFolder(filePath);
			static_cast<GLES_Shader*>(pShader)->InitShaderVar();
			static_cast<GLES_Shader*>(pShader)->LoadShader(cfg);
		}
		virtual void CreateCubeTexture( std::string dirPath,std::string xPName,
									   std::string xNName,
									   std::string yPName,std::string yNName,std::string zPName,std::string ZNName);
	protected:
		void enableStencil()override;
		virtual void openState();
		virtual void createTexture(TextureData& data)override;
		virtual void createTexture(Texture *texture, std::string textureUniform)override;
		
	};
}

#endif /* Material_hpp */
