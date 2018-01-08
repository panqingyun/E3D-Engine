//
//  RenderSystem.hpp
//
//  Created by 潘庆云 on 2017/1/22.
//

#ifndef _GLES_RenderSystem_HPP_
#define _GLES_RenderSystem_HPP_

#include "EGL\EGLContext.h"
#include <stdio.h>
#include <src/RenderSystem/E3DRenderSystem.hpp>
#include "EGL/EGLContext.h"
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
		virtual Render2Texture * CreateRtt(float width, float height) override;
#ifndef __IOS__
		void	CreateOpenGLES(EGLNativeDisplayType displayID,EGLNativeWindowType windowHandle);
#endif
		void	BindDefaultFBO();
		void    Clear(Color4 color, int clearType);

	public:
		virtual void BeginFrame() override;
		void clearFrameBufferObject();
		void EndFrame() override;
	public:
		void	SetupDefaultFrameBuffer();

	private:
		FrameBufferObject * defaultFrameBuffer;
		EGL_Context *		m_pEGL_Context_Ex;
	};

}
#endif /* RenderSystem_hpp */
