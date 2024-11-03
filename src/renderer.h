#ifndef RENDERER_H
#define RENDERER_H
#include <queue>
#include "buffers.h"
#include "shader.h"

class Renderer
{
public:
    Renderer();
    ~Renderer(){};

    void Clear();
    void Clear(float r, float g, float b);

    void DrawIndexed(const VertexArray& array, const Shader& shader);
    void DrawIndexed(const Ref<VertexArray>& array, const Ref<Shader>& shader);

    void DrawArray(const VertexArray& array, const Shader& shader);
    void DrawArray(const Ref<VertexArray>& array, const Ref<Shader>& shader);


    void SetDepthEnabled(bool enabled);
    void SetStencilEnabled(bool enabled);
private:
    bool m_DepthEnabled;
    bool m_StencilEnabled;
};

#endif