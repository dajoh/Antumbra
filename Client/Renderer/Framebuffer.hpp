#ifndef RENDERER_FRAMEBUFFER_HPP
#define RENDERER_FRAMEBUFFER_HPP

#include <vector>
#include "Texture2D.hpp"

namespace Antumbra
{
	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		void AttachTexture(GLenum attachPoint, Texture2D &texture);

		void Bind();
		void Unbind();
	private:
		Framebuffer(const Framebuffer &);
		Framebuffer &operator=(const Framebuffer &);

		GLuint m_framebuffer;
		std::vector<GLenum> m_drawBuffers;
	};
}

#endif