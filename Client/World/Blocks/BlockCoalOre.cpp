#include "BlockCoalOre.hpp"

namespace Antumbra
{
	uint8_t BlockCoalOre::GetId() const
	{
		return Id;
	}

	int BlockCoalOre::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockCoalOre::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/coal_ore.png");
	}
}