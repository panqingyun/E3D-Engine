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
			_GL_ES_2::Enable(GL_DEPTH_TEST);
		}
		else
		{
			_GL_ES_2::Disable(GL_DEPTH_TEST);
		}
        //深度测试
        if(enablewriteDepth)
		{
			_GL_ES_2::DepthMask(GL_TRUE);
        }
        else
		{
			_GL_ES_2::DepthMask(GL_FALSE);
        }       

        if(enableDoubleSide)
        {
			_GL_ES_2::Disable(GL_CULL_FACE);
        }
        else
        {
			_GL_ES_2::Enable(GL_CULL_FACE);
        }		

		if (srcBlendFactor == GL_NONE || dstBlendFactor == GL_NONE)
		{
			_GL_ES_2::Disable(GL_BLEND);
		}
		else
		{
			_GL_ES_2::Enable(GL_BLEND);
			_GL_ES_2::BlendFunc(srcBlendFactor, dstBlendFactor);
		}
		_GL_ES_2::Enable(GL_ALPHA);

		_GL_ES_2::Enable(GL_STENCIL_TEST);
		_GL_ES_2::ColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        
        if(enableStencilTest)
        {
            enableStencil();
        }
    }

    void GLES_Material::enableStencil()
    {
        _GL_ES_2::DepthMask(GL_TRUE);//启用写入深度值
        _GL_ES_2::ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        _GL_ES_2::StencilFunc(GL_EQUAL, 1, 0xFF);
        _GL_ES_2::StencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        _GL_ES_2::StencilMask(0xFF);
    }


	void GLES_Material::InvalidMaterial()
	{
		UseNullProgram();
		_GL_ES_2::BindTexture(GL_TEXTURE_2D, 0);
	}


	void GLES_Material::UpdateShader(unsigned int vertexType)
	{
		static_cast<GLES_Shader*>(mShader)->UpdateAttribPointerValue(vertexType);
	}
}
