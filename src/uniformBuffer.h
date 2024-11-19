#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H
#include <string>
#include <unordered_map>
#include "layout.h"
#include "shader.h"
#include "types.h"

struct UniformBufferMember
{
    GPUType Type;
    unsigned int Offset;
};

/* TODO: Deprecate in favor of simpler class? */
class UniformBuffer
{
public:
    UniformBuffer(const std::string& name, const GPUDataLayout& layout);
    ~UniformBuffer();

    /* TODO: Cache prop offsets */
    template<typename T>
    void SetProperty(const std::string& property, T v) { static_assert(0); }

    unsigned int GetID() const { return m_glID; }
    unsigned int GetSize() const { return m_Stride; }
    const std::string& GetName() const { return m_Name; }
private:
    void Init();
    void Destroy();

    const UniformBufferMember& GetMember(const std::string& name);

    std::string m_Name;
    std::unordered_map<std::string, UniformBufferMember> m_Layout;

    unsigned int m_Stride;

    unsigned int m_glID;
};

template<>
void UniformBuffer::SetProperty(const std::string& property, float v);

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::vec3 v);

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::mat4 v);

#endif