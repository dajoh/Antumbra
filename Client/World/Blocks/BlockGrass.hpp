#ifndef WORLD_BLOCKS_BLOCKGRASS_HPP
#define WORLD_BLOCKS_BLOCKGRASS_HPP

#include "Block.hpp"

namespace Antumbra
{
	class BlockGrass : public Block
	{
	public:
		static const uint8_t Id = 4;

		virtual uint8_t GetId() const;
		virtual int GetTexture(Direction direction) const;

		virtual void RegisterTextures(TextureRegistry &textureReg);
	private:
		int m_textures[6];
	};
}

#endif