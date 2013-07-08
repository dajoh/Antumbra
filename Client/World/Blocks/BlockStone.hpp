#ifndef WORLD_BLOCKS_BLOCKSTONE_HPP
#define WORLD_BLOCKS_BLOCKSTONE_HPP

#include "Block.hpp"

namespace Antumbra
{
	class BlockStone : public Block
	{
	public:
		static const uint8_t Id = 2;

		virtual uint8_t GetId() const;
		virtual int GetTexture(Direction direction) const;

		virtual void RegisterTextures(TextureRegistry &textureReg);
	private:
		int m_texture;
	};
}

#endif