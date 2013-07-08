#ifndef RENDERER_IMAGE_HPP
#define RENDERER_IMAGE_HPP

#include <string>
#include <GL/glew.h>

namespace Antumbra
{
	class Image
	{
	public:
		Image(const std::string &fileName, GLenum format);
		~Image();

		int GetWidth() const;
		int GetHeight() const;
		const void *GetData() const;
	private:
		int m_width;
		int m_height;
		unsigned char *m_data;
	};
}

#endif