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
	public:
		~GL_Render2Texture();
		void Bind();

	protected:
		FrameBufferObject   *	m_fbo;
	};

}

#endif // !__LAYER_H__

