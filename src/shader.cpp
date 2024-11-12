#include "shader.h"
#include <memory>
#include <iostream>
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"


Shader::Shader(const std::string& vs_source, const std::string& fs_source)
{
    unsigned int vs, fs;
    vs = CompileStage(GL_VERTEX_SHADER, vs_source);
    fs = CompileStage(GL_FRAGMENT_SHADER, fs_source);
    m_glID = LinkProgram(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(m_glID);
    CacheUniforms();
}

Shader::~Shader()
{
    glDeleteProgram(m_glID);
}

void Shader::Bind()
{
    glUseProgram(m_glID);
}

void Shader::Bind() const
{
    glUseProgram(m_glID);
}


void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::CompileStage(unsigned int type, const std::string& source)
{
    const char* source_cstr = source.c_str();
    unsigned int id;
    
    id = glCreateShader(type);
    glShaderSource(id, 1, &source_cstr, nullptr);
    glCompileShader(id);
    /* In GL_DEBUG_OUTPUT we trust! */
    return id;
}

unsigned int Shader::LinkProgram(unsigned int vs, unsigned int fs)
{
    unsigned int id;
    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    return id;
}

void Shader::CacheUniforms()
{
    /* TODO: Also precache blocks? */
    int uniformCount = 0;
    glGetProgramiv(m_glID, GL_ACTIVE_UNIFORMS, &uniformCount);
    if(uniformCount != 0)
    {
        int maxNameLength = 0;
        int length = 0, count = 0;
        unsigned int type = GL_NONE;
        glGetProgramiv(m_glID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

        std::unique_ptr<char[]> uniformName = std::make_unique<char[]>(maxNameLength);
        for(int i = 0; i < uniformCount; ++i)
        {
            glGetActiveUniform(m_glID, i, maxNameLength, &length, &count, &type, uniformName.get());
            
            UniformData data;
            data.count = count;
            data.type = type;
            data.location = glGetUniformLocation(m_glID, uniformName.get());

            m_Uniforms.emplace(std::make_pair(std::string(uniformName.get(), length), data));
        }
    }
}

void AttachBuffer(const UniformBuffer &buf)
{
    
}

int Shader::GetUniformLocation(const std::string& name)
{
    if(m_Uniforms.find(name) != m_Uniforms.end())
    {
        return m_Uniforms.at(name).location;
    }

    return glGetUniformLocation(m_glID, name.c_str());  /* Whatever */
}

template<>
void Shader::SetUniform(const std::string& name, float v)
{
    glUniform1f(GetUniformLocation(name), v);
}

template<>
void Shader::SetUniform(const std::string& name, int v)
{
    glUniform1i(GetUniformLocation(name), v);
}

template<>
void Shader::SetUniform(const std::string& name, glm::mat4 v)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
}

template<>
void Shader::SetUniform(const std::string& name, glm::vec3 v)
{
    glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
}

// #include "shader.h"
// #include "glad/glad.h"

// #include <string>
// #include <iostream>
// #include <memory>


// GLenum ShaderStageTypeToGL(ShaderStageType type)
// {
//     switch (type)
//     {
//     case ShaderStageType::_NONE:    return GL_INVALID_ENUM;
//     case ShaderStageType::VERTEX:   return GL_VERTEX_SHADER;
//     case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER;
//     default:                        return GL_INVALID_ENUM;
//     }
//     return GL_INVALID_ENUM;
// }

// GLbitfield ShaderStageTypeToGLBit(ShaderStageType type)
// {
//     switch (type)
//     {
//     case ShaderStageType::_NONE:    return GL_NONE;
//     case ShaderStageType::VERTEX:   return GL_VERTEX_SHADER_BIT;
//     case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER_BIT;
//     default:                        return GL_NONE;
//     }
//     return GL_NONE;
// }

// ShaderStage::ShaderStage(ShaderStageType type, const std::string& source)
//     : m_Type(type)
// {
//     const char* source_cstr = source.c_str();
//     m_glID = glCreateShaderProgramv(ShaderStageTypeToGL(type), 1, &source_cstr);
//     /* No error validation. In GL_DEBUG_OUTPUT we trust! */
// }

// ShaderStage::~ShaderStage()
// {
//     glDeleteProgram(m_glID);
// }

// Shader::Shader()
// {
//     glCreateProgramPipelines(1, &m_glID);
//     glBindProgramPipeline(m_glID);
// }

// Shader::~Shader()
// {
//     glDeleteProgramPipelines(1, &m_glID);
// }

// void Shader::SetStage(const ShaderStage& stage)
// {
//     glUseProgramStages(m_glID, ShaderStageTypeToGLBit(stage.GetType()), stage.GetID());\

//     this->CacheStageUniforms(stage.GetID());
// }

// void Shader::Bind()
// {
//     glBindProgramPipeline(m_glID);
// }

// void Shader::Unbind()
// {
//     glBindProgramPipeline(0);
// }

// void Shader::CacheUniforms()
// {

// }

// void Shader::CacheStageUniforms(const ShaderStage& stage)
// {
//     int uniformCount = 0;
//     int m_glID = stage.GetID();
//     glGetProgramiv(m_glID, GL_ACTIVE_UNIFORMS, &uniformCount);

//     if(!uniformCount)
//     {
//         int maxNameLength = 0;
//         int length = 0, count = 0;
//         unsigned int type = GL_NONE;
//         glGetProgramiv(m_glID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

//         std::unique_ptr<char[]> uniformName = std::make_unique<char[]>(maxNameLength);
//         for(int i = 0; i < uniformCount; ++i)
//         {
//             glGetActiveUniform(m_glID, i, maxNameLength, &length, &count, &type, uniformName.get());
            
//             UniformData data;
//             data.count = count;
//             data.type = type;
//             data.location = glGetUniformLocation(m_glID, uniformName.get());

//             std::cout << std::string(uniformName.get(), length) << '\n';
//             m_Uniforms.emplace(std::make_pair(std::string(uniformName.get(), length), data));
//         }
//     }
// }

// void Shader::ClearCachedUniforms()
// {
//     m_Uniforms.clear();
// }
