#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <unordered_map>

class Shader
{
public:
    Shader(const std::string& vs_source, const std::string& fs_source);
    ~Shader();

private:
    unsigned int m_glID;

    unsigned int CompileStage(unsigned int type, const std::string& source);
    void LinkProgram(unsigned int vs, unsigned int fs);
};

#endif

// #ifndef SHADER_H
// #define SHADER_H
// #include <string>
// #include <unordered_map>

// enum class ShaderStageType
// {
//     _NONE = 0,
//     VERTEX,
//     FRAGMENT,
// };

// struct UniformData
// {
//     int location, count;
//     unsigned int type;
// };

// class ShaderStage
// {
// public:
//     ShaderStage(ShaderStageType type, const std::string& source);
//     ~ShaderStage();

//     unsigned int GetID() { return m_glID; }
//     unsigned int GetID() const { return m_glID; }

//     ShaderStageType GetType() { return m_Type; }
//     ShaderStageType GetType() const { return m_Type; }
// private:
//     ShaderStageType m_Type;
//     unsigned int m_glID;
// };

// class Shader
// {
// public:
//     Shader();
//     ~Shader();

//     void SetStage(const ShaderStage& stage);

//     void Bind();
//     void Unbind();

//     void CacheUniforms();
//     void ClearCachedUniforms();

//     unsigned int GetID() { return m_glID; }
// private:
//     unsigned int m_glID;

//     std::unordered_map<std::string, UniformData> m_Uniforms;
//     void CacheStageUniforms(const ShaderStage& stage);
// };

// #endif