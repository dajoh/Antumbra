#ifndef WORLD_CHUNK_HPP
#define WORLD_CHUNK_HPP

#include <cstdint>

namespace Antumbra
{
	class Chunk
	{
	public:
		static const int Width = 16;
		static const int Height = 128;
		static const int Depth = 16;

		Chunk(int x, int z);

		void GetLocation(int &x, int &z) const;

		void SetBlock(int x, int y, int z, uint8_t id);
		void SetLight(int x, int y, int z, uint8_t level);
		void SetSkyLight(int x, int y, int z, uint8_t level);

		uint8_t GetBlock(int x, int y, int z) const;
		uint8_t GetLight(int x, int y, int z) const;
		uint8_t GetSkyLight(int x, int y, int z) const;
	private:
		int m_x;
		int m_z;
		uint8_t m_light[Width * Height * Depth];
		uint8_t m_blocks[Width * Height * Depth];
	};
}

#endif