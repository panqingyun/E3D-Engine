#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__

#include "../Material/E3DMaterial.hpp"
#include "../Texture/E3DTexture.hpp"
#include <src/Camera/E3DCamera.h>

namespace E3DEngine
{
	class Render2Texture : public Texture
	{
	public:
		Render2Texture();
		virtual void CreateRenderTarget(float width, float height);
	public:
		virtual ~Render2Texture();

		virtual void  Bind();

	public:
		virtual void Update(float deltaTime);

	protected:
		Camera				*   m_pCamera; 
		unsigned int			m_nTextureBuffer;
	};

}

#endif // !__LAYER_H__

