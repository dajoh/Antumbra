#ifndef WORLD_WORLD_HPP
#define WORLD_WORLD_HPP

#include <list>
#include <cmath>
#include <functional>
#include <sparsehash/dense_hash_map>
#include "ChunkGen.hpp"
#include "BlockAccess.hpp"
#include "Blocks/Block.hpp"

namespace Antumbra
{
	typedef google::dense_hash_map<uint8_t, BlockPtr> BlockRegistry;

	class World : public BlockAccess
	{
	public:
		World();

		void LoadChunk(int x, int z);
		void UnloadChunk(int x, int z);

		Chunk *GetChunk(int x, int z);
		const Chunk *GetChunk(int x, int z) const;

		void SetBlock(int x, int y, int z, uint8_t id);
		void SetLight(int x, int y, int z, uint8_t level);
		void SetSkyLight(int x, int y, int z, uint8_t level);

		uint8_t GetBlock(int x, int y, int z) const;
		uint8_t GetLight(int x, int y, int z) const;
		uint8_t GetSkyLight(int x, int y, int z) const;

		void OnChunkChanged(Chunk *chunk);

		void SetOnChunkLoaded(std::function<void(Chunk *)> cb);
		void SetOnChunkChanged(std::function<void(Chunk *)> cb);
		void SetOnChunkUnloaded(std::function<void(Chunk *)> cb);

		BlockRegistry &GetBlockRegistry();
	private:
		ChunkGen m_chunkGen;
		BlockRegistry m_blockReg;
		std::list<Chunk> m_chunks;
		std::function<void(Chunk *)> m_onChunkLoaded;
		std::function<void(Chunk *)> m_onChunkChanged;
		std::function<void(Chunk *)> m_onChunkUnloaded;
		google::dense_hash_map<uint64_t, Chunk *> m_chunkMap;
	};

	inline uint64_t HashCoords(int x, int z)
	{
		return ((uint64_t)z << 32) | (uint32_t)x;
	}

	inline void GetChunkCoords(int x, int z, int &chunkX, int &chunkZ)
	{
		static_assert(Chunk::Width == 16, "Chunk width not 16.");
		static_assert(Chunk::Depth == 16, "Chunk depth not 16.");
		chunkX = x >> 4;
		chunkZ = z >> 4;
	}

	inline void GetBlockCoords(int x, int z, int &blockX, int &blockZ)
	{
		static_assert(Chunk::Width == 16, "Chunk width not 16.");
		static_assert(Chunk::Depth == 16, "Chunk depth not 16.");
		blockX = x & 15;
		blockZ = z & 15;
	}
}

#endif