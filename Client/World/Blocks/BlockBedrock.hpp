#ifndef WORLD_BLOCKS_BLOCKBEDROCK_HPP
#define WORLD_BLOCKS_BLOCKBEDROCK_HPP

#include "Block.hpp"

namespace Antumbra
{
	class BlockBedrock : public Block
	{
	public:
		static const uint8_t Id = 1;

		virtual uint8_t GetId() const;
		virtual int GetTexture(Direction direction) const;

		virtual void RegisterTextures(TextureRegistry &textureReg);
	private:
		int m_texture;
	};
}

#endif