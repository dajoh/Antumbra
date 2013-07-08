#include <exception>
#include "Texture2D.hpp"

namespace Antumbra
{
	Texture2D::Texture2D() : m_filled(false)
	{
		glGenTextures(1, &m_texture);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_texture);
	}

	void Texture2D::Fill(const void *data, int width, int height, GLenum format)
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

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, basicFormat, formatType, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		m_filled = true;
	}

	bool Texture2D::IsFilled() const
	{
		return m_filled;
	}

	void Texture2D::SetParameter(GLenum name, GLint value)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, name, value);
	}

	void Texture2D::SetParameter(GLenum name, GLfloat value)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameterf(GL_TEXTURE_2D, name, value);
	}

	void Texture2D::Bind(int textureUnit)
	{
		if(!m_filled)
		{
			throw std::exception("Tried to bind unfilled texture.");
		}

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture2D::GenerateMipmaps()
	{
		if(!m_filled)
		{
			throw std::exception("Tried to generate mipmaps for unfilled texture.");
		}

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
}