#include "pmtyenginegl/window.h"

#include <stdexcept>

namespace pmtyenginegl
{

    static std::uint64_t s_windowCount;

    Window::Window(std::pair<int, int> size, std::pair<int, int> position, const std::string& name, bool fullscreen)
        : m_size(size), m_position(position), m_name(name), m_fullscreen(fullscreen), m_vsync(false), m_update(false)
    {
        if (s_windowCount == 0)
        {
            if (!glfwInit())
                throw std::runtime_error("failed to initialize glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        if (fullscreen)
        {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            m_window = glfwCreateWindow(mode->width, mode->height, name.c_str(), monitor, nullptr);
        }
        else
        {
            m_window = glfwCreateWindow(size.first, size.second, name.c_str(), nullptr, nullptr);
            glfwSetWindowPos(m_window, position.first, position.second);
        }

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, this);

        if (s_windowCount == 0)
        {
            if (!gladLoadGL(glfwGetProcAddress))
                throw std::runtime_error("failed to initialize glad");
        }

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            Window* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
            userWindow->onSize(width, height);
        });

        glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int left, int top)
        {
            Window* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
            userWindow->onPosition(left, top);
        });

        s_windowCount++;
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
        if (s_windowCount == 1)
            glfwTerminate();

        s_windowCount--;
    }

    void Window::setSize(std::pair<int, int> size)
    {
        m_size = size;
        glfwSetWindowSize(m_window, size.first, size.second);
    }

    std::pair<int, int> Window::getSize() const
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return { width, height };
    }

    void Window::setName(const std::string& name)
    {
        glfwSetWindowTitle(m_window, name.c_str());
        m_name = name;
    }

    void Window::setPosition(std::pair<int, int> position)
    {
        glfwSetWindowPos(m_window, position.first, position.second);
        m_position = position;
    }

    std::pair<int, int> Window::getPosition() const
    {
        int left, top;
        glfwGetWindowPos(m_window, &left, &top);
        return { left, top };
    }

    void Window::setFullscreen(bool fullscreen)
    {
        if (fullscreen)
        {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(m_window, nullptr, m_position.first, m_position.second, m_size.first, m_size.second, 0);
        }

        m_fullscreen = fullscreen;
    }

    void Window::setVsync(bool vsync)
    {
        glfwSwapInterval(vsync);
        m_vsync = vsync;
    }

    void Window::setClosing(bool closing)
    {
        glfwSetWindowShouldClose(m_window, closing);
    }

    bool Window::isClosing() const
    {
        while (!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();
            return false;
        }

        return true;
    }

    void Window::swapBuffers()
    {
        if (m_update)
        {
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
            glViewport(0, 0, framebufferWidth, framebufferHeight);
            m_update = false;
        }

        glfwSwapBuffers(m_window);
    }

    void Window::select() const
    {
        glfwMakeContextCurrent(m_window);
    }

    void Window::onSize(int width, int height)
    {
        if (!m_fullscreen)
            m_size = { width, height };

        m_update = true;
    }

    void Window::onPosition(int left, int top)
    {
        if (!m_fullscreen)
            m_position = { left, top };

        m_update = true;
    }

}