#ifndef BUFFERS_H
#define BUFFERS_H
#include <vector>
#include <utility>
#include "layout.h"

class StaticGPUBuffer
{
public:
    StaticGPUBuffer(void* data, unsigned int size);
    ~StaticGPUBuffer();

    unsigned int GetID() { return m_glID; }
    unsigned int GetID() const { return m_glID; }
    unsigned int GetSize() { return m_BufferSize; }
    unsigned int GetSize() const { return m_BufferSize; }
    
private:
    unsigned int m_glID;
    unsigned int m_BufferSize;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const StaticGPUBuffer& buffer, const GPUDataLayout& layout);
    void AddBuffer(const StaticGPUBuffer& buffer, GPUType elementType);

    void Bind();
    void Unbind();
private:
    std::vector<std::pair<GPUDataLayout, StaticGPUBuffer>> m_Buffers;
    unsigned int m_BufferCount;

    GPUType m_ElementBufferType;
    unsigned int m_glID;
};

#endif