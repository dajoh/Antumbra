#ifndef WORLD_BLOCKS_BLOCKGOLDORE_HPP
#define WORLD_BLOCKS_BLOCKGOLDORE_HPP

#include "Block.hpp"

namespace Antumbra
{
	class BlockGoldOre : public Block
	{
	public:
		static const uint8_t Id = 7;

		virtual uint8_t GetId() const;
		virtual int GetTexture(Direction direction) const;

		virtual void RegisterTextures(TextureRegistry &textureReg);
	private:
		int m_texture;
	};
}

#endif