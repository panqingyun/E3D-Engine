//
//  Material.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DGLESMaterial.hpp"
#include "..\Texture\E3DGLESCubeMapTexture.hpp"

namespace E3DEngine
{

	GLES_Material::GLES_Material()
	{
		
	}

	void GLES_Material::Destory()
	{
		SAFE_DELETE(mShader);
	}

	void GLES_Material::UseProgram()
	{
		if (mShader == nullptr)
			return;
		static_cast<GLES_Shader*>(mShader)->UseProgram();
	}

	void GLES_Material::UseNullProgram()
	{
		if (mShader == nullptr)
			return;
		static_cast<GLES_Shader*>(mShader)->UseNullProgram();
	}

	void GLES_Material::UseMaterial()
	{
		UseProgram();
		openState();
		if (mShader != nullptr)
		{
			static_cast<GLES_Shader*>(mShader)->UpdateProgramUniformValue();
		}
	}

    void GLES_Material::openState()
	{
		if (enableDepthTest)
		{
			ES2::Enable(GL_DEPTH_TEST);
		}
		else
		{
			ES2::Disable(GL_DEPTH_TEST);
		}
        //深度测试
        if(enablewriteDepth)
		{
			ES2::DepthMask(GL_TRUE);
        }
        else
		{
			ES2::DepthMask(GL_FALSE);
        }       

        if(enableDoubleSide)
        {
			ES2::Disable(GL_CULL_FACE);
        }
        else
        {
			ES2::Enable(GL_CULL_FACE);
        }		

		if (srcBlendFactor == GL_NONE || dstBlendFactor == GL_NONE)
		{
			ES2::Disable(GL_BLEND);
		}
		else
		{
			ES2::Enable(GL_BLEND);
			ES2::BlendFunc(srcBlendFactor, dstBlendFactor);
		}
		ES2::Enable(GL_ALPHA);

		ES2::Enable(GL_STENCIL_TEST);
		ES2::ColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        
        if(enableStencilTest)
        {
            enableStencil();
        }
    }

    void GLES_Material::enableStencil()
    {
        ES2::DepthMask(GL_TRUE);//启用写入深度值
        ES2::ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        ES2::StencilFunc(GL_EQUAL, 1, 0xFF);
        ES2::StencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        ES2::StencilMask(0xFF);
    }


	void GLES_Material::InvalidMaterial()
	{
		UseNullProgram();
		ES2::BindTexture(GL_TEXTURE_2D, 0);
	}


	void GLES_Material::UpdateShader(unsigned int vertexType)
	{
		static_cast<GLES_Shader*>(mShader)->UpdateAttribPointerValue(vertexType);
	}
}
