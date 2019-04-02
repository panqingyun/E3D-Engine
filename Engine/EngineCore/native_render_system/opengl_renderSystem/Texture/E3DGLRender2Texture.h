#ifndef __GL_RENDER_TEXTURE_H__
#define __GL_RENDER_TEXTURE_H__

#include "../FrameBufferObject/E3DFrameBufferObject.h"
#include <src/RenderSystem/Texture/E3DRender2Texture.h>
#include "../Include/Include.h"

namespace E3DEngine
{
	using namespace GLRenderSystem;
	class GL_Render2Texture : public Render2Texture
	{
		friend class GL_TextureDataManager;
	protected:
		GL_Render2Texture()
		{
		}
	public:
		virtual void CreateRenderTarget(float width, float height, int multiSampleLevel) override;
		virtual void CreateDepthTarget(float width, float height) override;
		virtual void Blit(Render2Texture * dest, BlitBuffer bufferType) override;

	public:
		~GL_Render2Texture();
		void Bind();
		FrameBufferObject * GetFBO();

	private:
		void blitFrameBuffer(FrameBufferObject * fbo, BlitBuffer bufferType);

	protected:
		FrameBufferObject   *	m_fbo;
	};

}

#endif // !__LAYER_H__

