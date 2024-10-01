#include <iostream>
#include "window.h"
#include "context.h"
#include "shader.h"
#include "buffers.h"

#include "content.h"

#include "glad/glad.h"
#include "stb_image.h"

int main(int argc, char const *argv[])
{
    Window window({1280, 720, "Hello OpenGL!"});
    GraphicsContext context(window.GetHandle());
    context.Init();

    ContentManager content;

    float vertices[] = 
    {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };  

    unsigned int indices[] = 
    {
        0, 1, 3,   /* T0 */
        1, 2, 3    /* T1 */
    }; 

    StaticGPUBuffer vb(&vertices, sizeof(float) * 8 * 4);
    StaticGPUBuffer ib(&indices, sizeof(float) * 2 * 3);

    unsigned int vao;

    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vb.GetID(), 0, sizeof(float) * 8);
    glVertexArrayElementBuffer(vao, ib.GetID());

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);

    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glVertexArrayAttribBinding(vao, 1, 0);

    glEnableVertexArrayAttrib(vao, 2);
    glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
    glVertexArrayAttribBinding(vao, 2, 0);

    stbi_set_flip_vertically_on_load(true);
    int width, height, bpp;
    unsigned char* data = stbi_load("awesomeface.png", &width, &height, &bpp, 0);

    unsigned int texture;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTextureUnit(0, texture);
    
    stbi_image_free(data);

    Ref<Shader> pr = content.Load<Shader>("test");
    pr->Bind();
    pr->SetUniform<int>("texture1", 0);

    while(!window.ShouldClose())
    {
        if(window.GetSizeChanged())
            context.SetViewportSize(window.GetSize());

        glClearColor(0.1, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.OnUpdate();
    }
    
    return 0;
}