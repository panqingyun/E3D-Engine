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
	const char * lightShader = GLES_STRING(
	vec3 lightposition;//光源位置
	vec4 ambient;//环境光颜色
	vec4 lightcolor;//光源颜色
	float Ns;//高光系数
	float attenuation;//光线的衰减系数

	vec4 _e3d_getLightColor()
	{
		//--------------------------------------------------------------
		//--- 光照
		lightposition = vec3(50.0, 50.0, 50.0);
		ambient = vec4(0.5, 0.5, 0.5, 1.0);
		lightcolor = vec4(1.0, 1.0, 1.0, 1.0);
		Ns = 10.0;
		attenuation = 0.1;
		vec4 interpolatedPosition = vec4($POS, 1.0);
		vec3 N = normalize((vec4($NORMAL, 1.0)).xyz);
		vec3 L = normalize(lightposition - interpolatedPosition.xyz);
		vec3 V = normalize(_e3d_cameraPos - interpolatedPosition.xyz);
		vec3 H = normalize(V + L);
		vec3 diffuse = vec3((lightcolor * max(dot(N, L), 0.0)).xyz);
		vec3 specular = vec3((lightcolor * pow(max(dot(N, H), 0.0), Ns) * attenuation).xyz);
		vec4 _des_color = vec4(clamp((diffuse + specular), 0.0, 1.0), 1.0);
		return (_des_color + ambient);
	}

	);

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

		processUniformVar(cfg);
		processAttribVar(cfg);

		std::string path = Application::AppDataPath + "/" + filePath;
		std::string shaderContent = vvision::getContentFromPath(path + "/" + cfg->VertexShader);
		std::string vertexShaderString = processVS().append(shaderContent);
		std::string fragmentShaderString = vvision::getContentFromPath(path + "/" + cfg->FragmentShader);

		LoadShader(vertexShaderString.c_str(), fragmentShaderString.c_str());
	}

	void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
	{
		std::string::size_type pos = 0;
		std::string::size_type srclen = strsrc.size();
		std::string::size_type dstlen = strdst.size();

		while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
		{
			strBig.replace(pos, srclen, strdst);
			pos += dstlen;
		}
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
		for (auto &attri : attributeMap)
		{
			if (attri.second.VarName == "")
			{
				continue;
			}
			priveVs.append("attribute ").append(attri.second.AttribType).append(" ").append(attri.second.VarName).append(";\n");
		}
		priveVs.append(lightShader);
		string_replace(priveVs, "$POS", attributeMap["POSITION"].VarName);
		string_replace(priveVs, "$NORMAL", attributeMap["NORMAL"].VarName);
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
		createAttribute("POSITION"		, 0	, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_VERTEX				, "vec3");
		createAttribute("NORMAL"		, 3	, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_NORMAL				, "vec3");
		createAttribute("COLOR"			, 6	, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_COLOR				, "vec4");
		createAttribute("TEXTURECOORD"	, 10, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE0			, "vec2");
		createAttribute("TANGENT"		, 12, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TANGENT			, "vec3");
		createAttribute("BONEINDEX"		, 15, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_INDICES		, "vec4");
		createAttribute("BONEWEIGHT"	, 19, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_WEIGHTS		, "vec4");
		createAttribute("TRANSPOSITION"	, 23, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_POSITION	, "vec3");
		createAttribute("TRANSSCALE"	, 26, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_SCALE	, "vec3");
		createAttribute("TRANSROTATE"	, 29, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TRANSFORM_ROTETION	, "vec3");
		createAttribute("SHADERINDEX"	, 32, GL_FLOAT, GL_FALSE, sizeof(Vertex), 1, LOCATION_ATTRIB_FRAGMENT_INDEX		, "float");
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
