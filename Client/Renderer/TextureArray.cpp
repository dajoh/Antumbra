#include <exception>
#include "TextureArray.hpp"

namespace Antumbra
{
	TextureArray::TextureArray() : m_filled(false)
	{
		glGenTextures(1, &m_texture);
	}

	TextureArray::~TextureArray()
	{
		glDeleteTextures(1, &m_texture);
	}

	void TextureArray::Fill(const void *data, int width, int height, int depth, GLenum format)
	{
		GLenum formatType;
		GLenum basicFormat;

		switch(format)
		{
		case GL_RGB8:
			formatType = GL_UNSIGNED_BYTE;
			basicFormat = GL_RGB;
			break;
		case GL_RGBA8:
			formatType = GL_UNSIGNED_BYTE;
			basicFormat = GL_RGBA;
			break;
		case GL_RG16F:
			formatType = GL_FLOAT;
			basicFormat = GL_RG;
			break;
		case GL_DEPTH_COMPONENT24:
			formatType = GL_UNSIGNED_BYTE;
			basicFormat = GL_DEPTH_COMPONENT;
			break;
		default:
			throw std::exception("Unsupported texture format.");
		}

		glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, depth, 0, basicFormat, formatType, data);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		m_filled = true;
	}

	bool TextureArray::IsFilled() const
	{
		return m_filled;
	}

	void TextureArray::SetParameter(GLenum name, GLint value)
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, name, value);
	}

	void TextureArray::SetParameter(GLenum name, GLfloat value)
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
		glTexParameterf(GL_TEXTURE_2D_ARRAY, name, value);
	}

	void TextureArray::Bind(int textureUnit)
	{
		if(!m_filled)
		{
			throw std::exception("Tried to bind unfilled texture.");
		}

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
	}

	void TextureArray::GenerateMipmaps()
	{
		if(!m_filled)
		{
			throw std::exception("Tried to generate mipmaps for unfilled texture.");
		}

		glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
}