#include "Framebuffer.hpp"

namespace Antumbra
{
	Framebuffer::Framebuffer()
	{
		glGenFramebuffers(1, &m_framebuffer);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_framebuffer);
	}

	void Framebuffer::AttachTexture(GLenum attachPoint, Texture2D &texture)
	{
		if(attachPoint >= GL_COLOR_ATTACHMENT0 && attachPoint < GL_DEPTH_ATTACHMENT)
		{
			bool drawBufFound = false;

			for(size_t i = 0; i < m_drawBuffers.size(); i++)
			{
				if(m_drawBuffers[i] == attachPoint)
				{
					drawBufFound = true;
					break;
				}
			}

			if(!drawBufFound)
			{
				m_drawBuffers.push_back(attachPoint);
			}
		}

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachPoint, GL_TEXTURE_2D, texture.m_texture, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);

		if(m_drawBuffers.size() != 0)
		{
			glDrawBuffers(m_drawBuffers.size(), &m_drawBuffers[0]);
		}
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
}