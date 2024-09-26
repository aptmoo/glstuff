#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <unordered_map>

struct UniformData
{
    int location, count;
    unsigned int type;
};

class Shader
{
public:
    Shader(const std::string& vs_source, const std::string& fs_source);
    ~Shader();

    void Bind();
    void Unbind();

    template<typename T>
    void SetUniform(const std::string& name, T v){static_assert(0);};
    
    unsigned int GetID(){ return m_glID; }
private:
    unsigned int m_glID;
    std::unordered_map<std::string, UniformData> m_Uniforms;

    unsigned int CompileStage(unsigned int type, const std::string& source);
    unsigned int LinkProgram(unsigned int vs, unsigned int fs);

    void CacheUniforms();
    int GetUniformLocation(const std::string& name);
};

template<>
void Shader::SetUniform(const std::string& name, float v);

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