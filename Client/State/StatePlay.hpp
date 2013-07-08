#ifndef STATE_STATEPLAY_HPP
#define STATE_STATEPLAY_HPP

#include "State.hpp"
#include "../Renderer/Window.hpp"
#include "../WorldRenderer/WorldRenderer.hpp"

namespace Antumbra
{
	class StatePlay : public State
	{
	public:
		StatePlay(Window &window);

		void Update(double dt);
		void Render(double alpha);

		StatePtr GetNextState(StatePtr currentState);
	private:
		void UpdateCameraPos(double dt);
		void UpdateCameraRot();

		World m_world;
		Camera m_camera;
		Window &m_window;
		glm::vec3 m_curCameraPos;
		glm::vec3 m_prevCameraPos;
		WorldRenderer m_worldRenderer;
	};
}

#endif