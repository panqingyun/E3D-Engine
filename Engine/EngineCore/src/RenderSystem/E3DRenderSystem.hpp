//
//  RenderSystem.hpp
//  ifme
//
//  Created by 潘庆云 on 2017/1/22.
//

#ifndef __E3D_RENDER_SYSTEM_HPP__
#define __E3D_RENDER_SYSTEM_HPP__

#include <stdio.h>
#include <string>
#include "RenderObject/E3DRenderManager.hpp"
#include "Material/E3DMaterialManager.hpp"
#include "Texture/E3DTextureDataManager.hpp"
#include "Texture/E3DRender2Texture.h"
#include "../../include/EngineAPI.h"
#include "Shader/E3DShaderManager.h"

namespace E3DEngine
{	
	enum ClearType
	{
		eCT_NotClear = 0,
		eCT_Color	 = 1,
		eCT_Depth	 = 1 << 1,
		eCT_Stencil  = 1 << 2,
	};

	enum DrawModule
	{
		eDM_TRIANGLE_STRIP,
		eDM_TRIANGLES,
		eDM_LINE_STRIP,
		eDM_LINES,
		eDM_POINTS,
	};

	class E3D_EXPORT_DLL RenderSystem : public IObject
	{
	public:
		RenderSystem();
		~RenderSystem() = default;

		void Render();
		void SetPauseRender(bool isPause);
	public:
		virtual void Initilize();
		virtual std::string GetName();

		virtual void	Cleanup(); 
		virtual void    Clear(Color4 color, int clearType);
		virtual void	BindDefaultBackbuffer();
		Vector2	GetFrameSize();
		virtual void    ChangeRenderSurface(NATIVE_WINDOW_TYPE windowHandle);
		virtual void	CreateShareContext();
		virtual void	UseShareContext();
		virtual void	UseRenderContext();

	public:
		RendererManager * GetRenderManager();
		MaterialManager * GetMaterialManager();
		TextureDataManager *GetTextureDataManager();
		ShaderManager * GetShaderManager();

	public:
		virtual void BeginFrame();
		virtual void EndFrame();

	public:
		void	setFrameHeight(float height);
		void	setFrameWidth(float width);
		float	getFrameHeight();
		float	getFrameWidth();
		bool	getIsMutilThreadRender();

	protected:
		float			m_frameHeight;
		float			m_frameWidth;

		RendererManager * m_pRenderManager;
		MaterialManager * m_pMaterialManager;
		TextureDataManager *	m_pTextureDataManager;
		ShaderManager	*		m_pShaderManager;

		bool					m_bIsMutilThreadRender;
		bool					m_bPauseRender;
		bool					m_bRenderPaused;
	};

}

void SetRenderSystem(E3DEngine::RenderSystem * rs);
E3D_EXPORT_DLL E3DEngine::RenderSystem * GetRenderSystem();

#endif /* RenderSystem_hpp */
