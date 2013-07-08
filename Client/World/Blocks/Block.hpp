#ifndef WORLD_BLOCKS_BLOCK_HPP
#define WORLD_BLOCKS_BLOCK_HPP

#include <memory>
#include <cstdint>
#include "../Direction.hpp"
#include "../../WorldRenderer/TextureRegistry.hpp"

namespace Antumbra
{
	typedef std::shared_ptr<class Block> BlockPtr;

	class Block
	{
	public:
		virtual ~Block();

		virtual uint8_t GetId() const;
		virtual int GetTexture(Direction direction) const;

		virtual void RegisterTextures(TextureRegistry &textureReg);
	};
}

#endif