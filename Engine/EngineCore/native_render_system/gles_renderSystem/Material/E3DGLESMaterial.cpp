//
//  Material.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "E3DGLESMaterial.hpp"
#include <src/Source/Application.h>
#include "../../3rd/header/FilePath.h"
#include <Source/E3DVertex.h>

namespace E3DEngine
{
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

	void GLES_Material::CreateMaterial(MaterialConfig * config, ShaderConfig * sCfg)
	{
		pMaterialConfig = config;// EngineDelegate::GetInstance().GetTableManager(tableName)->Select<E3DEngine::MaterialConfig>(ConfigID);
		if (pMaterialConfig != nullptr)
		{
			//ShaderConfig * sCfg = EngineDelegate::GetInstance().GetTableManager(tableName)->Select<ShaderConfig>(pMaterialConfig->ShaderID);
			if (sCfg == nullptr)
			{
				return;
			}
			Color = Convert::_16To10(pMaterialConfig->Color);
			CreateShader(sCfg);
			
			for (auto& sp : samplerNameValue)
			{
				createTexture(sp.second, sp.first);
			}
		}
	}


	void GLES_Material::LoadShader(const char * vertexShaderString, const char * fragmentShaderString)
	{
		if (pShader == nullptr)
		{
			Debug::Log(ell_Error, "please call CreateShader function first!");
			return;
		}
		static_cast<GLES_Shader*>(pShader)->LoadShader(vertexShaderString, fragmentShaderString);
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

	void GLES_Material::parseShaderConfig(ShaderConfig *cfg)
	{
		if (cfg == nullptr)
		{
			Debug::Log(ell_Error, "shader config is null");
			return;
		}

		std::string path = Application::AppDataPath + "/" + filePath;
		std::string vertexShaderString = processVS().append(vvision::getContentFromPath(path + "/" + cfg->VertexShader));
		std::string fragmentShaderString = vvision::getContentFromPath(path + "/" + cfg->FragmentShader);

		processUniformVar(cfg);
		processAttribVar(cfg);

		LoadShader(vertexShaderString.c_str(), fragmentShaderString.c_str());
	}


	std::string GLES_Material::processVS()
	{
#ifdef __IOS__
		std::string priveVs = "#define __IOS__\n";
#endif
#ifdef __ANDROID__
		std::string priveVs = "#define __ANDROID__\n";
#endif
#ifdef WIN32
		std::string priveVs = "#define __WIN32__\n";
#endif
		priveVs.append("uniform mat4 ").append(VIEW_MATRIX).append(";\nuniform mat4 ").append(MODEL_MATRIX).append(";\nuniform mat4 ").append(PROJ_MATRIX).append(";\nuniform vec3 ").append(CAMERA_POS).append(";\n");
		priveVs.append("mat4 _e3d_getMVPMatrix()\n");
		priveVs.append("{\n");
		priveVs.append("\treturn ").append(PROJ_MATRIX).append(" * ").append(VIEW_MATRIX).append(" * ").append(MODEL_MATRIX).append(";\n");
		priveVs.append("}\n");
		return priveVs;
	}

    void GLES_Material::enableStencil()
    {
        glDepthMask(GL_TRUE);//启用写入深度值
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);
    }

	void GLES_Material::InitShaderVar()
	{
		createAttribute("POSITION"		, 0	, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_VERTEX);
		createAttribute("NORMAL"		, 3	, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_NORMAL);
		createAttribute("COLOR"			, 6	, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_COLOR);
		createAttribute("TEXTURECOORD"	, 10, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE0);
		createAttribute("TANGENT"		, 12, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TANGENT);
		createAttribute("BONEINDEX"		, 15, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_INDICES);
		createAttribute("BONEWEIGHT"	, 19, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_WEIGHTS);
		createAttribute("TRANSPOSITION"	, 23, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_POSITION);
		createAttribute("TRANSSCALE"	, 26, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_SCALE);
		createAttribute("TRANSROTATE"	, 29, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_ROTETION);
		createAttribute("SHADERINDEX"	, 32, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_FRAGMENT_INDEX);
		uniformSetFunc["float"]		= &Material::createFloat1Uniform;
		uniformSetFunc["vec2"]		= &Material::createFloat2Uniform;
		uniformSetFunc["vec3"]		= &Material::createFloat3Uniform;
		uniformSetFunc["vec4"]		= &Material::createFloat4Uniform;
		uniformSetFunc["mat2"]		= &Material::createMatrix2Uniform;
		uniformSetFunc["mat3"]		= &Material::createMatrix3Uniform;
		uniformSetFunc["mat4"]		= &Material::createMatrix4Uniform;
		uniformSetFunc["int"]		= &Material::createInt1Uniform;
		uniformSetFunc["sampler2D"] = &Material::createSamplerUniform;
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

	void GLES_Material::processUniformVar(ShaderConfig * cfg)
	{
		std::vector<std::string> uniformVar = StringBuilder::Split(cfg->UniformVariable, ";");
		for (auto &uniform : uniformVar)
		{
			std::string uniformKeyValue = StringBuilder::Trim(uniform);
			if (uniformKeyValue == empty_string)
			{
				continue;
			}
			bool hasDefaultVale = true;
			
			// 临时只处理一下sampler2D
			if (uniformKeyValue.find("-") != std::string::npos)
			{
				hasDefaultVale = true;
			}
			else
			{
				hasDefaultVale = false;

			}
			std::vector<std::string> uniformKey = StringBuilder::Split(uniformKeyValue, ":");
			std::string uniformValue = "";
			std::string defaultVale = "";
			if (hasDefaultVale)
			{
				std::vector<std::string> values = StringBuilder::Split(uniformKey[1], "-");
				uniformValue = values[0];
				defaultVale = values[1];
				varToTypeMap[uniformValue] = uniformKey[0];
			}
			else
			{
				varToTypeMap[uniformKey[1]] = uniformKey[0];
				uniformValue = uniformKey[1];
			}
			(this->*uniformSetFunc[uniformKey[0]])(uniformValue.c_str(), defaultVale);
			
		}
		(this->*uniformSetFunc["mat4"])(PROJ_MATRIX, "");
		(this->*uniformSetFunc["mat4"])(VIEW_MATRIX, "");
		(this->*uniformSetFunc["mat4"])(MODEL_MATRIX, "");
		(this->*uniformSetFunc["vec3"])(CAMERA_POS, "");
	}

}
