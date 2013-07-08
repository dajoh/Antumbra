#include "ChunkRenderer.hpp"
#include "../World/Blocks/BlockGrass.hpp"

namespace Antumbra
{
	ChunkRenderer::ChunkRenderer(World &world, Shader &shader) : m_world(world)
	{
		m_mesh.LinkShader(shader);
	}

	void ChunkRenderer::Render() const
	{
		m_mesh.Draw();
	}

	void ChunkRenderer::Rebuild(const ChunkCache &cache, int chunkX, int chunkZ)
	{
		BlockRegistry &blockReg = m_world.GetBlockRegistry();

		m_mesh.StartBuilding(GL_TRIANGLES);

		for(int y = 0; y < Chunk::Height; y++)
		{
			for(int z = 0; z < Chunk::Depth; z++)
			{
				for(int x = 0; x < Chunk::Width; x++)
				{
					int worldX = chunkX * Chunk::Width + x;
					int worldZ = chunkZ * Chunk::Depth + z;

					auto base = glm::vec3(x, y, z);
					auto blockId = cache.GetBlock(worldX, y, worldZ);
					
					if(blockId == 0)
					{
						continue;
					}

					auto blockPtr = blockReg[blockId];

					uint8_t adjBlocks[] =
					{
						cache.GetBlock(worldX + 1, y, worldZ),
						cache.GetBlock(worldX - 1, y, worldZ),
						cache.GetBlock(worldX, y + 1, worldZ),
						cache.GetBlock(worldX, y - 1, worldZ),
						cache.GetBlock(worldX, y, worldZ + 1),
						cache.GetBlock(worldX, y, worldZ - 1)
					};

					uint8_t adjLight[] =
					{
						cache.GetLight(worldX + 1, y, worldZ),
						cache.GetLight(worldX - 1, y, worldZ),
						cache.GetLight(worldX, y + 1, worldZ),
						cache.GetLight(worldX, y - 1, worldZ),
						cache.GetLight(worldX, y, worldZ + 1),
						cache.GetLight(worldX, y, worldZ - 1)
					};

					m_mesh.SetColor(glm::vec3(1, 1, 1));

					if(adjBlocks[Direction_Right] == 0)
					{
						glm::vec3 baseTex(0, 0, blockPtr->GetTexture(Direction_Right));

						m_mesh.SetPosition(base + glm::vec3(0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(0.5f,  0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();
					}

					if(adjBlocks[Direction_Left] == 0)
					{
						glm::vec3 baseTex(0, 0, blockPtr->GetTexture(Direction_Left));

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();
					}

					if(adjBlocks[Direction_Up] == 0)
					{
						if(blockId == BlockGrass::Id)
						{
							m_mesh.SetColor(glm::vec3(0.48f, 1.0f, 0.38f));
						}

						glm::vec3 baseTex(0, 0, blockPtr->GetTexture(Direction_Up));

						m_mesh.SetPosition(base + glm::vec3( 0.5f, 0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, 0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, 0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, 0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, 0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, 0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						if(blockId == BlockGrass::Id)
						{
							m_mesh.SetColor(glm::vec3(1, 1, 1));
						}
					}

					if(adjBlocks[Direction_Down] == 0)
					{
						glm::vec3 baseTex(0, 0, blockPtr->GetTexture(Direction_Down));

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f,  0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();
					}

					if(adjBlocks[Direction_Forward] == 0)
					{
						glm::vec3 baseTex(0, 0, blockPtr->GetTexture(Direction_Forward));

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f, 0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f, 0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f, 0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f, 0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f,  0.5f, 0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f, 0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();
					}

					if(adjBlocks[Direction_Backward] == 0)
					{
						glm::vec3 baseTex(0, 0, blockPtr->GetTexture(Direction_Backward));

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 0, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3(-0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(1, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f,  0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 1, 0));
						m_mesh.Advance();

						m_mesh.SetPosition(base + glm::vec3( 0.5f, -0.5f, -0.5f));
						m_mesh.SetTexCoord(baseTex + glm::vec3(0, 0, 0));
						m_mesh.Advance();
					}
				}
			}
		}

		m_mesh.StopBuilding();
	}
}