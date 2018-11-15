#include "E3DGLShaderManager.h"
#include "E3DGLShader.hpp"
#include "..\..\..\src\Source\E3DVertex.h"
#include "..\..\..\src\Scene\E3DSceneManager.hpp"
#include <src/Source/Helpers.h>

const std::string gAttributeStr = "#Attribute";
const std::string gVertexBeginStr = "#Vertex_Begin";
const std::string gVertexEndStr = "#Vertex_End";
const std::string gFragmentBeginStr = "#Framgent_Begin";
const std::string gFragmentEndStr = "#Framgent_End";

E3DEngine::GL_ShaderManager::GL_ShaderManager()
{
	initShaderAttributeVar();
}

E3DEngine::Shader * E3DEngine::GL_ShaderManager::createShader(std::string shaderPath, std::string unifVar)
{
	GL_Shader *shader = new GL_Shader;
	shader->InitShaderVar();
	std::string vertexShaderString;
	std::string fragmentShaderString;
	preProcessShader(shader, shaderPath, vertexShaderString, fragmentShaderString);
	shader->LoadShader(vertexShaderString.c_str(), fragmentShaderString.c_str());
	return shader;
}

void E3DEngine::GL_ShaderManager::createAttribute(std::string typeName, int StartPosition, uint VarType, BOOL Normalized, uint VertexStructSize, uint AttributeSize, uint BindLocation, std::string attrType, uint type)
{
	Attribute attribute;
	attribute.AttributeSize = AttributeSize;
	attribute.BindLocation = BindLocation;
	attribute.Normalized = Normalized;
	attribute.StartPosition = StartPosition;
	attribute.VarName = "";
	attribute.VarType = VarType;
	attribute.AttribType = attrType;

	attribute.VertexStructSize = VertexStructSize;
	if (type == STATIC_VERTEX)
	{
		staticAttributeMap[typeName] = attribute;
	}
	else
	{
		dynamicAttributeMap[typeName] = attribute;
	}
}

void E3DEngine::GL_ShaderManager::initShaderAttributeVar()
{
	createAttribute("POSITION", 0, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_VERTEX, "vec3", STATIC_VERTEX);
	createAttribute("NORMAL", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_NORMAL, "vec3", STATIC_VERTEX);
	createAttribute("COLOR", 6, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_COLOR, "vec4", STATIC_VERTEX);
	createAttribute("TEXTURECOORD", 10, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE0, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD0", 10, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE0, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD1", 12, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE1, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD2", 14, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE2, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD3", 16, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE3, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD4", 18, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE4, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD5", 20, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE5, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD6", 22, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE6, "vec2", STATIC_VERTEX);
	createAttribute("TEXTURECOORD7", 24, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2, LOCATION_ATTRIB_TEXTURE7, "vec2", STATIC_VERTEX);
	createAttribute("TANGENT", 26, GL_FLOAT, GL_FALSE, sizeof(Vertex), 3, LOCATION_ATTRIB_TANGENT, "vec3", STATIC_VERTEX);
	createAttribute("BONEINDEX", 29, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_INDICES, "vec4", STATIC_VERTEX);
	createAttribute("BONEWEIGHT", 33, GL_FLOAT, GL_FALSE, sizeof(Vertex), 4, LOCATION_ATTRIB_BONES_WEIGHTS, "vec4", STATIC_VERTEX);

	createAttribute("TRANSPOSITION", 0, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), 3, LOCATION_ATTRIB_TRANSFORM_POSITION, "vec3", DYNAMIC_VERTEX);
	createAttribute("TRANSSCALE", 3, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), 3, LOCATION_ATTRIB_TRANSFORM_SCALE, "vec3", DYNAMIC_VERTEX);
	createAttribute("TRANSROTATE", 6, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), 3, LOCATION_ATTRIB_TRANSFORM_ROTETION, "vec3", DYNAMIC_VERTEX);
	createAttribute("DYNAMICCOLOR", 9, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), 4, LOCATION_ATTRIB_DYNAMIC_COLOR, "vec4", DYNAMIC_VERTEX);
}

std::string E3DEngine::GL_ShaderManager::processVS()
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
	if (SceneManager::GetCurrentScene()->GetDirectionalLight() != nullptr)
	{
		priveVs.append("#define USING_DIRECTIONAL_LIGHT  \n");
		priveVs.append("uniform vec3 ").append(LIGHT_DIR).append(";\n");
		priveVs.append("uniform vec4 ").append(LIGHT_COLOR).append(";\n");
		priveVs.append("uniform mat4 ").append(LIGHT_PROJ_MAT).append(";\n");
		priveVs.append("uniform mat4 ").append(LIGHT_VIEW_MAT).append(";\n");
	}
	std::map<UINT, Light*>& pointLights = SceneManager::GetCurrentScene()->GetPointLights();
	if (pointLights.size() != 0)
	{
		std::string lightCount = Convert::ToString((int)pointLights.size());
		priveVs.append("#define USING_POINT_LIGHT  \n");
		priveVs.append("const int _e3d_PointLightCount = ").append(lightCount).append(";\n");
		priveVs.append("uniform vec3 ").append(POINT_LIGHT_POS).append("[").append(lightCount).append("];\n");
		priveVs.append("uniform float ").append(POINT_LIGHT_RANGE).append("[").append(lightCount).append("];\n");
		priveVs.append("uniform vec4 ").append(POINT_LIGHT_COLOR).append("[").append(lightCount).append("];\n");
	}
	priveVs.append("uniform mat4 ").append(VIEW_MATRIX).append(";\nuniform mat4 ").append(MODEL_MATRIX).append(";\nuniform mat4 ").append(PROJ_MATRIX).append(";\nuniform vec3 ").append(CAMERA_POS).append(";\n");
	priveVs.append("uniform vec3 ").append(ROTATION_VEC).append(";\n");
	priveVs.append("mat4 _e3d_getMVPMatrix()\n");
	priveVs.append("{\n");
	priveVs.append("\treturn ").append(PROJ_MATRIX).append(" * ").append(VIEW_MATRIX).append(" * ").append(MODEL_MATRIX).append(";\n");
	priveVs.append("}\n");
	priveVs.append("uniform float ").append(_Time).append(";\n");
	
	return priveVs;
}

void E3DEngine::GL_ShaderManager::processUniformVar(GL_Shader *shader, std::string &shaderContent)
{
	size_t&& pos = shaderContent.find("uniform");
	while (pos != std::string::npos)
	{
		size_t&& endPos = shaderContent.find(";", pos + 1);
		if (endPos == std::string::npos)
		{
			pos = shaderContent.find("uniform", pos + 1);
			continue;
		}
		std::string&& uniformString = shaderContent.substr(pos, endPos - pos);

		StringBuilder::ReplaceAll(uniformString, "\t", " ");
		std::vector<std::string> &&uniformVar = StringBuilder::Split(uniformString, " ");
		std::string uniformType = "";
		std::string uniformName = "";
		int size = 0;
		for (int i = 0; i < uniformVar.size();i++)
		{
			if (uniformVar[i] == "uniform" || uniformVar[i].empty())
			{
				continue;
			}
			else if (uniformType == "")
			{
				uniformType = uniformVar[i] + uniformType;
			}
			else if (uniformName == "")
			{
				uniformName = uniformVar[i];
				if (uniformName.find("[") != std::string::npos) //数组
				{
					std::vector<std::string> &&values = StringBuilder::Split(uniformName, "[");
					uniformType += "[]";

					size_t pos = values[1].find("]");
					if (pos != std::string::npos)
					{
						size = Convert::ToInt(values[1].substr(0, pos));
					}
				}
			}
		}
		shader->RunUniformFunc(uniformType, uniformName.c_str(), "", size);
		pos = shaderContent.find("uniform", pos + 1);
	}

}

void E3DEngine::GL_ShaderManager::processEngineDefineUniform(GL_Shader *shader)
{
	shader->RunUniformFunc("mat4",PROJ_MATRIX, "", 1);
	shader->RunUniformFunc("mat4",VIEW_MATRIX, "", 1);
	shader->RunUniformFunc("mat4",MODEL_MATRIX, "", 1);
	shader->RunUniformFunc("vec3",CAMERA_POS, "", 1);
	shader->RunUniformFunc("vec3", ROTATION_VEC, "", 1);
	shader->RunUniformFunc("float", _Time, "", 1);
	shader->RunUniformFunc("mat4", LIGHT_PROJ_MAT, "", 1);
	shader->RunUniformFunc("mat4", LIGHT_VIEW_MAT, "", 1);
	if (SceneManager::GetCurrentScene()->GetDirectionalLight() != nullptr)
	{
		shader->RunUniformFunc("vec4", LIGHT_COLOR, "", 1);
		shader->RunUniformFunc("vec3", LIGHT_DIR, "", 1);
	}
	std::map<UINT, Light*>& pointLights = SceneManager::GetCurrentScene()->GetPointLights();
	if (pointLights.size() != 0)
	{
		shader->RunUniformFunc("vec4[]",POINT_LIGHT_COLOR, "", pointLights.size());
		shader->RunUniformFunc("vec3[]",POINT_LIGHT_POS, "", pointLights.size());
		shader->RunUniformFunc("float[]",POINT_LIGHT_RANGE, "", pointLights.size());
	}
}

std::string E3DEngine::GL_ShaderManager::preProcessShader(GL_Shader *shader, std::string shaderFileName, std::string &vs_content, std::string &fs_content)
{
	std::ifstream infile;
	infile.open(shaderFileName.data());   //将文件流对象与文件连接起来 
	std::string strLine;
	std::string shaderContent = "";
	std::string folder, fileName;
	StringManipulator::SplitFileName(shaderFileName, folder, fileName);
	
	std::ostringstream tmp;
	tmp << infile.rdbuf();
	std::string &&str = tmp.str();

	getVertex(shader, str, folder, vs_content);
	getFragment(shader, str, folder, fs_content);

	return shaderContent;
}

void E3DEngine::GL_ShaderManager::appendInclude(std::string &strLine, std::string folder)
{
	size_t pos = strLine.find("#include");
	while (pos != std::string::npos)
	{
		int startPos = strLine.find("\"", pos);
		int endPos = strLine.find("\"", startPos + 1);
		std::string file = folder + "/" + strLine.substr(startPos + 1, endPos - startPos - 1);
		std::ifstream infile;
		infile.open(file.data());   //将文件流对象与文件连接起来 

		std::ostringstream tmp;
		tmp << infile.rdbuf();
		std::string &&str = tmp.str();

		strLine.erase(strLine.begin() + pos, strLine.begin() + endPos + 1);
		appendInclude(str, folder);
		strLine.insert(pos, str);

		pos = strLine.find("#include", pos + 1);
	}
}

void E3DEngine::GL_ShaderManager::processAttributeVar(GL_Shader *shader, std::string attri, std::string &shaderContent)
{
	StringBuilder::ReplaceAll(attri, "\t", "");
	StringBuilder::ReplaceAll(attri, " ", "");
	StringBuilder::ReplaceAll(attri, "\n", "");
	std::vector<std::string> &&attriVec = StringBuilder::Split(attri, ";");
	std::string attributeVari = "";
	for (int i = 0; i < attriVec.size(); i++)
	{
		std::vector<std::string> &&attribute = StringBuilder::Split(attriVec[i], ":");
		if (attribute.empty())
		{
			continue;
		}

		if (staticAttributeMap.find(attribute[0]) != staticAttributeMap.end())
		{
			int typeSize = staticAttributeMap[attribute[0]].AttributeSize;
			Attribute &attr = staticAttributeMap[attribute[0]];
			staticAttributeMap[attribute[0]].VarName = attribute[1];
			attr.VarName = attribute[1];
			attr.TypeName = attribute[0];
			shader->AddAttriList(attr, true);
			attributeVari.append("attribute ").append(attr.AttribType).append(" ").append(attr.VarName).append(";\n");
		}
		else if (dynamicAttributeMap.find(attribute[0]) != dynamicAttributeMap.end())
		{
			int typeSize = dynamicAttributeMap[attribute[0]].AttributeSize;
			Attribute &attr = dynamicAttributeMap[attribute[0]];
			dynamicAttributeMap[attribute[0]].VarName = attribute[1];
			attr.VarName = attribute[1];
			attr.TypeName = attribute[0];
			shader->AddAttriList(attr, false);
			attributeVari.append("attribute ").append(attr.AttribType).append(" ").append(attr.VarName).append(";\n");
		}
	}

	shaderContent.insert(0, attributeVari);
}

void E3DEngine::GL_ShaderManager::getVertex(GL_Shader *shader, std::string &str, std::string folder, std::string &vs_content)
{
	size_t pos_begin = str.find(gVertexBeginStr);
	size_t pos_end = str.find(gVertexEndStr);
	if (pos_begin != std::string::npos && pos_end != std::string::npos)
	{
		vs_content = str.substr(pos_begin, pos_end);
		size_t pos = vs_content.find(gAttributeStr);
		if (pos != std::string::npos)
		{
			size_t pos1 = vs_content.find("{", pos);
			size_t pos2 = vs_content.find("}", pos);
			if (pos1 != std::string::npos && pos2 != std::string::npos)
			{
				std::string attrib = vs_content.substr(pos1 + 1, pos2 - pos1 - 1);
				vs_content = vs_content.substr(pos2 + 1, pos_end - pos2);
				processUniformVar(shader, vs_content);
				processEngineDefineUniform(shader);
				appendInclude(vs_content, folder);
				processAttributeVar(shader, attrib, vs_content);
				vs_content = processVS().append(vs_content);
			}
		}
	}
}

void E3DEngine::GL_ShaderManager::getFragment(GL_Shader *shader, std::string &str, std::string folder, std::string &fs_content)
{
	size_t pos_begin = str.find(gFragmentBeginStr);
	size_t pos_end = str.find(gFragmentEndStr);
	if (pos_begin != std::string::npos && pos_end != std::string::npos)
	{
		fs_content = str.substr(pos_begin + gFragmentBeginStr.length() + 1, pos_end - pos_begin - 1 - gFragmentBeginStr.length());

		if (SceneManager::GetCurrentScene()->GetDirectionalLight() != nullptr)
		{
			std::string lightUniform = "";
			Light * light = SceneManager::GetCurrentScene()->GetDirectionalLight();
			if (object_cast<bool>(Light::GetCreateShadow(light)))
			{
				lightUniform.append("#define __CREATE_SHADOW__\n").append("uniform sampler2D ").append(LIGHT_DEPTH_TEX).append(";\n");
			}
			fs_content = lightUniform + fs_content;
		}
		appendInclude(fs_content, folder);
		processUniformVar(shader, fs_content);
	}
}
