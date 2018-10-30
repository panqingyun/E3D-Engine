#include "E3DGLMaterial.hpp"
#include "..\Texture\E3DGLCubeMapTexture.hpp"

namespace E3DEngine
{
	GL_Material::GL_Material()
	{
		
	}

	void GL_Material::Destory()
	{
		for (std::map<UINT, Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		SAFE_DELETE(mShader);
		Textures.clear();
	}

	void GL_Material::SetTexture(Texture * texture, int index)
	{
		if (Textures.find(index) != Textures.end() && texture != Textures[index])
		{
			SAFE_DELETE(Textures[index]);
		}
		else
		{
			index = Textures.size();
		}
		Textures[index] = texture;
		texture->SetTextureEnum(index + GL_TEXTURE0);
		texture->SetTextureUniformIndex(index, static_cast<GL_Shader*>(mShader)->ShaderProgram);
		
	}

	void GL_Material::createTexture2D(TextureData& data)
	{
		GL_Texture2D * texture = new GL_Texture2D();
		std::string path = mFilePath;
		path = path + data.fileName;
		int textureSum = Textures.size();
		texture->Create(path, data);
		texture->SetTextureEnum(GL_TEXTURE0 + textureSum);
		texture->SetTextureUniformName(data.uniformName);
		texture->SetTextureUniformIndex(textureSum, static_cast<GL_Shader*>(mShader)->ShaderProgram);
		Textures[textureSum] = ((E3DEngine::Texture*)texture);
	}

	void GL_Material::createTexture(Texture *texture, std::string textureUniform)
	{
		int textureSum = Textures.size();
		texture->SetTextureEnum(GL_TEXTURE0 + textureSum);
		texture->SetTextureUniformName(textureUniform);
		texture->SetTextureUniformIndex(textureSum, static_cast<GL_Shader*>(mShader)->ShaderProgram);
		Textures[textureSum] = ((E3DEngine::Texture*)texture);
	}


	void GL_Material::createCubeTexture(std::string filePath,int selectID, std::string uniformName)
	{
		GL_CubeMapTexture * texture = new GL_CubeMapTexture;
		texture->Create(filePath, selectID);
		int textureSum = Textures.size();
		texture->SetTextureEnum(GL_TEXTURE0 + textureSum);
		texture->SetTextureUniformName(uniformName);
		texture->SetTextureUniformIndex(textureSum, static_cast<GL_Shader*>(mShader)->ShaderProgram);
		Textures[textureSum] = ((E3DEngine::Texture*)texture);
	}

	void GL_Material::BindTexture()
	{
		for (auto & it : Textures)
		{
			if (it.second == nullptr)
			{
				continue;
			}
			it.second->ActiveBindTexture();
		}
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

	void GL_Material::CreateCubeTexture(std::string dirPath, std::string xPName, std::string xNName, std::string yPName, std::string yNName, std::string zPName, std::string ZNName)
	{

	}

	void GL_Material::UseMaterial()
	{
		UseProgram();
		openState();
		for(auto & it : Textures)
		{
			if (it.second == nullptr)
			{
				continue;
			}
			it.second->ActiveBindTexture();
		}
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
			glEnable(GL_BLEND);
			glBlendFunc(srcBlendFactor, dstBlendFactor);
		}
		glEnable(GL_ALPHA);

        glEnable(GL_STENCIL_TEST);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        
        if(enableStencilTest)
        {
            enableStencil();
        }
    }

    void GL_Material::enableStencil()
    {
        glDepthMask(GL_TRUE);//启用写入深度值
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);
    }


	void GL_Material::InvalidMaterial()
	{
		for (auto & it : Textures)
		{
			if (it.second == nullptr)
			{
				continue;
			}
			it.second->InvalidTexture();
		}
		UseNullProgram();
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void GL_Material::UpdateShader(unsigned int vertexType)
	{
		static_cast<GL_Shader*>(mShader)->UpdateAttribPointerValue(vertexType);
	}
}
