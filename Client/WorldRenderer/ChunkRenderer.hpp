#ifndef WORLDRENDERER_CHUNKRENDERER_HPP
#define WORLDRENDERER_CHUNKRENDERER_HPP

#include <memory>
#include "../World/World.hpp"
#include "../World/ChunkCache.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/DynamicMesh.hpp"

namespace Antumbra
{
	typedef std::shared_ptr<class ChunkRenderer> ChunkRendererPtr;

	class ChunkRenderer
	{
	public:
		ChunkRenderer(World &world, Shader &shader);

		void Render() const;
		void Rebuild(const ChunkCache &cache, int x, int z);
	private:
		World &m_world;
		DynamicMesh m_mesh;
	};
}

#endif