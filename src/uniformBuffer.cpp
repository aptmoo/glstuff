#include "uniformBuffer.h"
#include <cstdlib>
#include <cstring>
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include <iostream>

UniformBuffer::UniformBuffer(const std::string &name, const GPUDataLayout &layout)
    : m_Name(name)
{
    unsigned int size = 0;
    
    for(const GPUDataElement& e : layout)
    {
        size += e.Offset;
        UniformBufferMember m{e.Type, e.Offset};
        m_Layout.emplace(e.Name, m);
    }

    m_Stride = size;
    Init();
}

UniformBuffer::~UniformBuffer()
{
    Destroy();
}

void UniformBuffer::Init()
{
    glCreateBuffers(1, &m_glID);
    glNamedBufferData(m_glID, m_Stride, nullptr, GL_DYNAMIC_DRAW);
}

void UniformBuffer::Destroy()
{
    glDeleteBuffers(1, &m_glID);
}

const UniformBufferMember& UniformBuffer::GetMember(const std::string& name)
{
    if(m_Layout.find(name) != m_Layout.end())
    {
        return m_Layout.at(name);
    }

    static UniformBufferMember s_DefaultMember{GPUType::_DEFAULT, 0};
    // Whatever setproperty handles this
    return s_DefaultMember;
}

template<>
void UniformBuffer::SetProperty(const std::string& property, float v)
{
    const UniformBufferMember& element = GetMember(property);
    if(element.Type != GPUType::FLOAT)
        return;

    float cv = v;
    glNamedBufferSubData(m_glID, element.Offset, sizeof(float), &cv);
}

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::vec3 v)
{
    const UniformBufferMember& element = GetMember(property);
    if(element.Type != GPUType::FLOAT3)
        return;
    
    glNamedBufferSubData(m_glID, element.Offset, sizeof(float)*3, glm::value_ptr(v));
}

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::mat4 v)
{
    const UniformBufferMember& element = GetMember(property);
    if(element.Type != GPUType::MAT4)
        return;
    
    glNamedBufferSubData(m_glID, element.Offset, sizeof(float)* 4 * 4, glm::value_ptr(v));
}