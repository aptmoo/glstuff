#include <iostream>
#include "window.h"
#include "context.h"

#include "glad/glad.h"

int main(int argc, char const *argv[])
{
    Window window({1280, 720, "Hello OpenGL!"});
    GraphicsContext context(window.GetHandle());
    context.Init();

    float vertices[] = 
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };  

    unsigned int indices[] = 
    {
        0, 1, 3,   /* T0 */
        1, 2, 3    /* T1 */
    }; 

    unsigned int vbo, ibo, vao;
    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, sizeof(float) * 3 * 4, &vertices, GL_STATIC_DRAW);

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, sizeof(int) * 2 * 3, &indices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);
    glVertexArrayElementBuffer(vao, ibo);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);

    std::string vs_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    std::string fs_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
    const char* vs_cstring = vs_source.c_str();
    const char* fs_cstring = fs_source.c_str();

    unsigned int vs, fs, pr;
    vs = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vs_cstring);
    fs = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fs_cstring);
    glCreateProgramPipelines(1, &pr);
    glUseProgramStages(pr, GL_VERTEX_SHADER_BIT, vs);
    glUseProgramStages(pr, GL_FRAGMENT_SHADER_BIT, fs);
    glBindProgramPipeline(pr);

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

    glDeleteProgram(vs);

    return 0;
}
