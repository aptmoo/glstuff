#ifndef BUFFERS_H
#define BUFFERS_H
#include <vector>
#include <utility>
#include "types.h"
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

    static Ref<StaticGPUBuffer> Create(void* data, unsigned int size);
private:
    unsigned int m_glID;
    unsigned int m_BufferSize;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const Ref<StaticGPUBuffer>& buffer, const GPUDataLayout& layout);

    /**
     * @brief Add index buffer.
     * This clears the previous element buffer!
     * 
     * @param buffer 
     * @param elementType 
     */
    void AddBuffer(const Ref<StaticGPUBuffer>& buffer, GPUType elementType);

    unsigned int GetElementCount();
    unsigned int GetElementCount() const;

    unsigned int GetVertexCount();
    unsigned int GetVertexCount() const;

    bool HasIndexBuffer() { return m_IndexBuffer.get() != nullptr; }

    void Bind();
    void Bind() const;
    void Unbind();
    void Unbind() const;

private:
    /* Added buffers only as smart ptrs, to avoid using deleted buffers */
    std::vector<std::pair<GPUDataLayout, Ref<StaticGPUBuffer>>> m_Buffers;
    unsigned int m_BufferCount; /* Only counts vertex buffers.*/
    Ref<StaticGPUBuffer> m_IndexBuffer;

    GPUType m_ElementBufferType;
    unsigned int m_glID;
};

#endif