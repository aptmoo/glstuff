#include "glutils.h"

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
        case GPUType::BYTE:       return GL_BYTE;

        case GPUType::UCHAR:       return GL_UNSIGNED_BYTE;
        case GPUType::UBYTE:       return GL_UNSIGNED_BYTE;

        default: return GL_INVALID_ENUM;
    }

    return GL_INVALID_ENUM;
}