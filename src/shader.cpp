#include "shader.h"
#include "glad/glad.h"

GLenum ShaderStageTypeToGL(ShaderStageType type)
{
    switch (type)
    {
    case ShaderStageType::_NONE:    return GL_INVALID_ENUM;
    case ShaderStageType::VERTEX:   return GL_VERTEX_SHADER_BIT;
    case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER_BIT;
    default:                        return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

ShaderStage::ShaderStage(ShaderStageType type, const std::string& source)
{
    const char* source_cstr = source.c_str();
    m_glID = glCreateShaderProgramv(ShaderStageTypeToGL(type), 1, &source_cstr);
}

ShaderStage::~ShaderStage()
{
    glDeleteProgram(m_glID);
}

