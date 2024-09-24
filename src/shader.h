#ifndef SHADER_H
#define SHADER_H
#include <string>

enum class ShaderStageType
{
    _NONE = 0,
    VERTEX,
    FRAGMENT,
};

class ShaderStage
{
public:
    ShaderStage(ShaderStageType type, const std::string& source);
    ~ShaderStage();

    unsigned int GetID() { return m_glID; }
private:
    unsigned int m_glID;
};

class Shader
{
public:


    unsigned int GetID() { return m_glID; }
private:
    unsigned int m_glID;

    unsigned int CompileShaderStage(const std::string& source, ShaderStageType type);
    unsigned int LinkProgram(unsigned int vs, unsigned int fs);
};

#endif