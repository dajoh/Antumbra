#ifndef WORLD_BLOCKS_BLOCKIRONORE_HPP
#define WORLD_BLOCKS_BLOCKIRONORE_HPP

#include "Block.hpp"

namespace Antumbra
{
	class BlockIronOre : public Block
	{
	public:
		static const uint8_t Id = 6;

		virtual uint8_t GetId() const;
		virtual int GetTexture(Direction direction) const;

		virtual void RegisterTextures(TextureRegistry &textureReg);
	private:
		int m_texture;
	};
}

#endif