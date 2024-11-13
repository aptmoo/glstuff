#include "uniformBuffer.h"
#include <cstdlib>
#include <cstring>
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

UniformBuffer::UniformBuffer(const std::string &name, const GPUDataLayout &layout)
    : m_Name(name), m_Layout(layout)
{
    unsigned int size = m_Layout.GetStride();
    
    glCreateBuffers(1, &m_glID);
    glNamedBufferData(m_glID, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_glID, 0, size);
    // glNamedBufferSubData(m_glID, 0, size, m_Data);
    
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &m_glID);
}


void UniformBuffer::Bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_glID);
}

void UniformBuffer::Unbind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

template<>
void UniformBuffer::SetProperty(const std::string& property, float v)
{
    const GPUDataElement& element = m_Layout.GetElement(property);
    if(element.Type != GPUType::FLOAT)
        return;

    float cv = v;
    glNamedBufferSubData(m_glID, element.Offset, sizeof(float), &cv);}

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::vec3 v)
{
    const GPUDataElement& element = m_Layout.GetElement(property);
    if(element.Type != GPUType::FLOAT3)
        return;
    
    glNamedBufferSubData(m_glID, element.Offset, sizeof(float)*3, glm::value_ptr(v));
}

template<>
void UniformBuffer::SetProperty(const std::string& property, glm::mat4 v)
{
    const GPUDataElement& element = m_Layout.GetElement(property);
    if(element.Type != GPUType::MAT4)
        return;
    
    glNamedBufferSubData(m_glID, element.Offset, sizeof(float)* 4 * 4, glm::value_ptr(v));
}