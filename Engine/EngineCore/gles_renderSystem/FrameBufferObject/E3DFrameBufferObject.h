#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

#include <src/RenderSystem/E3DRenderSystem.hpp>
#include "../Include/Include.h"

namespace E3DEngine
{
	typedef enum 
	{
		RENDER_BUFFER,
		RENDER_TO_TEXTURE,
	} RenderTargeType;

	class RenderTarget
	{
	public:
		virtual ~RenderTarget()
		{
			glDeleteRenderbuffers(1, &m_DepthBuffer);
		}
		GLuint	m_DepthBuffer;
		RenderTargeType Type;
	};

	class RenderTexture : public RenderTarget
	{
	public:
		~RenderTexture() override;
		RenderTexture();
	public:
		GLuint	m_TextureBuffer;
	};

	class RenderBuffer : public RenderTarget
	{
	public:
		RenderBuffer();
		~RenderBuffer() override;
	public:
		GLuint	m_RenderBuffer;
	};

	class FrameBufferObject
	{
	public:
		FrameBufferObject();
		~FrameBufferObject();

	public:
		void Create(int width, int height, RenderTargeType targetType);
		void Clear();
		void Bind();
		void SetClearColor(Color4 clearColor);
	public:
		GLuint GetTextureBufferID();
		GLuint GetFrameBufferID();
		GLuint GetRenderBufferID();
		GLuint GetDepthBufferID();
		GLbyte * GetPixels();
		GLint  GetReadBufferFormat();
		GLint  GetReadBufferType();
	private:
		void createTarget(RenderTargeType targetType);
	private:
		GLuint			m_FrameBuffer;
		RenderTarget  * m_renderTarget;
		int				m_FrameWidth;
		int				m_FrameHeight;
		Color4			m_ClearColor;
		GLint			m_BufferFormat;
		GLint			m_BufferType;
		GLbyte		  * m_BufferPixels;
	};

}

#endif
