#include "BlockStone.hpp"

namespace Antumbra
{
	uint8_t BlockStone::GetId() const
	{
		return Id;
	}

	int BlockStone::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockStone::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/stone.png");
	}
}