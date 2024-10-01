#include "buffers.h"
#include "glad/glad.h"

StaticGPUBuffer::StaticGPUBuffer(void* data, unsigned int size)
    : m_BufferSize(size)
{
    glCreateBuffers(1, &m_glID);
    glNamedBufferData(m_glID, size, data, GL_STATIC_DRAW);
}

StaticGPUBuffer::~StaticGPUBuffer()
{
    glDeleteBuffers(1, &m_glID);
}

void VertexArray::AddBuffer(const StaticGPUBuffer& buffer, const GPUDataLayout& layout)
{
    unsigned int count = buffer.GetSize() / layout.GetStride();
    unsigned int attribIndex = 0;

}

void VertexArray::AddBuffer(const StaticGPUBuffer& buffer, GPUType elementType)
{
    unsigned int count = buffer.GetSize() / GPUTypeSize(elementType);
}