#include "Window.hpp"

namespace Antumbra
{
	Window::Window()
	{
		if(glfwInit() != GL_TRUE)
		{
			throw std::exception("Couldn't initialize GLFW.");
		}

		glfwWindowHint(GLFW_SAMPLES, 8);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		m_window = glfwCreateWindow(640, 480, "RenderWindow", nullptr, nullptr);
		if(!m_window)
		{
			glfwTerminate();
			throw std::exception("Couldn't create window.");
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, KeyCallback);
		glfwSetCharCallback(m_window, CharCallback);
		glfwSetMouseButtonCallback(m_window, MouseCallback);
		glfwMakeContextCurrent(m_window);

		glewExperimental = true;
		if(glewInit() != GLEW_OK)
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
			throw std::exception("Couldn't initialize GLEW.");
		}

		wglSwapIntervalEXT(0);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Window::SetTitle(const std::string &title)
	{
		glfwSetWindowTitle(m_window, title.c_str());
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_window, width, height);
	}

	void Window::GetSize(int &width, int &height) const
	{
		glfwGetWindowSize(m_window, &width, &height);
	}

	bool Window::HasFocus() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GL_TRUE;
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_window) == GL_TRUE;
	}

	bool Window::IsKeyDown(int key) const
	{
		return glfwGetKey(m_window, key) == GLFW_PRESS;
	}

	void Window::SetCursorPos(double x, double y)
	{
		glfwSetCursorPos(m_window, x, y);
	}

	void Window::GetCursorPos(double &x, double &y) const
	{
		glfwGetCursorPos(m_window, &x, &y);
	}

	bool Window::IsCursorVisible() const
	{
		return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
	}

	void Window::SetCursorVisible(bool visible)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}

	void Window::SetOnKeyEvent(std::function<void(KeyEvent)> cb)
	{
		m_onKeyEvent = cb;
	}

	void Window::SetOnCharEvent(std::function<void(CharEvent)> cb)
	{
		m_onCharEvent = cb;
	}

	void Window::SetOnMouseEvent(std::function<void(MouseEvent)> cb)
	{
		m_onMouseEvent = cb;
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	void Window::UpdateInput()
	{
		glfwPollEvents();
	}

	void Window::KeyCallback(GLFWwindow *window, int key, int sysKey, int action, int mods)
	{
		Window *instance = (Window *)glfwGetWindowUserPointer(window);

		if(instance->m_onKeyEvent)
		{
			KeyEvent ev;
			ev.key = key;

			switch(action)
			{
			case GLFW_PRESS: ev.action = InputAction_Press; break;
			case GLFW_REPEAT: ev.action = InputAction_Repeat; break;
			case GLFW_RELEASE: ev.action = InputAction_Release; break;
			default:
				return;
			}

			instance->m_onKeyEvent(ev);
		}
	}

	void Window::CharCallback(GLFWwindow *window, unsigned int ch)
	{
		Window *instance = (Window *)glfwGetWindowUserPointer(window);

		if(instance->m_onCharEvent)
		{
			CharEvent ev;
			ev.ch = ch;
			instance->m_onCharEvent(ev);
		}
	}

	void Window::MouseCallback(GLFWwindow *window, int button, int action, int mods)
	{
		Window *instance = (Window *)glfwGetWindowUserPointer(window);

		if(instance->m_onMouseEvent)
		{
			MouseEvent ev;

			switch(action)
			{
			case GLFW_PRESS: ev.action = InputAction_Press; break;
			case GLFW_REPEAT: ev.action = InputAction_Repeat; break;
			case GLFW_RELEASE: ev.action = InputAction_Release; break;
			default:
				return;
			}

			switch(button)
			{
			case GLFW_MOUSE_BUTTON_LEFT: ev.button = MouseButton_Left; break;
			case GLFW_MOUSE_BUTTON_RIGHT: ev.button = MouseButton_Right; break;
			case GLFW_MOUSE_BUTTON_MIDDLE: ev.button = MouseButton_Middle; break;
			default:
				return;
			}

			instance->m_onMouseEvent(ev);
		}
	}
}