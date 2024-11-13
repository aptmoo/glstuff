#include "buffers.h"
#include "glad/glad.h"
#include "glutils.h"

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

Ref<StaticGPUBuffer> StaticGPUBuffer::Create(void* data, unsigned int size)
{
    return MakeRef<StaticGPUBuffer>(data, size);
}


VertexArray::VertexArray()
    : m_BufferCount(0)
{
    glCreateVertexArrays(1, &m_glID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_glID);
}


void VertexArray::AddBuffer(const Ref<StaticGPUBuffer>& buffer, const GPUDataLayout& layout)
{
    unsigned int count = buffer->GetSize() / layout.GetStride();
    unsigned int attribIndex = 0;

    glVertexArrayVertexBuffer(m_glID, m_BufferCount, buffer->GetID(), 0, layout.GetStride());
    for(const GPUDataElement& element : layout)
    {
        glEnableVertexArrayAttrib(m_glID, attribIndex);
        glVertexArrayAttribFormat(m_glID, attribIndex, GPUTypeElements(element.Type), GPUTypeToGL(element.Type), element.Normalized, element.Offset);
        glVertexArrayAttribBinding(m_glID, attribIndex, m_BufferCount);
        attribIndex++;
    }

    m_Buffers.push_back({layout, buffer});
    m_BufferCount++;
}

void VertexArray::AddBuffer(const Ref<StaticGPUBuffer>& buffer, GPUType elementType)
{
    glVertexArrayElementBuffer(m_glID, buffer->GetID());
    m_ElementBufferType = elementType;
    m_IndexBuffer = buffer;
}

unsigned int VertexArray::GetElementCount() const
{
    if(m_IndexBuffer.get() != nullptr)
    {
        return m_IndexBuffer->GetSize() / GPUTypeSize(m_ElementBufferType);
    }
    return 0;
}

unsigned int VertexArray::GetVertexCount() const
{
    unsigned size = 0;
    for(auto& vb : m_Buffers)
    {
        size += vb.second->GetSize() / vb.first.GetStride();
    }
    return size;
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_glID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}