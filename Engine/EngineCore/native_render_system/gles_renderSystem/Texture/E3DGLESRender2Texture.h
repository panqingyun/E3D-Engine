#ifndef __GLES_RENDER_TEXTURE_H__
#define __GLES_RENDER_TEXTURE_H__

#include "../FrameBufferObject/E3DFrameBufferObject.h"
#include "../Texture/E3DGLESTexture.hpp"
#include <src/RenderSystem/Texture/E3DRender2Texture.h>
#include "../Include/Include.h"

namespace E3DEngine
{
	class GLES_Render2Texture : public Render2Texture
	{
	public:
		GLES_Render2Texture()
		{
		}
		virtual void CreateRenderTarget(float width, float height) override;
	public:
		~GLES_Render2Texture();
		virtual void  Bind();

	public:
		virtual void Update(float deltaTime) override;

	protected:
		FrameBufferObject   *	m_fbo;
	};

}

#endif // !__LAYER_H__

