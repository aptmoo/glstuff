#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H
#include <string>
#include <variant>
#include "layout.h"
#include "shader.h"
#include "types.h"

class UniformBuffer
{
public:
    UniformBuffer(const std::string& name, const GPUDataLayout& layout);
    ~UniformBuffer();

    /* TODO: Cache prop offsets */
    template<typename T>
    void SetProperty(const std::string& property, T v) { static_assert(0); }

    void Bind() const;
    void Unbind() const;

    unsigned int GetID() { return m_glID; }
    unsigned int GetID() const { return m_glID; }

    unsigned int GetSize() { return m_Layout.GetStride(); }
    unsigned int GetSize() const { return m_Layout.GetStride(); }

    const std::string& GetName() { return m_Name; }
    const std::string& GetName() const { return m_Name; }
private:
    std::string m_Name;

    GPUDataLayout m_Layout;

    unsigned int m_glID;
};

template<>
void UniformBuffer::SetProperty(const std::string& property, float v);

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::vec3 v);

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::mat4 v);

#endif