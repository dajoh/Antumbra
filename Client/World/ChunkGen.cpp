#include "Simplex.hpp"
#include "ChunkGen.hpp"
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
	void ChunkGen::Generate(Chunk &chunk)
	{
		int chunkX, chunkZ;
		chunk.GetLocation(chunkX, chunkZ);

		int heightMap[Chunk::Depth][Chunk::Width];

		for(int z = 0; z < Chunk::Depth; z++)
		{
			for(int x = 0; x < Chunk::Width; x++)
			{
				float smoothX = (chunkX * Chunk::Width + x) / 40.0f;
				float smoothZ = (chunkZ * Chunk::Depth + z) / 40.0f;

				heightMap[z][x] = (int)(Simplex2D(smoothX, smoothZ) * 5 + 49);
			}
		}

		for(int y = 0; y < Chunk::Height; y++)
		{
			for(int z = 0; z < Chunk::Depth; z++)
			{
				for(int x = 0; x < Chunk::Width; x++)
				{
					if(y == 0)
					{
						chunk.SetBlock(x, y, z, BlockBedrock::Id);
					}
					else if(y < heightMap[z][x])
					{
						chunk.SetBlock(x, y, z, BlockStone::Id);
						PopulateCoal(chunk, x, y, z);
						PopulateIron(chunk, x, y, z);
						PopulateGold(chunk, x, y, z);
						PopulateDiamond(chunk, x, y, z);
					}
					else if(y == heightMap[z][x])
					{
						chunk.SetBlock(x, y, z, BlockGrass::Id);
					}
					else
					{
						chunk.SetBlock(x, y, z, 0);
					}
				}
			}
		}
	}

	// ------------------------------------------------------------------------
	// These methods could be implemented way better...
	// ------------------------------------------------------------------------

	void ChunkGen::PopulateCoal(Chunk &chunk, int x, int y, int z)
	{
		int chunkX, chunkZ;
		chunk.GetLocation(chunkX, chunkZ);

		auto smoothX = (chunkX * Chunk::Width + x) / 16.0f;
		auto smoothY = y / 16.0f + (64.0f * 1);
		auto smoothZ = (chunkZ * Chunk::Depth + z) / 16.0f;
		auto noise = Simplex3D(smoothX, smoothY, smoothZ);

		if(noise > 0.95)
		{
			chunk.SetBlock(x, y, z, BlockCoalOre::Id);
		}
	}

	void ChunkGen::PopulateIron(Chunk &chunk, int x, int y, int z)
	{
		int chunkX, chunkZ;
		chunk.GetLocation(chunkX, chunkZ);

		auto smoothX = (chunkX * Chunk::Width + x) / 16.0f;
		auto smoothY = y / 16.0f + (64.0f * 2);
		auto smoothZ = (chunkZ * Chunk::Depth + z) / 16.0f;
		auto noise = Simplex3D(smoothX, smoothY, smoothZ);

		if(noise > 0.965)
		{
			chunk.SetBlock(x, y, z, BlockIronOre::Id);
		}
	}

	void ChunkGen::PopulateGold(Chunk &chunk, int x, int y, int z)
	{
		int chunkX, chunkZ;
		chunk.GetLocation(chunkX, chunkZ);

		auto smoothX = (chunkX * Chunk::Width + x) / 16.0f;
		auto smoothY = y / 16.0f + (64.0f * 3);
		auto smoothZ = (chunkZ * Chunk::Depth + z) / 16.0f;
		auto noise = Simplex3D(smoothX, smoothY, smoothZ);

		if(noise > 0.9675)
		{
			chunk.SetBlock(x, y, z, BlockGoldOre::Id);
		}
	}

	void ChunkGen::PopulateDiamond(Chunk &chunk, int x, int y, int z)
	{
		if(y > 40)
		{
			return;
		}

		int chunkX, chunkZ;
		chunk.GetLocation(chunkX, chunkZ);

		auto smoothX = (chunkX * Chunk::Width + x) / 16.0f;
		auto smoothY = y / 16.0f + (64.0f * 4);
		auto smoothZ = (chunkZ * Chunk::Depth + z) / 16.0f;
		auto noise = Simplex3D(smoothX, smoothY, smoothZ);

		if(noise > 0.9675)
		{
			chunk.SetBlock(x, y, z, BlockDiamondOre::Id);
		}
	}
}