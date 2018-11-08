#ifndef __GLES_RENDER_TEXTURE_H__
#define __GLES_RENDER_TEXTURE_H__

#include "../FrameBufferObject/E3DFrameBufferObject.h"
#include <src/RenderSystem/Texture/E3DRender2Texture.h>
#include "../Include/Include.h"

namespace E3DEngine
{
	class GLES_Render2Texture : public Render2Texture
	{
		friend class GLES_TextureDataManager;
	protected:
		GLES_Render2Texture()
		{
		}
	public:
		virtual void CreateRenderTarget(float width, float height) override;
		virtual void CreateDepthTarget(float width, float height) override;
	public:
		~GLES_Render2Texture();
		virtual void  Bind();
	protected:
		GLESRenderSystem::FrameBufferObject   *	m_fbo;
		GLuint			m_nTextureUniform;
		GLuint			m_nTextureIndex;
	};

}

#endif // !__LAYER_H__

