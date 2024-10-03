#include "buffers.h"
#include "glad/glad.h"

GLenum GPUTypeToGL(GPUType type)
{
    switch(type)
    {
        case GPUType::_DEFAULT:   return 0;

        case GPUType::FLOAT:      return GL_FLOAT;
        case GPUType::FLOAT2:     return GL_FLOAT;
        case GPUType::FLOAT3:     return GL_FLOAT;
        case GPUType::FLOAT4:     return GL_FLOAT;

        case GPUType::INT:        return GL_INT;
        case GPUType::INT2:       return GL_INT;
        case GPUType::INT3:       return GL_INT;
        case GPUType::INT4:       return GL_INT;

        case GPUType::UINT:       return GL_UNSIGNED_INT;
        case GPUType::UINT2:      return GL_UNSIGNED_INT;
        case GPUType::UINT3:      return GL_UNSIGNED_INT;
        case GPUType::UINT4:      return GL_UNSIGNED_INT;

        case GPUType::BOOL:       return GL_BOOL;
        case GPUType::CHAR:       return GL_BYTE;

        default: return GL_INVALID_ENUM;
    }

    return GL_INVALID_ENUM;
}

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

void VertexArray::Bind()
{
    glBindVertexArray(m_glID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}