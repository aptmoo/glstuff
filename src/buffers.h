#ifndef BUFFERS_H
#define BUFFERS_H
#include <vector>
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
    void AddBuffer(const StaticGPUBuffer& buffer, const GPUDataLayout& layout);
    void AddBuffer(const StaticGPUBuffer& buffer, GPUType elementType);
private:
    unsigned int m_glID;
    unsigned int m_BufferCount;
};

#endif