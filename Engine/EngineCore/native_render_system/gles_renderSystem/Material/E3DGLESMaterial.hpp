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
		virtual void UseProgram();		
		virtual void UseNullProgram();
		virtual void InvalidMaterial();
		virtual void UpdateShader(unsigned int vertexType);

	protected:
		void enableStencil()override;
		virtual void openState();
		
	};
}

#endif /* Material_hpp */
