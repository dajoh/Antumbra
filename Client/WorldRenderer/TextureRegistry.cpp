#include <cstdint>
#include "TextureRegistry.hpp"
#include "../Renderer/Image.hpp"

namespace Antumbra
{
	int TextureRegistry::RegisterTexture(const std::string &name)
	{
		m_texNames.push_back(name);
		return m_texNames.size() - 1;
	}

	void TextureRegistry::BuildTexture()
	{
		if(m_texNames.size() == 0)
		{
			return;
		}

		std::shared_ptr<uint8_t> texData(new uint8_t [256*256*3 * m_texNames.size()]);

		for(size_t i = 0; i < m_texNames.size(); i++)
		{
			Image image(m_texNames[i], GL_RGB8);

			if(image.GetWidth() != 256 || image.GetHeight() != 256)
			{
				throw std::exception("Texture not 256x256.");
			}

			memcpy(&texData.get()[256*256*3 * i], image.GetData(), 256*256*3);
		}

		m_texArray.Fill(texData.get(), 256, 256, m_texNames.size(), GL_RGB8);
		m_texArray.GenerateMipmaps();
		m_texArray.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		m_texArray.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		m_texArray.SetParameter(GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	void TextureRegistry::Bind(int textureUnit)
	{
		m_texArray.Bind(textureUnit);
	}
}