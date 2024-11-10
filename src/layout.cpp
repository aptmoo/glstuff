#include "layout.h"

GPUDataLayout::GPUDataLayout(std::initializer_list<GPUDataElement> elements)
    : m_Elements(elements)
{
    CalculateOffsets();
}

void GPUDataLayout::AddElement(const std::string& name, const GPUType& type, bool normalized)
{
    m_Elements.push_back({name, type, 0, normalized});
    CalculateOffsets();
}

static GPUDataElement s_EmptyElement = {"error", GPUType::_DEFAULT, 0, false};

const GPUDataElement& GPUDataLayout::GetElement(const std::string& name)
{
    for(const GPUDataElement& e : m_Elements)
    {
        if(e.Name == name)
        {
            return e;
        }
    }

    return s_EmptyElement;
}

const GPUDataElement& GPUDataLayout::GetElement(const std::string& name) const
{
    for(const GPUDataElement& e : m_Elements)
    {
        if(e.Name == name)
        {
            return e;
        }
    }

    return s_EmptyElement;
}

void GPUDataLayout::CalculateOffsets()
{
    m_Stride = 0;
    unsigned int currentOffset = 0;
    for(GPUDataElement& element : m_Elements)
    {
        element.Offset = currentOffset;
        currentOffset += GPUTypeSize(element.Type);
        m_Stride += GPUTypeSize(element.Type);
    }
}