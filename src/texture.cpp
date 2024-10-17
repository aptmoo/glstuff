#include "texture.h"
#include "glad/glad.h"
#include "glutils.h"

GLenum FilterToGL(TextureFilter filter)
{
    switch (filter)
    {
    case TextureFilter::DEFAULT:    return GL_LINEAR;
    case TextureFilter::LINEAR:     return GL_LINEAR;
    case TextureFilter::NEAREST:    return GL_NEAREST;
    default:                        return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

GLenum MipFilterToGL(MipFilter filter)
{
    switch (filter)
    {
    case MipFilter::NONE:           return GL_INVALID_ENUM;
    case MipFilter::LINEAR:         return GL_LINEAR_MIPMAP_LINEAR;
    case MipFilter::LINEAR_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
    case MipFilter::NEAREST:        return GL_NEAREST_MIPMAP_NEAREST;
    case MipFilter::NEAREST_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
    default:                        return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

GLenum WrapToGL(WrapMode mode)
{
    switch (mode)
    {
    case WrapMode::DEFAULT:         return GL_REPEAT;
    case WrapMode::REPEAT:          return GL_REPEAT;
    case WrapMode::REPEAT_MIRRORED: return GL_MIRRORED_REPEAT;
    case WrapMode::CLAMP:           return GL_CLAMP_TO_BORDER;
    case WrapMode::CLAMP_STRETCH:   return GL_CLAMP_TO_EDGE;
    default:                        return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

GLenum TextureFormatToGL(TextureFormat format)
{
    switch (format)
    {
    case TextureFormat::DEFAULT:        return GL_RGBA;
    case TextureFormat::RGB:            return GL_RGB;
    case TextureFormat::RGBA:           return GL_RGBA;
    default:                            return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

GLenum InternalFormatToGL(InternalFormat format)
{
    switch (format)
    {
    case InternalFormat::_NONE:         return GL_INVALID_ENUM;
    case InternalFormat::RGBA8:         return GL_RGBA8;
    case InternalFormat::RGBA16:        return GL_RGBA16;
    case InternalFormat::RGB8:          return GL_RGB8;
    case InternalFormat::RGB16:         return GL_RGB16;
    case InternalFormat::RG8:           return GL_RG8;
    case InternalFormat::RG16:          return GL_RG16;
    case InternalFormat::RED8:          return GL_R8;
    case InternalFormat::RED16 :        return GL_R16;
    default:                            return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

Texture::Texture(unsigned char* data, const TextureDesc& desc)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_glID);
    glTextureParameteri(m_glID, GL_TEXTURE_WRAP_S, WrapToGL(desc.wrapMode));
    glTextureParameteri(m_glID, GL_TEXTURE_WRAP_T, WrapToGL(desc.wrapMode));
    glTextureParameteri(m_glID, GL_TEXTURE_MAG_FILTER, FilterToGL(desc.filter));

    if(desc.mipFilter == MipFilter::NONE)
    {
        glTextureParameteri(m_glID, GL_TEXTURE_MIN_FILTER, FilterToGL(desc.filter));
    }
    else
    {
        glTextureParameteri(m_glID, GL_TEXTURE_MIN_FILTER, MipFilterToGL(desc.mipFilter));
    }

    glTextureStorage2D(m_glID, 1, InternalFormatToGL(desc.internalFormat), desc.width, desc.height);
    glTextureSubImage2D(m_glID, 0, 0, 0, desc.width, desc.height, TextureFormatToGL(desc.format), GPUTypeToGL(desc.type), data);

    if(desc.mipFilter != MipFilter::NONE)
        glGenerateTextureMipmap(m_glID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_glID);
}

void Texture::Bind(unsigned int slot)
{
    glBindTextureUnit(slot, m_glID);
}