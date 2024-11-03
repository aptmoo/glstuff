#include "renderer.h"
#include "glad/glad.h"

Renderer::Renderer()
{
    SetDepthEnabled(true);
    SetStencilEnabled(false);
}

void Renderer::Clear()
{
    GLbitfield flags = GL_COLOR_BUFFER_BIT;

    if(m_DepthEnabled)
    {
        flags = flags | GL_DEPTH_BUFFER_BIT;
    }

    if(m_StencilEnabled)
    {
        flags = flags | GL_STENCIL_BUFFER_BIT;
    }

    glClear(flags);
}

void Renderer::Clear(float r, float g, float b)
{
    GLbitfield flags = GL_COLOR_BUFFER_BIT;

    if(m_DepthEnabled)
    {
        flags = flags | GL_DEPTH_BUFFER_BIT;
    }

    if(m_StencilEnabled)
    {
        flags = flags | GL_STENCIL_BUFFER_BIT;
    }

    glClearColor(r, g, b, 1.0f);
    glClear(flags);
}

void Renderer::DrawIndexed(const VertexArray& array, const Shader& shader)
{
    shader.Bind();
    array.Bind();
    glDrawElements(GL_TRIANGLES, array.GetElementCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawIndexed(const Ref<VertexArray>& array, const Ref<Shader>& shader)
{
    shader->Bind();
    array->Bind();
    glDrawElements(GL_TRIANGLES, array->GetElementCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawArray(const VertexArray& array, const Shader& shader)
{
    shader.Bind();
    array.Bind();
    glDrawArrays(GL_TRIANGLES, 0, array.GetVertexCount());
}

void Renderer::DrawArray(const Ref<VertexArray>& array, const Ref<Shader>& shader)
{
    shader->Bind();
    array->Bind();
    glDrawArrays(GL_TRIANGLES, 0, array->GetVertexCount());
}

void Renderer::SetDepthEnabled(bool enabled)
{
    m_DepthEnabled = enabled;
    if(enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void Renderer::SetStencilEnabled(bool enabled)
{
    m_StencilEnabled = enabled;
    if(enabled)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);
}