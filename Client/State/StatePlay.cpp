#include "StatePlay.hpp"

namespace Antumbra
{
	StatePlay::StatePlay(Window &window) : m_window(window), m_worldRenderer(m_world)
	{
		m_window.SetTitle("Antumbra");
		m_window.SetSize(1280, 720);
		m_window.SetCursorVisible(false);
		m_camera.SetAspectRatio(16.0f / 9.0f);

		// Remove ugly white square while loading.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_window.SwapBuffers();

		for(int z = -2; z <= 2; z++)
		{
			for(int x = -2; x <= 2; x++)
			{
				m_world.LoadChunk(x, z);
			}
		}

		glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void StatePlay::Update(double dt)
	{
		m_window.UpdateInput();
		UpdateCameraPos(dt);
	}

	void StatePlay::Render(double alpha)
	{
		if(m_window.HasFocus())
		{
			m_window.UpdateInput();
			UpdateCameraRot();
		}

		m_camera.SetPosition(m_curCameraPos * (float)alpha + m_prevCameraPos * (1.0f - (float)alpha));

		int width, height;
		m_window.GetSize(width, height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{
			m_worldRenderer.Render(m_camera);
		}
		m_window.SwapBuffers();
	}

	StatePtr StatePlay::GetNextState(StatePtr currentState)
	{
		if(m_window.ShouldClose())
		{
			return nullptr;
		}

		return currentState;
	}

	void StatePlay::UpdateCameraPos(double dt)
	{
		m_prevCameraPos = m_curCameraPos;

		if(m_window.IsKeyDown(GLFW_KEY_W))
		{
			m_curCameraPos += m_camera.GetForwardVector() * (float)dt * 20.0f;
		}

		if(m_window.IsKeyDown(GLFW_KEY_A))
		{
			m_curCameraPos += -m_camera.GetRightVector() * (float)dt * 20.0f;
		}

		if(m_window.IsKeyDown(GLFW_KEY_S))
		{
			m_curCameraPos += -m_camera.GetForwardVector() * (float)dt * 20.0f;
		}

		if(m_window.IsKeyDown(GLFW_KEY_D))
		{
			m_curCameraPos += m_camera.GetRightVector() * (float)dt * 20.0f;
		}
	}

	void StatePlay::UpdateCameraRot()
	{
		int width, height;
		m_window.GetSize(width, height);

		double x, y;
		m_window.GetCursorPos(x, y);
		m_window.SetCursorPos(width / 2, height / 2);

		double dx, dy;
		dx = x - width / 2;
		dy = y - height / 2;

		m_camera.OffsetRotation(glm::vec2(dx, dy) * 0.12f);
	}
}