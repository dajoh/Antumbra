#ifndef RENDERER_WINDOW_HPP
#define RENDERER_WINDOW_HPP

#include <string>
#include <cstdint>
#include <functional>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

namespace Antumbra
{
	enum MouseButton;
	enum InputAction;

	struct KeyEvent;
	struct CharEvent;
	struct MouseEvent;

	class Window
	{
	public:
		Window();
		~Window();

		void SetTitle(const std::string &title);

		void SetSize(int width, int height);
		void GetSize(int &width, int &height) const;

		bool HasFocus() const;
		bool ShouldClose() const;
		bool IsKeyDown(int key) const;

		void SetCursorPos(double x, double y);
		void GetCursorPos(double &x, double &y) const;

		bool IsCursorVisible() const;
		void SetCursorVisible(bool visible);

		void SetOnKeyEvent(std::function<void(KeyEvent)> cb);
		void SetOnCharEvent(std::function<void(CharEvent)> cb);
		void SetOnMouseEvent(std::function<void(MouseEvent)> cb);

		void SwapBuffers();
		void UpdateInput();
	private:
		Window(const Window &);
		Window &operator=(const Window &);

		static void KeyCallback(GLFWwindow *window, int key, int sysKey, int action, int mods);
		static void CharCallback(GLFWwindow *window, unsigned int ch);
		static void MouseCallback(GLFWwindow *window, int button, int action, int mods);

		GLFWwindow *m_window;

		std::function<void(KeyEvent)> m_onKeyEvent;
		std::function<void(CharEvent)> m_onCharEvent;
		std::function<void(MouseEvent)> m_onMouseEvent;
	};

	enum MouseButton
	{
		MouseButton_Left,
		MouseButton_Right,
		MouseButton_Middle
	};

	enum InputAction
	{
		InputAction_Press,
		InputAction_Repeat,
		InputAction_Release
	};

	struct KeyEvent
	{
		int key;
		InputAction action;
	};

	struct CharEvent
	{
		uint32_t ch;
	};

	struct MouseEvent
	{
		MouseButton button;
		InputAction action;
	};
}

#endif