#ifndef _PMTYENGINEGL_WINDOW_H_
#define _PMTYENGINEGL_WINDOW_H_

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>
#include <utility>

namespace pmtyenginegl
{

	class Window
	{
	public:
		Window(std::pair<int, int> size, std::pair<int, int> position, const std::string& name, bool fullscreen = false);
		~Window();

		void setSize(std::pair<int, int> size);
		std::pair<int, int> getSize() const;

		void setPosition(std::pair<int, int> position);
		std::pair<int, int> getPosition() const;

		void setName(const std::string& name);
		const std::string& getName() const { return m_name; }
		
		void setFullscreen(bool fullscreen);
		bool isFullscreen() const { return m_fullscreen; }

		void setVsync(bool vsync);
		bool isVsync() const { return m_vsync; }

		void setClosing(bool closing);
		bool isClosing() const;

		void swapBuffers();
		void select() const;
	private:
		void onSize(int width, int height);
		void onPosition(int left, int top);
	private:
		GLFWwindow* m_window;
		std::pair<int, int> m_size, m_position;
		std::string m_name;
		bool m_fullscreen, m_vsync, m_update;
	};

}

#endif