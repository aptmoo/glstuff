#include "uniformBuffer.h"
#include <cstdlib>
#include <cstring>
#include "glad/glad.h"

UniformBuffer::UniformBuffer(const std::string &name, const GPUDataLayout &layout)
    : m_Name(name), m_Layout(layout)
{
    unsigned int size = m_Layout.GetStride();
    m_Data = malloc(size);
    memset(m_Data, 0, size);
    
    glCreateBuffers(1, &m_glID);
    glNamedBufferData(m_glID, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_glID, 0, size);
    glNamedBufferSubData(m_glID, 0, size, m_Data);
    
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
    free(m_Data);
}