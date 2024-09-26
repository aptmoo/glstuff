#include "shader.h"
#include "glad/glad.h"


GLenum ShaderStageTypeToGL(ShaderStageType type)
{
    switch (type)
    {
    case ShaderStageType::_NONE:    return GL_INVALID_ENUM;
    case ShaderStageType::VERTEX:   return GL_VERTEX_SHADER;
    case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER;
    default:                        return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

GLbitfield ShaderStageTypeToGLBit(ShaderStageType type)
{
    switch (type)
    {
    case ShaderStageType::_NONE:    return GL_NONE;
    case ShaderStageType::VERTEX:   return GL_VERTEX_SHADER_BIT;
    case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER_BIT;
    default:                        return GL_NONE;
    }
    return GL_NONE;
}

ShaderStage::ShaderStage(ShaderStageType type, const std::string& source)
    : m_Type(type)
{
    const char* source_cstr = source.c_str();
    m_glID = glCreateShaderProgramv(ShaderStageTypeToGL(type), 1, &source_cstr);
    /* No error validation. In GL_DEBUG_OUTPUT we trust! */
}

ShaderStage::~ShaderStage()
{
    glDeleteProgram(m_glID);
}

Shader::Shader()
{
    glCreateProgramPipelines(1, &m_glID);
}

Shader::~Shader()
{
    glDeleteProgramPipelines(1, &m_glID);
}

void Shader::SetStage(const ShaderStage& stage)
{
    glUseProgramStages(m_glID, ShaderStageTypeToGLBit(stage.GetType()), stage.GetID());
}

void Shader::Bind()
{
    glBindProgramPipeline(m_glID);
}

void Shader::Unbind()
{
    glBindProgramPipeline(0);
}