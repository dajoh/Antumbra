#include "BlockIronOre.hpp"

namespace Antumbra
{
	uint8_t BlockIronOre::GetId() const
	{
		return Id;
	}

	int BlockIronOre::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockIronOre::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/iron_ore.png");
	}
}