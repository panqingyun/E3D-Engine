#ifndef _GL_RENDERSYSTEM_HPP_
#define _GL_RENDERSYSTEM_HPP_
#include "WGL/WGLContext.h"
#include <stdio.h>
#include <src/RenderSystem/E3DRenderSystem.hpp>
#include "FrameBufferObject/E3DFrameBufferObject.h"
#include "Include/Include.h"

namespace E3DEngine
{
	using namespace GLRenderSystem;
	class GL_RenderSystem : public RenderSystem
	{
	public:
		GL_RenderSystem();
		~GL_RenderSystem() = default;
	public:
		virtual void Initilize() override;
		virtual void Cleanup() override;
		virtual void BindDefaultBackbuffer() override;
		virtual void ChangeRenderSurface(HWND windowHandle) override;
		void	CreateOpenGL(HDC displayID);
		void    Clear(Color4 color, int clearType);
		static GL_RenderSystem * GetRenderSystem();
		virtual void CreateShareContext() override;
		virtual void UseShareContext() override;
		virtual void UseRenderContext() override;
		virtual void SetCullFaceType(CULL_FACE type) override;
	public:
		virtual void BeginFrame() override;
		void EndFrame() override;
	public:
		void	SetupDefaultFrameBuffer();

	private:
		FrameBufferObject * defaultFrameBuffer;
		GL_Context *		m_pGL_Context;
	};

}

#endif /* RenderSystem_hpp */
