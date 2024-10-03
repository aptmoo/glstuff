#include "texture.h"
#include "glad/glad.h"

GLenum FilterToGL(TextureFilter filter)
{
    switch (filter)
    {
    case TextureFilter::_NONE:      return GL_INVALID_ENUM;
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
    case WrapMode::_NONE:           return GL_REPEAT;
    case WrapMode::REPEAT:          return GL_REPEAT;
    case WrapMode::REPEAT_MIRRORED: return GL_MIRRORED_REPEAT;
    case WrapMode::CLAMP:           return GL_CLAMP_TO_BORDER;
    case WrapMode::CLAMP_STRETCH:   return GL_CLAMP_TO_EDGE;
    default:                        return GL_INVALID_ENUM;
    }
    return GL_INVALID_ENUM;
}

Texture::Texture(unsigned char* data, const TextureDesc& desc)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_glID);
    glTextureParameteri(m_glID, GL_TEXTURE_WRAP_S, WrapToGL(desc.Wrap));
    glTextureParameteri(m_glID, GL_TEXTURE_WRAP_T, WrapToGL(desc.Wrap));
    glTextureParameteri(m_glID, GL_TEXTURE_MAG_FILTER, FilterToGL(desc.Filter));

    if(desc.Mip == MipFilter::NONE)
    {
        glTextureParameteri(m_glID, GL_TEXTURE_MIN_FILTER, FilterToGL(desc.Filter));
    }
    else
    {
        glTextureParameteri(m_glID, GL_TEXTURE_MIN_FILTER, MipFilterToGL(desc.Mip));
    }

    glTextureStorage2D(m_glID, 1, GL_RGBA8, desc.Width, desc.Height);
    glTextureSubImage2D(m_glID, 0, 0, 0, desc.Width, desc.Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

    if(desc.Mip != MipFilter::NONE)
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