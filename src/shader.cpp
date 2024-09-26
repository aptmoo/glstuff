#include "shader.h"

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
//     int stageID = stage.GetID();
//     glGetProgramiv(stageID, GL_ACTIVE_UNIFORMS, &uniformCount);

//     if(!uniformCount)
//     {
//         int maxNameLength = 0;
//         int length = 0, count = 0;
//         unsigned int type = GL_NONE;
//         glGetProgramiv(stageID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

//         std::unique_ptr<char[]> uniformName = std::make_unique<char[]>(maxNameLength);
//         for(int i = 0; i < uniformCount; ++i)
//         {
//             glGetActiveUniform(stageID, i, maxNameLength, &length, &count, &type, uniformName.get());
            
//             UniformData data;
//             data.count = count;
//             data.type = type;
//             data.location = glGetUniformLocation(stageID, uniformName.get());

//             std::cout << std::string(uniformName.get(), length) << '\n';
//             m_Uniforms.emplace(std::make_pair(std::string(uniformName.get(), length), data));
//         }
//     }
// }

// void Shader::ClearCachedUniforms()
// {
//     m_Uniforms.clear();
// }
