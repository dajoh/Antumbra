#ifndef WORLD_BLOCKACCESS_HPP
#define WORLD_BLOCKACCESS_HPP

#include <cstdint>

namespace Antumbra
{
	class BlockAccess
	{
	public:
		virtual ~BlockAccess();

		virtual void SetBlock(int x, int y, int z, uint8_t id) = 0;
		virtual void SetLight(int x, int y, int z, uint8_t level) = 0;
		virtual void SetSkyLight(int x, int y, int z, uint8_t level) = 0;

		virtual uint8_t GetBlock(int x, int y, int z) const = 0;
		virtual uint8_t GetLight(int x, int y, int z) const = 0;
		virtual uint8_t GetSkyLight(int x, int y, int z) const = 0;
	};
}

#endif