#ifndef WORLD_CHUNKCACHE_HPP
#define WORLD_CHUNKCACHE_HPP

#include <vector>
#include "World.hpp"

namespace Antumbra
{
	class ChunkCache : public BlockAccess
	{
	public:
		ChunkCache(World &world, int minX, int minZ, int maxX, int maxZ);

		void SetBlock(int x, int y, int z, uint8_t id);
		void SetLight(int x, int y, int z, uint8_t level);
		void SetSkyLight(int x, int y, int z, uint8_t level);

		uint8_t GetBlock(int x, int y, int z) const;
		uint8_t GetLight(int x, int y, int z) const;
		uint8_t GetSkyLight(int x, int y, int z) const;
	private:
		Chunk *GetChunk(int x, int z);
		const Chunk *GetChunk(int x, int z) const;

		int m_minX, m_minZ;
		int m_maxX, m_maxZ;
		int m_xChunks, m_zChunks;
		bool m_allLoaded;
		std::vector<Chunk *> m_chunks;
	};
}

#endif