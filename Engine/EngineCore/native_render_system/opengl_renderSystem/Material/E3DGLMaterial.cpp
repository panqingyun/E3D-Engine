#include "E3DGLMaterial.hpp"
#include "..\Texture\E3DGLCubeMapTexture.hpp"

namespace E3DEngine
{
	GL_Material::GL_Material()
	{
		
	}

	void GL_Material::Destory()
	{
		SAFE_DELETE(mShader);
	}

	void GL_Material::UseProgram()
	{
		if (mShader == nullptr)
			return;
		static_cast<GL_Shader*>(mShader)->UseProgram();
	}

	void GL_Material::UseNullProgram()
	{
		if (mShader == nullptr)
			return;
		static_cast<GL_Shader*>(mShader)->UseNullProgram();
	}

	void GL_Material::UseMaterial()
	{
		UseProgram(); 
		openState();
		if (mShader != nullptr)
		{
			static_cast<GL_Shader*>(mShader)->UpdateProgramUniformValue();
		}
	}

    void GL_Material::openState()
	{
		if (enableDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
        //深度测试
        if(enablewriteDepth)
		{
			glDepthMask(GL_TRUE);
        }
        else
		{
			glDepthMask(GL_FALSE);
        }       

        if(enableDoubleSide)
        {
            glDisable(GL_CULL_FACE);
        }
        else
        {
			glEnable(GL_CULL_FACE);
        }		

		if (srcBlendFactor == GL_NONE || dstBlendFactor == GL_NONE)
		{
			glDisable(GL_BLEND);
		}
		else
		{
			glEnable(GL_ALPHA);
			glEnable(GL_BLEND);
			glBlendFunc(srcBlendFactor, dstBlendFactor);
		}
		        
        if(enableStencilTest)
		{
			glEnable(GL_STENCIL_TEST);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            enableStencil();
        }
    }

    void GL_Material::enableStencil()
    {
        glDepthMask(GL_TRUE);//启用写入深度值
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_GEQUAL, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);
    }


	void GL_Material::InvalidMaterial()
	{
		UseNullProgram();
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void GL_Material::UpdateShader(unsigned int vertexType)
	{
		static_cast<GL_Shader*>(mShader)->UpdateAttribPointerValue(vertexType);
	}

	void GL_Material::SetRenderState()
	{
		
	}

	void GL_Material::DisableVertexAttrib(unsigned int vertexType)
	{
		static_cast<GL_Shader*>(mShader)->DisableVertexAttribArray(vertexType);
	}

}
