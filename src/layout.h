#ifndef LAYOUT_H
#define LAYOUT_H
#include <string>
#include <vector>

enum class GPUType
{
    _DEFAULT = 0,
    FLOAT, FLOAT2, FLOAT3, FLOAT4,
    INT, INT2, INT3, INT4,
    UINT, UINT2, UINT3, UINT4,
    CHAR,
    BOOL,
    MAT3, MAT4,
};

unsigned int GPUTypeSize(GPUType type);
unsigned int GPUTypeElements(GPUType type);

struct GPUDataElement
{
    std::string Name;
    GPUType Type;
    /* TODO: Are size and elementcount neccesary? */
    // unsigned int Size;
    // unsigned int ElementCount;
    unsigned int Offset;
    bool Normalized;
};

class GPUDataLayout
{
public:
    GPUDataLayout(){};
    GPUDataLayout(std::initializer_list<GPUDataElement> elements);
    ~GPUDataLayout(){};

    /**
     * @brief Add element. Forces recalculation of offsets.
     * 
     * @param element 
     */
    void AddElement(const std::string& name, const GPUType& type, bool normalized = false);

    unsigned int GetStride() { return m_Stride; }
    unsigned int GetStride() const { return m_Stride; }

    /* Stl iterators */
    std::vector<GPUDataElement>::iterator begin()        { return m_Elements.begin(); }
    std::vector<GPUDataElement>::iterator end()          { return m_Elements.end(); }
    std::vector<GPUDataElement>::const_iterator begin()  const { return m_Elements.begin(); }
    std::vector<GPUDataElement>::const_iterator end()    const { return m_Elements.end(); }
private:
    std::vector<GPUDataElement> m_Elements;
    unsigned int m_Stride;

    void CalculateOffsets();
};

#endif