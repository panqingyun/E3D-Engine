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

	enum CULL_FACE
	{
		eCF_BACK,
		eCF_FRONT,
	};

	class E3D_EXPORT_DLL RenderSystem : public IObject
	{
	public:
		RenderSystem();
		virtual ~RenderSystem() = default;
		void Render();
		void SetPauseRender(bool isPause);
		std::string GetName();
		Vector2	GetFrameSize();

	public:
		virtual void	Initilize()							= 0;
		virtual void	Cleanup()							= 0; 
		virtual void    Clear(Color4 color, int clearType)	= 0;
		virtual void	BindDefaultBackbuffer()				= 0;
		virtual void	UseShareContext()					= 0;
		virtual void	UseRenderContext()					= 0;
		virtual void	BeginFrame()						= 0;
		virtual void	EndFrame()							= 0;
		virtual void    SetCullFaceType(CULL_FACE type)		= 0;
		virtual void    ChangeRenderSurface(NATIVE_WINDOW_TYPE windowHandle) = 0;

	public:
		RendererManager * GetRenderManager();
		MaterialManager * GetMaterialManager();
		TextureDataManager *GetTextureDataManager();
		ShaderManager * GetShaderManager();
		virtual void	CreateShareContext();


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
