#ifndef RENDERER_TEXTUREARRAY_HPP
#define RENDERER_TEXTUREARRAY_HPP

#include <GL/glew.h>

namespace Antumbra
{
	class TextureArray
	{
	public:
		TextureArray();
		~TextureArray();

		void Fill(const void *data, int width, int height, int depth, GLenum format);
		bool IsFilled() const;

		void SetParameter(GLenum name, GLint value);
		void SetParameter(GLenum name, GLfloat value);

		void Bind(int textureUnit);
		void GenerateMipmaps();
	private:
		TextureArray(const TextureArray &);
		TextureArray &operator=(const TextureArray &);

		bool m_filled;
		GLuint m_texture;
	};
}

#endif