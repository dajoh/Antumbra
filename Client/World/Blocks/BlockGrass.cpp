#include "BlockGrass.hpp"

namespace Antumbra
{
	uint8_t BlockGrass::GetId() const
	{
		return Id;
	}

	int BlockGrass::GetTexture(Direction direction) const
	{
		return m_textures[direction];
	}

	void BlockGrass::RegisterTextures(TextureRegistry &textureReg)
	{
		int top = textureReg.RegisterTexture("textures/grass_top.png");
		int side = textureReg.RegisterTexture("textures/grass_side.png");
		int bottom = textureReg.RegisterTexture("textures/grass_bottom.png");

		m_textures[Direction_Right] = side;
		m_textures[Direction_Left] = side;
		m_textures[Direction_Up] = top;
		m_textures[Direction_Down] = bottom;
		m_textures[Direction_Forward] = side;
		m_textures[Direction_Backward] = side;
	}
}