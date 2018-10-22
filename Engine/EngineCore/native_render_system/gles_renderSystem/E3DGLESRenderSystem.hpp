//
//  GLES_RenderSystem.hpp
//
//  Created by 潘庆云 on 2017/1/22.
//

#ifndef _GLES_RENDERSYSTEM_HPP_
#define _GLES_RENDERSYSTEM_HPP_
#ifndef __IOS__
#include "EGL/EGLContext.h"
#endif
#include <stdio.h>
#include <src/RenderSystem/E3DRenderSystem.hpp>
#include "FrameBufferObject/E3DFrameBufferObject.h"
#include "Include/Include.h"

namespace E3DEngine
{
	class GLES_RenderSystem : public RenderSystem
	{
	public:
		GLES_RenderSystem();
		~GLES_RenderSystem() = default;
	public:
		virtual void Initilize() override;
		virtual void Cleanup() override;
		virtual void BindDefaultBackbuffer() override;
		virtual void ChangeRenderSurface(EGLNativeWindowType windowHandle) override;
		void	CreateOpenGLES(EGLNativeDisplayType displayID,EGLNativeWindowType windowHandle);
		void    Clear(Color4 color, int clearType);
		static GLES_RenderSystem * GetRenderSystem();
        
	public:
		virtual void BeginFrame() override;
		void clearFrameBufferObject();
		void EndFrame() override;
	public:
		void	SetupDefaultFrameBuffer();

	private:
		FrameBufferObject * defaultFrameBuffer;
		EGL_Context *		m_pEGL_Context;
	};

}

#endif /* RenderSystem_hpp */
