#include "BlockGoldOre.hpp"

namespace Antumbra
{
	uint8_t BlockGoldOre::GetId() const
	{
		return Id;
	}

	int BlockGoldOre::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockGoldOre::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/gold_ore.png");
	}
}