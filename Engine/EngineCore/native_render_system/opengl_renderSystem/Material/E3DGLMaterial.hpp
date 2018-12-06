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
		virtual void SetRenderState() override;
		void DisableVertexAttrib(unsigned int vertexType);
		virtual void SetTexture(Texture * texture, int index = 0) override { }
	protected:
		void enableStencil();
		void openState();
		
	};
}

#endif /* Material_hpp */
