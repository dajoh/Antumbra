#include "World.hpp"
#include "Blocks/BlockDirt.hpp"
#include "Blocks/BlockStone.hpp"
#include "Blocks/BlockGrass.hpp"
#include "Blocks/BlockBedrock.hpp"
#include "Blocks/BlockCoalOre.hpp"
#include "Blocks/BlockIronOre.hpp"
#include "Blocks/BlockGoldOre.hpp"
#include "Blocks/BlockDiamondOre.hpp"

namespace Antumbra
{
	World::World()
	{
		m_blockReg.set_empty_key(0);
		m_chunkMap.set_empty_key(HashCoords(INT32_MIN, INT32_MIN));
		m_chunkMap.set_deleted_key(HashCoords(INT32_MAX, INT32_MAX));
		
		m_blockReg[BlockDirt::Id] = BlockPtr(new BlockDirt());
		m_blockReg[BlockStone::Id] = BlockPtr(new BlockStone());
		m_blockReg[BlockGrass::Id] = BlockPtr(new BlockGrass());
		m_blockReg[BlockBedrock::Id] = BlockPtr(new BlockBedrock());
		m_blockReg[BlockCoalOre::Id] = BlockPtr(new BlockCoalOre());
		m_blockReg[BlockIronOre::Id] = BlockPtr(new BlockIronOre());
		m_blockReg[BlockGoldOre::Id] = BlockPtr(new BlockGoldOre());
		m_blockReg[BlockDiamondOre::Id] = BlockPtr(new BlockDiamondOre());
	}

	void World::LoadChunk(int x, int z)
	{
		m_chunks.push_back(Chunk(x, z));
		m_chunkMap[HashCoords(x, z)] = &m_chunks.back();
		m_chunkGen.Generate(m_chunks.back());

		if(m_onChunkLoaded)
		{
			m_onChunkLoaded(&m_chunks.back());
		}
	}

	void World::UnloadChunk(int x, int z)
	{
	}

	Chunk *World::GetChunk(int x, int z)
	{
		auto it = m_chunkMap.find(HashCoords(x, z));
		if(it != m_chunkMap.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const Chunk *World::GetChunk(int x, int z) const
	{
		auto it = m_chunkMap.find(HashCoords(x, z));
		if(it != m_chunkMap.end())
		{
			return it->second;
		}

		return nullptr;
	}

	void World::SetBlock(int x, int y, int z, uint8_t id)
	{
		int chunkX, chunkZ; GetChunkCoords(x, z, chunkX, chunkZ);
		int blockX, blockZ; GetBlockCoords(x, z, blockX, blockZ);

		auto chunk = GetChunk(chunkX, chunkZ);
		chunk->SetBlock(blockX, y, blockZ, id);
		OnChunkChanged(chunk);
	}

	void World::SetLight(int x, int y, int z, uint8_t level)
	{
		int chunkX, chunkZ; GetChunkCoords(x, z, chunkX, chunkZ);
		int blockX, blockZ; GetBlockCoords(x, z, blockX, blockZ);

		auto chunk = GetChunk(chunkX, chunkZ);
		chunk->SetLight(blockX, y, blockZ, level);
		OnChunkChanged(chunk);
	}

	void World::SetSkyLight(int x, int y, int z, uint8_t level)
	{
		int chunkX, chunkZ; GetChunkCoords(x, z, chunkX, chunkZ);
		int blockX, blockZ; GetBlockCoords(x, z, blockX, blockZ);

		auto chunk = GetChunk(chunkX, chunkZ);
		chunk->SetSkyLight(blockX, y, blockZ, level);
		OnChunkChanged(chunk);
	}

	uint8_t World::GetBlock(int x, int y, int z) const
	{
		int chunkX, chunkZ; GetChunkCoords(x, z, chunkX, chunkZ);
		int blockX, blockZ; GetBlockCoords(x, z, blockX, blockZ);
		return GetChunk(chunkX, chunkZ)->GetBlock(blockX, y, blockZ);
	}

	uint8_t World::GetLight(int x, int y, int z) const
	{
		int chunkX, chunkZ; GetChunkCoords(x, z, chunkX, chunkZ);
		int blockX, blockZ; GetBlockCoords(x, z, blockX, blockZ);
		return GetChunk(chunkX, chunkZ)->GetLight(blockX, y, blockZ);
	}

	uint8_t World::GetSkyLight(int x, int y, int z) const
	{
		int chunkX, chunkZ; GetChunkCoords(x, z, chunkX, chunkZ);
		int blockX, blockZ; GetBlockCoords(x, z, blockX, blockZ);
		return GetChunk(chunkX, chunkZ)->GetSkyLight(blockX, y, blockZ);
	}

	void World::OnChunkChanged(Chunk *chunk)
	{
		if(m_onChunkChanged)
		{
			m_onChunkChanged(chunk);
		}
	}

	void World::SetOnChunkLoaded(std::function<void(Chunk *)> cb)
	{
		m_onChunkLoaded = cb;
	}

	void World::SetOnChunkChanged(std::function<void(Chunk *)> cb)
	{
		m_onChunkChanged = cb;
	}

	void World::SetOnChunkUnloaded(std::function<void(Chunk *)> cb)
	{
		m_onChunkUnloaded = cb;
	}

	BlockRegistry &World::GetBlockRegistry()
	{
		return m_blockReg;
	}
}