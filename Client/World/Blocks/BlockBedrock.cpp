#include "BlockBedrock.hpp"

namespace Antumbra
{
	uint8_t BlockBedrock::GetId() const
	{
		return Id;
	}

	int BlockBedrock::GetTexture(Direction direction) const
	{
		return m_texture;
	}

	void BlockBedrock::RegisterTextures(TextureRegistry &textureReg)
	{
		m_texture = textureReg.RegisterTexture("textures/bedrock.png");
	}
}