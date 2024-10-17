#include "gpuUtils.h"

unsigned int GPUTypeSize(GPUType type)
{
    switch(type)
    {
        case GPUType::_DEFAULT:   return 0;

        case GPUType::FLOAT:      return 4;
        case GPUType::FLOAT2:     return 4 * 2;
        case GPUType::FLOAT3:     return 4 * 3;
        case GPUType::FLOAT4:     return 4 * 4;

        case GPUType::INT:        return 4;
        case GPUType::INT2:       return 4 * 2;
        case GPUType::INT3:       return 4 * 3;
        case GPUType::INT4:       return 4 * 4;

        case GPUType::UINT:       return 4;
        case GPUType::UINT2:      return 4 * 2;
        case GPUType::UINT3:      return 4 * 3;
        case GPUType::UINT4:      return 4 * 4;

        case GPUType::MAT3:       return 3 * 3 * 4;
        case GPUType::MAT4:       return 4 * 4 * 4;

        case GPUType::BOOL:       return 1;
        case GPUType::CHAR:       return 1;
        case GPUType::BYTE:       return 1;

        case GPUType::UCHAR:      return 1;
        case GPUType::UBYTE:      return 1;


        default: return 0;
    }

    return 0;
}

unsigned int GPUTypeElements(GPUType type)
{
    switch(type)
    {
        case GPUType::_DEFAULT:   return 0;

        case GPUType::FLOAT:      return 1;
        case GPUType::FLOAT2:     return 2;
        case GPUType::FLOAT3:     return 3;
        case GPUType::FLOAT4:     return 4;

        case GPUType::INT:        return 1;
        case GPUType::INT2:       return 2;
        case GPUType::INT3:       return 3;
        case GPUType::INT4:       return 4;

        case GPUType::UINT:       return 1;
        case GPUType::UINT2:      return 2;
        case GPUType::UINT3:      return 3;
        case GPUType::UINT4:      return 4;

        case GPUType::MAT3:       return 3 * 3;
        case GPUType::MAT4:       return 4 * 4;

        case GPUType::BOOL:       return 1;
        case GPUType::CHAR:       return 1;
        case GPUType::BYTE:       return 1;

        case GPUType::UCHAR:      return 1;
        case GPUType::UBYTE:      return 1;

        default: return 0;
    }

    return 0;
}