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
    unsigned int GetID() const { return m_glID; }

    ShaderStageType GetType() { return m_Type; }
    ShaderStageType GetType() const { return m_Type; }
private:
    ShaderStageType m_Type;
    unsigned int m_glID;
};

class Shader
{
public:
    Shader();
    ~Shader();

    void SetStage(const ShaderStage& stage);

    void Bind();
    void Unbind();

    unsigned int GetID() { return m_glID; }
private:
    unsigned int m_glID;
};

#endif