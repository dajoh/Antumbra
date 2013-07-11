#ifndef RENDERER_TEXTURE2D_HPP
#define RENDERER_TEXTURE2D_HPP

#include <GL/glew.h>

namespace Antumbra
{
	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();

		void Fill(const void *data, int width, int height, GLenum format);
		bool IsFilled() const;

		void SetParameter(GLenum name, GLint value);
		void SetParameter(GLenum name, GLfloat value);

		void Bind(int textureUnit);
		void GenerateMipmaps();
	private:
		Texture2D(const Texture2D &);
		Texture2D &operator=(const Texture2D &);

		bool m_filled;
		GLuint m_texture;

		friend class Framebuffer;
	};
}

#endif