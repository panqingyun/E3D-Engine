#include "E3DFrameBufferObject.h"
#include <src/RenderSystem/Texture/E3DTextureDataManager.hpp>
#include "../../../src/Source/E3DDebug.h"

namespace E3DEngine
{
	namespace GLRenderSystem
	{
		FrameBufferObject::FrameBufferObject()
		{
			m_FrameBuffer = 0;
			m_renderTarget = nullptr;
			m_ClearColor = Color4(0, 0, 0, 0);
			m_BufferPixels = nullptr;
		}

		FrameBufferObject::~FrameBufferObject()
		{
			SAFE_DELETE(m_renderTarget);
			glDeleteFramebuffers(1, &m_FrameBuffer);
			SAFE_DELETE(m_BufferPixels);
		}

		void FrameBufferObject::Create(int width, int height, DWORD targetType)
		{
			m_FrameWidth = width;
			m_FrameHeight = height;
			createTarget(targetType);

			glGenFramebuffers(1, &m_FrameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
			glGenRenderbuffers(1, &m_renderTarget->m_DepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, m_renderTarget->m_DepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderTarget->m_DepthBuffer);
			if (targetType == RENDER_BUFFER)
			{
				RenderBuffer* dt = static_cast<RenderBuffer*>(m_renderTarget);
				glGenRenderbuffers(1, &dt->m_RenderBuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, dt->m_RenderBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8_OES, width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, dt->m_RenderBuffer);
			}
			else
			{
				RenderTexture* dt = static_cast<RenderTexture*>(m_renderTarget);
				glGenTextures(1, &dt->m_TextureBuffer);
				glBindTexture(GL_TEXTURE_2D, dt->m_TextureBuffer);


				if (targetType == RENDER_TO_TEXTURE)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dt->m_TextureBuffer, 0);
				}
				else if(targetType == RENDER_DEPTH)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
					GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
					glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, dt->m_TextureBuffer, 0);
					glDrawBuffer(GL_NONE);
					glReadBuffer(GL_NONE);
					GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
					if (status != GL_FRAMEBUFFER_COMPLETE) 
					{
						Debug::Log(ell_Error, "FrameBuffer create failed");
					}
				}
			}
			m_BufferPixels = (GLbyte*)malloc(width * height * 4);
			glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &m_BufferType);
			glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &m_BufferFormat);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		}

		void FrameBufferObject::Clear()
		{
			glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
			glClearStencil(0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void FrameBufferObject::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
			glViewport(0, 0, m_FrameWidth, m_FrameHeight);
		}

		void FrameBufferObject::BindRenderBuffer()
		{
			if (m_renderTarget->Type == RENDER_BUFFER)
			{
				glBindRenderbuffer(GL_RENDERBUFFER, static_cast<RenderBuffer*>(m_renderTarget)->m_RenderBuffer);
			}
		}

		void FrameBufferObject::SetClearColor(Color4 clearColor)
		{
			m_ClearColor = clearColor;
		}

		GLuint FrameBufferObject::GetTextureBufferID()
		{
			if (m_renderTarget->Type == RENDER_TO_TEXTURE)
			{
				return static_cast<RenderTexture*>(m_renderTarget)->m_TextureBuffer;
			}
			return 0;
		}

		GLuint FrameBufferObject::GetFrameBufferID()
		{
			return m_FrameBuffer;
		}

		GLuint FrameBufferObject::GetRenderBufferID()
		{
			if (m_renderTarget->Type == RENDER_BUFFER)
			{
				return static_cast<RenderBuffer*>(m_renderTarget)->m_RenderBuffer;
			}
			return 0;
		}

		GLuint FrameBufferObject::GetDepthBufferID()
		{
			return m_renderTarget->m_DepthBuffer;
		}

		GLbyte * FrameBufferObject::GetPixels()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
			glReadPixels(0, 0, m_FrameWidth, m_FrameHeight, m_BufferFormat, m_BufferType, m_BufferPixels);
			return m_BufferPixels;
		}

		GLint FrameBufferObject::GetReadBufferFormat()
		{
			return m_BufferFormat;
		}

		GLint FrameBufferObject::GetReadBufferType()
		{
			return m_BufferType;
		}

		void FrameBufferObject::createTarget(DWORD targetType)
		{
			if (targetType == RENDER_BUFFER)
			{
				m_renderTarget = new RenderBuffer;
			}
			else if (targetType == RENDER_TO_TEXTURE || targetType == RENDER_DEPTH)
			{
				m_renderTarget = new RenderTexture;
			}
		}

		RenderTexture::~RenderTexture()
		{
			glDeleteTextures(1, &m_TextureBuffer);
		}

		RenderTexture::RenderTexture()
		{
			Type = RENDER_TO_TEXTURE;
			m_DepthBuffer = 0;
			m_TextureBuffer = 0;
		}

		RenderBuffer::RenderBuffer()
		{
			Type = RENDER_BUFFER;
			m_DepthBuffer = 0;
			m_RenderBuffer = 0;
		}

		RenderBuffer::~RenderBuffer()
		{
			glDeleteRenderbuffers(1, &m_RenderBuffer);
		}
	}
}

