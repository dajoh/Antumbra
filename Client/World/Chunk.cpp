#include <cstring>
#include <cassert>
#include "Chunk.hpp"

namespace Antumbra
{
	Chunk::Chunk(int x, int z) : m_x(x), m_z(z)
	{
		memset(m_light, 0, Width * Height * Depth);
		memset(m_blocks, 0, Width * Height * Depth);
	}

	void Chunk::GetLocation(int &x, int &z) const
	{
		x = m_x;
		z = m_z;
	}

	void Chunk::SetBlock(int x, int y, int z, uint8_t id)
	{
		assert(x >= 0 && y >= 0 && z >= 0);
		assert(x < Width && y < Height && z < Depth);

		m_blocks[y * Width * Depth + z * Width + x] = id;
	}

	void Chunk::SetLight(int x, int y, int z, uint8_t level)
	{
		assert(x >= 0 && y >= 0 && z >= 0);
		assert(x < Width && y < Height && z < Depth);

		m_light[y * Width * Depth + z * Width + x] &= 0xF0;
		m_light[y * Width * Depth + z * Width + x] |= level & 0x0F;
	}

	void Chunk::SetSkyLight(int x, int y, int z, uint8_t level)
	{
		assert(x >= 0 && y >= 0 && z >= 0);
		assert(x < Width && y < Height && z < Depth);

		m_light[y * Width * Depth + z * Width + x] &= 0x0F;
		m_light[y * Width * Depth + z * Width + x] |= level & 0xF0;
	}

	uint8_t Chunk::GetBlock(int x, int y, int z) const
	{
		assert(x >= 0 && y >= 0 && z >= 0);
		assert(x < Width && y < Height && z < Depth);

		return m_blocks[y * Width * Depth + z * Width + x];
	}

	uint8_t Chunk::GetLight(int x, int y, int z) const
	{
		assert(x >= 0 && y >= 0 && z >= 0);
		assert(x < Width && y < Height && z < Depth);

		return m_light[y * Width * Depth + z * Width + x] & 0x0F;
	}

	uint8_t Chunk::GetSkyLight(int x, int y, int z) const
	{
		assert(x >= 0 && y >= 0 && z >= 0);
		assert(x < Width && y < Height && z < Depth);

		return m_light[y * Width * Depth + z * Width + x] >> 4;
	}
}