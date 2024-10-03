#ifndef TEXTURE_H
#define TEXTURE_H

enum class TextureFilter
{
    _NONE = 0,
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
    _NONE = 0,
    REPEAT,
    REPEAT_MIRRORED,
    CLAMP,
    CLAMP_STRETCH,
};

struct TextureDesc
{
    TextureFilter Filter;
    MipFilter Mip;    // Set to NONE for no filtering
    WrapMode Wrap;
    int Width, Height;
};

class Texture
{
public:
    Texture(unsigned char* data, const TextureDesc& desc);
    ~Texture();

    void Bind(unsigned int slot);

    int GetWidth()          { return m_desc.Width;     }
    int GetHeight()         { return m_desc.Height;    }
    MipFilter GetMipFilter()         { return m_desc.Mip; }
    TextureFilter GetTextureFilter() { return m_desc.Filter;    }
    TextureDesc GetDesc()            { return m_desc;           }
private:
    TextureDesc m_desc;
    unsigned int m_glID;
};

#endif