#ifndef WORLDRENDERER_TEXTUREREGISTRY_HPP
#define WORLDRENDERER_TEXTUREREGISTRY_HPP

#include <vector>
#include <string>
#include "../Renderer/TextureArray.hpp"

namespace Antumbra
{
	class TextureRegistry
	{
	public:
		int RegisterTexture(const std::string &name);
		void BuildTexture();

		void Bind(int textureUnit);
	private:
		TextureArray m_texArray;
		std::vector<std::string> m_texNames;
	};
}

#endif