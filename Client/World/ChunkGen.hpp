#ifndef WORLD_CHUNKGEN_HPP
#define WORLD_CHUNKGEN_HPP

#include "Chunk.hpp"

namespace Antumbra
{
	class ChunkGen
	{
	public:
		void Generate(Chunk &chunk);
	private:
		void PopulateCoal(Chunk &chunk, int x, int y, int z);
		void PopulateIron(Chunk &chunk, int x, int y, int z);
		void PopulateGold(Chunk &chunk, int x, int y, int z);
		void PopulateDiamond(Chunk &chunk, int x, int y, int z);
	};
}

#endif