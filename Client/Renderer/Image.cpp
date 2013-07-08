#include <soil/soil.h>
#include "Image.hpp"

namespace Antumbra
{
	Image::Image(const std::string &fileName, GLenum format)
	{
		int channels;

		switch(format)
		{
		case GL_RGB8: channels = SOIL_LOAD_RGB; break;
		case GL_RGBA8: channels = SOIL_LOAD_RGBA; break;
		default:
			throw std::exception("Unsupported texture format.");
		};

		m_data = SOIL_load_image(fileName.c_str(), &m_width, &m_height, &channels, channels);
		if(!m_data)
		{
			throw std::exception("Couldn't load image.");
		}
	}

	Image::~Image()
	{
		SOIL_free_image_data(m_data);
	}

	int Image::GetWidth() const
	{
		return m_width;
	}

	int Image::GetHeight() const
	{
		return m_height;
	}

	const void *Image::GetData() const
	{
		return m_data;
	}
}