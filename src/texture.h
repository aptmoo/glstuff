#ifndef TEXTURE_H
#define TEXTURE_H

enum class TextureFilter
{
    DEFAULT = 0,
    NEAREST,
    LINEAR,
};

enum class MipFilter
{
    NONE = 0,   // WOO none used for once
    NEAREST,
    NEAREST_LINEAR,
    LINEAR,
    LINEAR_NEAREST,
};

enum class WrapMode
{
    DEFAULT = 0,
    REPEAT,
    REPEAT_MIRRORED,
    CLAMP,
    CLAMP_STRETCH,
};

// TODO: unused. Use.
enum class TextureFormat
{
    DEFAULT = 0, // RGBA assumed
    RGB, 
    RGBA,
    RG,
    RED,
    // TODO: More formats when needed
};

enum class InternalFormat
{
    _NONE = 0,
    RGBA8,
    RGBA16,
    RGB8,
    RGB16,
    RG8,
    RG16,
    RED8,
    RED16,
};

struct TextureDesc
{
    TextureFilter filter;
    MipFilter mipFilter;    // Set to NONE for no filtering
    WrapMode wrapMode;
    TextureFormat format;
    InternalFormat internalFormat;
    int width, height;
};

class Texture
{
public:
    Texture(unsigned char* data, const TextureDesc& desc);
    ~Texture();

    void Bind(unsigned int slot);

    int GetWidth()          { return m_desc.width;     }
    int GetHeight()         { return m_desc.height;    }
    MipFilter GetMipFilter()         { return m_desc.mipFilter; }
    TextureFilter GetTextureFilter() { return m_desc.filter;    }
    TextureDesc GetDesc()            { return m_desc;           }
private:
    TextureDesc m_desc;
    unsigned int m_glID;
};

#endif