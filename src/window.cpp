#include "window.h"
#include <stdexcept>
#include "GLFW/glfw3.h"

static unsigned s_WindowCount;

void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
    data->Width = width;
    data->Height = height;
    data->SizeChanged = true;
}

Window::Window(const WindowDesc& desc)
{
    if(!glfwInit())
    {
        throw std::runtime_error("Failed to init GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    m_pWindowHandle = glfwCreateWindow(desc.Width, desc.Height, desc.Title.c_str(), nullptr, nullptr);

    m_Desc.Width = desc.Width;
    m_Desc.Height = desc.Height;
    m_Desc.SizeChanged = true;
    glfwSetWindowUserPointer((GLFWwindow*)m_pWindowHandle, &m_Desc);

    glfwSetFramebufferSizeCallback((GLFWwindow*)m_pWindowHandle, FramebufferResizeCallback);

    if(!m_pWindowHandle)
    {
        throw std::runtime_error("Failed to create window!");
    }

    s_WindowCount++;
}

Window::~Window()
{
    glfwDestroyWindow((GLFWwindow*)m_pWindowHandle);
    s_WindowCount--;

    if(!s_WindowCount)
    {
        glfwTerminate();
    }
}

void Window::OnUpdate()
{
    m_Desc.SizeChanged = false;
    glfwSwapBuffers((GLFWwindow*)m_pWindowHandle);
    glfwPollEvents();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose((GLFWwindow*)m_pWindowHandle);
}