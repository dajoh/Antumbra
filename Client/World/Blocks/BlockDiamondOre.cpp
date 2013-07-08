#include "BlockDiamondOre.hpp"

namespace Antumbra
{
	uint8_t BlockDiamondOre::GetId() const
	{
		return Id;
	}

	int BlockDiamondOre::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockDiamondOre::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/diamond_ore.png");
	}
}