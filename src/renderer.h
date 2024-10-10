#ifndef RENDERER_H
#define RENDERER_H
#include "buffers.h"
#include "shader.h"

class Renderer
{
public:
    Renderer();
    ~Renderer(){};

    void Clear();
    void Clear(float r, float g, float b);

    void Draw(const VertexArray& array, const Shader& shader);

    void SetDepthEnabled(bool enabled);
    void SetStencilEnabled(bool enabled);
private:
    bool m_DepthEnabled;
    bool m_StencilEnabled;
};

#endif