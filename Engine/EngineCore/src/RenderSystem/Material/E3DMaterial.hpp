//
//  Material.hpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#ifndef __E3D_METRAIL_HPP__
#define __E3D_METRAIL_HPP__

#include "../Shader/E3DShader.hpp"
#include "../Texture/E3DTexture.hpp"

namespace E3DEngine
{
	class TableManager;
	class MaterialConfig;
	class E3D_EXPORT_DLL Material : public  Object
	{
	public:
		Material(); 
		// -----------------------------------------------
		// 渲染调用开始之前，使用材质
		//-----------------------------------------------
		virtual void UseMaterial();

		// -----------------------------------------------
		// 材质失效
		//-----------------------------------------------
		virtual void InvalidMaterial();

		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Destory();

		// -----------------------------------------------
		// 创建材质
		// @param 材质配置
		// @param Shader配置
		//-----------------------------------------------
		virtual void CreateMaterial(MaterialConfig * config);

		// -----------------------------------------------
		// 给材质设置纹理
		// @param 纹理
		// @param 纹理索引
		//-----------------------------------------------
		virtual void SetTexture(Texture * texture, int index = 0);

		// -----------------------------------------------
		// 启用Shader
		//-----------------------------------------------
		virtual void UseProgram() { }

		// -----------------------------------------------
		// 使用ID是0的shader 即不使用任何shader
		//-----------------------------------------------
		virtual void UseNullProgram() { }
		virtual void UpdateShader(unsigned int vertexType) { }
		virtual void SetEnableDepthWrite(bool bEnable);
		virtual void SetBlendType(DWORD src, DWORD dst);
		virtual void SetEnableDepthTest(bool enable);
		virtual void SetEnableCullFace(bool enable);

	public:
		Shader *GetShader();
		// -----------------------------------------------
		// 创建Shader 
		// @param shader配置
		//-----------------------------------------------
		void CreateShader(ShaderConfig *cfg);
		Render2Texture *GetRenderTexture();
		// -----------------------------------------------
		// 创建Mono对象
		//-----------------------------------------------
		MonoBehaviour * GetBehaviour();
		void SetColor(Color4 color);

	protected:
		virtual void createShader(string vsName, string psName, string attrVar, string unifVar) { }
		virtual void parseShaderConfig(ShaderConfig *cfg);
		virtual void enableStencil();
		virtual void beforeUpdate();
		virtual void afterUpdate();
		virtual void createTexture2D(TextureData& data);
		virtual void createCubeTexture(std::vector<std::string> &varValues);
		void initUniformValue(ShaderConfig * sCfg, MaterialConfig * config);
		void createSampler2D(std::vector<std::string> &varValues, MaterialConfig * config);

		void createRtt(std::vector<std::string>& varValues);

	protected:
		bool        enableDepthTest; //开启深度测试
		bool        enablewriteDepth;
		bool        enableStencilTest; //开启模版测试
		bool        enableDoubleSide;
		bool        turnOnBlend;
		DWORD		srcBlendFactor;
		DWORD		dstBlendFactor;
		Render2Texture *Rtt;
		int			textureCount;

	public:
		Shader			* mShader;		// shader
		TableManager	* mMaterialTableManager;
		MaterialConfig	* mMaterialConfig;
		std::string		mFilePath;
		vvision::vec4f	mColor;
	};
}

#endif /* Material_hpp */
