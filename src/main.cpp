#include <iostream>
#include <vector>
#include "window.h"
#include "context.h"
#include "texture.h"
#include "renderer.h"

#include "content.h"
#include "camera.h"

#include "glad/glad.h"
#include "stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

int main(int argc, char const *argv[])
{
    Window window({1280, 720, "Hello OpenGL!"});
    GraphicsContext context(window.GetHandle());
    context.Init();

    ContentManager content;
    Renderer renderer;

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

    GPUDataLayout vbLayout;
    vbLayout.AddElement("Positions", GPUType::FLOAT3);
    vbLayout.AddElement("Colors", GPUType::FLOAT3);
    vbLayout.AddElement("TexCoord0", GPUType::FLOAT2);
    Ref<StaticGPUBuffer> vb = StaticGPUBuffer::Create(&vertices, sizeof(float) * 8 * 4);
    Ref<StaticGPUBuffer> ib = StaticGPUBuffer::Create(&indices, sizeof(float) * 2 * 3);
    VertexArray va;
    va.AddBuffer(ib, GPUType::UINT);
    va.AddBuffer(vb, vbLayout);

    std::vector<float> cubeVertices =
    {
        -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f,

         1.0f, -1.0f, -1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 1.0f,

        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 1.0f
    };

    std::vector<unsigned int> cubeIndices = 
    {
        0, 1, 2,  0, 2, 3,
        6, 5, 4,  7, 6, 4,
        8, 9, 10,  8, 10, 11,
        14, 13, 12,  15, 14, 12,
        16, 17, 18,  16, 18, 19,
        22, 21, 20,  23, 22, 20
    };

    GPUDataLayout cubeLayout;
    cubeLayout.AddElement("Positions", GPUType::FLOAT3);
    cubeLayout.AddElement("Colors", GPUType::FLOAT4);
    cubeLayout.AddElement("TexCoord0", GPUType::FLOAT2);
    Ref<StaticGPUBuffer> cubeVb = StaticGPUBuffer::Create(cubeVertices.data(), sizeof(float) * cubeVertices.size());
    Ref<StaticGPUBuffer> cubeIb = StaticGPUBuffer::Create(cubeIndices.data(), sizeof(unsigned int) * cubeIndices.size());
    VertexArray cubeVa;
    cubeVa.AddBuffer(cubeVb, cubeLayout);
    cubeVa.AddBuffer(cubeIb, GPUType::UINT);

    stbi_set_flip_vertically_on_load(true);
    int width, height, bpp;
    unsigned char* data = stbi_load("awesomeface_16bit.png", &width, &height, &bpp, 0);
    Texture tex(data, (TextureDesc){GPUType::UCHAR, TextureFilter::LINEAR, MipFilter::LINEAR, WrapMode::REPEAT, TextureFormat::RGBA, InternalFormat::RGBA16, width, height});
    tex.Bind(0);
    stbi_image_free(data);

    Ref<Shader> pr = content.Load<Shader>("test");
    pr->SetUniform<int>("texture0", 0);

    Ref<Shader> cubePr = content.Load<Shader>("cube");

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 cubePositions[] = 
    {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    float r;

    CameraTransform camera(glm::vec3(-6.0f, -1.0f, -6.0f));

    while(!window.ShouldClose())
    {
        /* Update stuff */
        r += 0.5f;  
        camera.SetRotation(glm::radians(glm::vec3(0.0f, -45.0f, 0.0f)));
        camera.Update();
        projection = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);


        /* draw stuff*/
        if(window.GetSizeChanged())
            context.SetViewportSize(window.GetSize());        
        renderer.Clear(0.1f, 0.1f, 0.1f);
        
        cubePr->Bind();
        cubePr->SetUniform<glm::mat4>("projection", projection);
        cubePr->SetUniform<glm::mat4>("view", camera.GetViewMatrix());
        cubePr->SetUniform<glm::mat4>("model", glm::mat4(1.0f));
        renderer.Draw(cubeVa, *cubePr);

        window.OnUpdate();
    }
    
    return 0;
}