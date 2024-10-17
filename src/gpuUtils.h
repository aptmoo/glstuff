#ifndef GPU_UTILS_H
#define GPU_UTILS_H

enum class GPUType
{
    _DEFAULT = 0,
    FLOAT, FLOAT2, FLOAT3, FLOAT4,
    INT, INT2, INT3, INT4,
    UINT, UINT2, UINT3, UINT4,
    CHAR, BYTE,
    UCHAR, UBYTE,
    BOOL,
    MAT3, MAT4,
};

unsigned int GPUTypeSize(GPUType type);
unsigned int GPUTypeElements(GPUType type);


#endif