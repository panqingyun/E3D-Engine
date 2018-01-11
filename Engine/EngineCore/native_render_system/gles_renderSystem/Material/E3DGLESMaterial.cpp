//
//  Material.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DGLESMaterial.hpp"
#include <src/Source/Application.h>
#include <3rd/header/FilePath.h>
#include <src/Source/E3DVertex.h>
#include <3rd/header/Helpers.h>

namespace E3DEngine
{
	const char * lightShader = "";

	GLES_Material::GLES_Material()
	{
		
	}

	void GLES_Material::Destory()
	{
		for (std::map<UINT, Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		SAFE_DELETE(pShader);
		Textures.clear();
	}

	void GLES_Material::SetTexture(Texture * texture, int index)
	{
		UINT textureIndex = GL_TEXTURE0 + index;
		std::map<UINT, Texture*>::iterator it = Textures.find(index);
		if (it != Textures.end())
		{
			static_cast<GLES_Texture*>(texture)->SetTextureUniformName(static_cast<GLES_Texture*>(it->second)->m_strTextureUniformName);
			SAFE_DELETE(it->second);
			Textures[index] = texture;
			static_cast<GLES_Texture*>(texture)->SetTextureEnum(textureIndex);
			static_cast<GLES_Texture*>(texture)->SetTextureUniformLocation(index, static_cast<GLES_Shader*>(pShader)->ShaderProgram);
		}
	}

	void GLES_Material::createTexture(std::string textureName, std::string textureUniform)
	{
		GLES_Texture * texture = new GLES_Texture();
		std::string path = Application::AppDataPath + "/" + filePath;
		path = path + textureName;
		int textureSum = Textures.size();
		texture->Create(path);
		texture->SetTextureEnum(GL_TEXTURE0 + textureSum);
		texture->SetTextureUniformName(textureUniform);
		texture->SetTextureUniformLocation(textureSum, static_cast<GLES_Shader*>(pShader)->ShaderProgram);
		Textures[textureSum] = ((E3DEngine::Texture*)texture);
	}

	void GLES_Material::createTexture(Texture *texture, std::string textureUniform)
	{
		int textureSum = Textures.size();
		texture->SetTextureEnum(GL_TEXTURE0 + textureSum);
		static_cast<GLES_Texture*>(texture)->SetTextureUniformName(textureUniform);
		static_cast<GLES_Texture*>(texture)->SetTextureUniformLocation(textureSum, static_cast<GLES_Shader*>(pShader)->ShaderProgram);
		Textures[textureSum] = ((E3DEngine::Texture*)texture);
	}

	void GLES_Material::BindTexture()
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

	void GLES_Material::UseProgram()
	{
		if (pShader == nullptr)
			return;
		static_cast<GLES_Shader*>(pShader)->UseProgram();
	}

	void GLES_Material::UseNullProgram()
	{
		if (pShader == nullptr)
			return;
		static_cast<GLES_Shader*>(pShader)->UseNullProgram();
	}

	void GLES_Material::CreateCubeTexture(std::string dirPath, std::string xPName, std::string xNName, std::string yPName, std::string yNName, std::string zPName, std::string ZNName)
	{

	}

	void GLES_Material::UseMaterial()
	{
		UseProgram();
		for(auto & it : Textures)
		{
			if (it.second == nullptr)
			{
				continue;
			}
			it.second->ActiveBindTexture();
		}
		if (pShader != nullptr)
		{
			static_cast<GLES_Shader*>(pShader)->UpdateProgramUniformValue();
			static_cast<GLES_Shader*>(pShader)->UpdateAttribPointerValue();
		}
	}

    void GLES_Material::beforeUpdate()
    {
  //      //深度测试
  //      if(enableDepthTest)
  //      {
  //          glEnable(GL_DEPTH_TEST);
  //      }
  //      else
  //      {
  //          glDisable(GL_DEPTH_TEST);
  //      }
  //      
  //      
  //      if(enablewriteDepth)
  //      {
  //          glDepthMask(GL_TRUE);
  //      }
  //      else
  //      {
  //          glDepthMask(GL_FALSE);
  //      }
  //      
  //      
  //      if(enableDoubleSide)
  //      {
  //         // glDisable(GL_CULL_FACE);
  //      }
  //      else
  //      {
  //         // glEnable(GL_CULL_FACE);
  //      }
  //      
  //      if (turnOnBlend)
		//{
  //          glEnable(GL_BLEND);
  //          glBlendEquation(GL_FUNC_ADD);
  //          switch (blendType) 
		//	{
  //              case eBlendType_One:
		//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//			break;
  //              
  //              default:
		//			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//			break;
  //          }
  //      }
  //      glEnable(GL_STENCIL_TEST);
  //      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  //      
  //      //暂时关闭这个真实人脸拉伸遮挡 蒙板测试
  //      if(enableStencilTest)
  //      {
  //          enableStencil();
  //      }
    }

	void GLES_Material::afterUpdate()
	{
		glDisable(GL_STENCIL_TEST);
		if (enableDepthTest)
		{
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			glEnable(GL_DEPTH_TEST);
		}

		if (enableDoubleSide)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
		if (turnOnBlend)
		{
			glDisable(GL_BLEND);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

    void GLES_Material::enableStencil()
    {
        glDepthMask(GL_TRUE);//启用写入深度值
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);
    }


	void GLES_Material::InvalidMaterial()
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
		afterUpdate();
	}

}
