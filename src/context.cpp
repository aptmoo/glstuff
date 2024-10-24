#include "context.h"
#include <stdexcept>
#include <iostream>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include "GLFW/glfw3.h"
#include "glad/glad.h"

static void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const*)
{
    auto const src_str = [source]() 
    {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW_SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
        default: return "UNKNOWN";
		}
	}();

	auto const type_str = [type]() 
    {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
        default: return "UNKNOWN";
		}
	}();

	auto const polite_type_str = [type]() 
    {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "deprecation notice";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "undefined behaviour notif";
		case GL_DEBUG_TYPE_PORTABILITY: return "portability error";
		case GL_DEBUG_TYPE_PERFORMANCE: return "performance notif";
		case GL_DEBUG_TYPE_MARKER: return "marker";
		case GL_DEBUG_TYPE_OTHER: return "misc notification";
        default: return "UNKNOWN";
		}
	}();

	auto const severity_str = [severity]()
    {
		switch (severity) 
        {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
        default: return "UNKNOWN";
		}
	}();

    std::cout << "GL " << polite_type_str << " from " << src_str << ", type=" << type_str << ", sev=" << severity_str << ", obj id=" << id << ":\n" << message << "\n---------------\n";
	getchar();
}

GraphicsContext::GraphicsContext(void* handle)
    : m_pWindowHandle(handle)
{}

GraphicsContext::~GraphicsContext(){};

void GraphicsContext::Init()
{
    glfwMakeContextCurrent((GLFWwindow*)m_pWindowHandle);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to init Glad!");
    }

    #ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugMessageCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    #endif
}

void GraphicsContext::Swap()
{
    glfwSwapBuffers((GLFWwindow*)m_pWindowHandle);
}

void GraphicsContext::SetViewportSize(Size2D size)
{
    glViewport(0, 0, size.width, size.height);
}

void GraphicsContext::SetViewportSize(VieportSize size)
{
    glViewport(size.x, size.y, size.width, size.height);
}