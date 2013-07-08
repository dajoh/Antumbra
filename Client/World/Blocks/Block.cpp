#include "Block.hpp"

namespace Antumbra
{
	Block::~Block()
	{
	}

	uint8_t Block::GetId() const
	{
		return 0;
	}

	int Block::GetTexture(Direction direction) const
	{
		return 0;
	}

	void Block::RegisterTextures(TextureRegistry &textureReg)
	{
	}
}