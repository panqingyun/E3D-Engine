#ifndef __E3D_RENDER_TEXTURE_H__
#define __E3D_RENDER_TEXTURE_H__

#include "../Material/E3DMaterial.hpp"
#include "../Texture/E3DTexture.hpp"

namespace E3DEngine
{
	class E3D_EXPORT_DLL Render2Texture : public Texture
	{
	protected:
		Render2Texture();
	public:
		virtual void CreateRenderTarget(float width, float height, int multiSampleLevel)	= 0;
		virtual void CreateDepthTarget(float width, float height)	= 0;
		virtual void  Bind()										= 0;
	public:
		virtual ~Render2Texture();

		float GetWidth();
		float GetHeight();

	protected:
		Camera				*   m_pCamera; 
		float					m_nWidth;
		float					m_nHeight;
	};

}

#endif // !__LAYER_H__

