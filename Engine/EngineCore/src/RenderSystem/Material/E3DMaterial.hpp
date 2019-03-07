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
		virtual void UseMaterial()		= 0;
		// -----------------------------------------------
		// 材质失效
		//-----------------------------------------------
		virtual void InvalidMaterial()	= 0;
		// -----------------------------------------------
		// 给材质设置纹理
		// @param texture 纹理
		// @param index 纹理索引
		//-----------------------------------------------
		virtual void SetTexture(Texture * texture, int index = 0)	= 0;
		// -----------------------------------------------
		// 启用Shader
		//-----------------------------------------------
		virtual void UseProgram()									= 0;
		// -----------------------------------------------
		// 使用ID是0的shader 即不使用任何shader
		//-----------------------------------------------
		virtual void UseNullProgram()								= 0;
		// -----------------------------------------------
		// 更新shader 变量
		// @ param vertexType 顶点索引类型
		//-----------------------------------------------
		virtual void UpdateShader(unsigned int vertexType)			= 0;

	public:
		Shader *GetShader();
		// -----------------------------------------------
		// 创建Shader 
		// @param shader配置
		//-----------------------------------------------
		void CreateShader(ShaderConfig *cfg);
		// -----------------------------------------------
		// 获取RenderTexture
		//-----------------------------------------------
		Render2Texture *GetRenderTexture();
		// -----------------------------------------------
		// 创建Mono对象
		//-----------------------------------------------
		MonoBehaviour * GetBehaviour();
		void SetColor(Color4 color);
		int GetTextureCount();
		void SaveInFile();

	public:

		// -----------------------------------------------
		// 清理
		//-----------------------------------------------
		virtual void Destory();
		// -----------------------------------------------
		// 创建材质
		// @param 材质配置
		// @param Shader配置
		//-----------------------------------------------
		void CreateMaterial(MaterialConfig * config);
		void SetRenderState() { }
		void SetEnableDepthWrite(bool bEnable);
		void SetBlendType(DWORD src, DWORD dst);
		void SetEnableDepthTest(bool enable);
		void SetEnableCullFace(bool enable);
	protected:
		void createCubeTexture(std::vector<std::string> &varValues);
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
		int			textureCount;

		Render2Texture *Rtt;

	public:
		Shader			* mShader;		// shader
		TableManager	* mMaterialTableManager;
		MaterialConfig	* mMaterialConfig;
		std::string		mFilePath;
		vvision::vec4f	mColor;
	};
}

#endif /* Material_hpp */
