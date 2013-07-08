#include "BlockDirt.hpp"

namespace Antumbra
{
	uint8_t BlockDirt::GetId() const
	{
		return Id;
	}

	int BlockDirt::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockDirt::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/dirt.png");
	}
}