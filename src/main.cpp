#include <iostream>
#include <vector>
#include "window.h"
#include "context.h"
#include "texture.h"
#include "renderer.h"
#include "uniformBuffer.h"

#include "content.h"
#include "camera.h"

#include "glad/glad.h"
#include "stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "tiny_obj_loader.h"

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
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    0.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,     0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.5f, 0.0f, 1.0f,     0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, -1.0f, 0.0f,  0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, -1.0f, 0.0f,  0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, -1.0f, 0.0f,  0.0f, 0.5f, 1.0f, 1.0f,     1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, -1.0f, 0.0f,  0.0f, 0.5f, 1.0f, 1.0f,     0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.5f, 1.0f,     1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.5f, 1.0f,     0.0f, 1.0f
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
    cubeLayout.AddElement("Normals", GPUType::FLOAT3);
    cubeLayout.AddElement("Colors", GPUType::FLOAT4);
    cubeLayout.AddElement("TexCoord0", GPUType::FLOAT2);
    Ref<StaticGPUBuffer> cubeVb = StaticGPUBuffer::Create(cubeVertices.data(), sizeof(float) * cubeVertices.size());
    Ref<StaticGPUBuffer> cubeIb = StaticGPUBuffer::Create(cubeIndices.data(), sizeof(unsigned int) * cubeIndices.size());
    VertexArray cubeVa;
    cubeVa.AddBuffer(cubeVb, cubeLayout);
    cubeVa.AddBuffer(cubeIb, GPUType::UINT);

    struct MeshVertex
    {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec4 color;
        glm::vec2 texcoord;
    };
    std::vector<MeshVertex> meshVertices;
    
    /* Model import */
    {
        // Uses cube layout
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;
        if(!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "models/miyako_notex_noline.obj"))
        {
            std::cout << warn + err << '\n';
            std::cout << "\nProbably going to crash...\n";
        }

        // vertices.reserve(attrib.vertices.size());
        for(int i = 0; i < shapes.size(); i++)
        {
            tinyobj::shape_t& shape = shapes[i];
            tinyobj::mesh_t& mesh = shape.mesh;
            for(int j = 0; j < mesh.indices.size(); j++)
            {
                MeshVertex vtx;
                tinyobj::index_t idx = mesh.indices.at(j);
                vtx.pos = 
                {
                    attrib.vertices.at(idx.vertex_index * 3),
                    attrib.vertices.at(idx.vertex_index * 3 + 1),
                    attrib.vertices.at(idx.vertex_index * 3 + 2),
                };
                vtx.normal = 
                {
                    attrib.normals.at(idx.normal_index * 3),
                    attrib.normals.at(idx.normal_index * 3 + 1),
                    attrib.normals.at(idx.normal_index * 3 + 2),
                };
                vtx.color = glm::vec4(1.0f);
                vtx.texcoord = 
                {
                    attrib.texcoords.at(idx.texcoord_index * 2),
                    attrib.texcoords.at(idx.texcoord_index * 2 + 1),
                };
                meshVertices.push_back(vtx);
            }
        }
    }

    Ref<StaticGPUBuffer> meshVb = StaticGPUBuffer::Create(meshVertices.data(), meshVertices.size() * sizeof(MeshVertex));
    VertexArray meshVa;
    meshVa.AddBuffer(meshVb, cubeLayout);
    
    /* Import textures */

    stbi_set_flip_vertically_on_load(true);

    int width, height, bpp;
    unsigned char* data = stbi_load("white_2x2.png", &width, &height, &bpp, 0);
    Texture tex(data, (TextureDesc){GPUType::UCHAR, TextureFilter::LINEAR, MipFilter::LINEAR, WrapMode::REPEAT, TextureFormat::RGBA, InternalFormat::RGBA16, width, height});
    tex.Bind(0);
    stbi_image_free(data);

    int width1, height1, bpp1;
    unsigned char* data1 = stbi_load("white_2x2.png", &width1, &height1, &bpp1, 0);
    Texture specTex(data1, (TextureDesc){GPUType::UCHAR, TextureFilter::LINEAR, MipFilter::LINEAR, WrapMode::REPEAT, TextureFormat::RGBA, InternalFormat::RGBA16, width1, height1});
    specTex.Bind(1);
    stbi_image_free(data1);

    Ref<Shader> pr = content.Load<Shader>("test");
    pr->SetUniform<int>("texture0", 0);

    Ref<Shader> cubePr = content.Load<Shader>("cube");
    Ref<Shader> lightboxPr = content.Load<Shader>("lightbox");
    Ref<Shader> blackPr = content.Load<Shader>("black");

    Ref<Shader> ambientPr = content.Load<Shader>("ambient");
    ambientPr->SetUniform("u_EnvLight.ambient", glm::vec3(0.25f, 0.25f, 0.25f));
    ambientPr->SetUniform("u_EnvLight.ambientStrength", 0.5f);

    Ref<Shader> pointLightPr = content.Load<Shader>("pointLight");

    pointLightPr->SetUniform("u_Light.color", glm::vec3(0.1f, 1.0f, 0.9f));
    pointLightPr->SetUniform("u_Light.brightness", 1.0f);
    pointLightPr->SetUniform("u_Light.type", 0);

    GPUDataLayout sceneDataLayout;
    sceneDataLayout.AddElement("view", GPUType::MAT4);
    sceneDataLayout.AddElement("projection", GPUType::MAT4);
    sceneDataLayout.AddElement("model", GPUType::MAT4);
    sceneDataLayout.AddElement("ambientColor", GPUType::FLOAT3);
    sceneDataLayout.AddElement("ambientStrength", GPUType::FLOAT);

    // struct SceneData
    // {
    //     glm::mat4 view, projection, model;
    //     glm::vec3 ambientColor;
    //     float ambientStrength;
    // } sceneData;

    UniformBuffer sceneData("ub_SceneData", sceneDataLayout);

    // unsigned int sceneDataBlock = glGetUniformBlockIndex(ambientPr->GetID(), "ub_SceneData");
    // glUniformBlockBinding(ambientPr->GetID(), sceneDataBlock, 0);

    // unsigned int sceneDataUbo;
    // glCreateBuffers(1, &sceneDataUbo);
    // glNamedBufferData(sceneDataUbo, sizeof(SceneData), nullptr, GL_DYNAMIC_DRAW);
    // glNamedBufferSubData(sceneDataUbo, 0, sizeof(SceneData), &sceneData);
    // // glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // glBindBufferRange(GL_UNIFORM_BUFFER, 0, sceneDataUbo, 0, sizeof(SceneData));


    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    float r;

    CameraTransform camera(glm::vec3(-6, -3, -6));
    glm::vec3 lightPos = glm::vec3(0, 0, 2);

    int frame = 0;

    while(!window.ShouldClose())
    {
        frame++;
        // std::cout << frame << '\n';
        /* Update stuff */
        r += 0.5f;  
        lightPos.x = 2 * sin(0.05f * r);
        lightPos.z = 2 * cos(0.05f * r);
        // lightPos.y = 4 * sin(0.0025f * r);
        camera.SetRotation(glm::radians(glm::vec3(20.0f, -45.0f, 0.0f)));
        camera.Update();
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);


        /* draw stuff*/
        if(window.GetSizeChanged())
        {
            std::cout << "New window size: " << window.GetWidth() << "x" << window.GetHeight()<<'\n';
            context.SetViewportSize(window.GetSize());        
        }
        renderer.Clear(0.0f, 0.0f, 0.0f);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glDepthFunc(GL_LEQUAL);

        glDepthMask(GL_TRUE);
        glColorMask(false, false, false, false);
        {
            blackPr->Bind();
            blackPr->SetUniform("projection", projection);
            blackPr->SetUniform("view", view);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0, -4, 0));
            model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
            model = glm::scale(model, glm::vec3(4));
            // model = glm::rotate(model, 0.1f * r, glm::vec3(0, 1, 0));
            blackPr->SetUniform<glm::mat4>("model", model);
            renderer.DrawArray(meshVa, *blackPr);
        }
        glColorMask(true, true, true, true);
        glDepthMask(GL_FALSE);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        /* Draw lightbox */
        {
            lightboxPr->Bind();
            lightboxPr->SetUniform("projection", projection);
            lightboxPr->SetUniform("view", view);
            glm::mat4 model = glm::mat4(1.0f);
            // model = glm::translate(model, glm::vec3(0, 0, 2));
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.25f));
            lightboxPr->SetUniform("model", model);
            renderer.DrawIndexed(cubeVa, *lightboxPr);

            model = glm::translate(glm::mat4(1.0), glm::vec3(lightPos.z, lightPos.y, lightPos.x));
            model = glm::scale(model, glm::vec3(0.25f));
            lightboxPr->SetUniform("model", model);
            renderer.DrawIndexed(cubeVa, *lightboxPr);
        }
        
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0, -4, 0));
            model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
            model = glm::scale(model, glm::vec3(4));
            sceneData.SetProperty("projection", projection);
            sceneData.SetProperty("view", view);
            sceneData.SetProperty("model", model);
            sceneData.SetProperty("ambientColor", glm::vec3(0.1, 0.1, 0.2));
            sceneData.SetProperty("ambientStrength", 0.5f);

            // sceneData.view = view;
            // sceneData.model = model;
            // sceneData.ambientColor = glm::vec3(0.1, 0.1, 0.2);
            // sceneData.ambientStrength = 0.5f;
            // glNamedBufferSubData(sceneDataUbo, 0, sizeof(SceneData), &sceneData);

            ambientPr->Bind();  
            ambientPr->AttachBuffer(sceneData, 0);
            // ambientPr->SetUniform("projection", projection);
            // ambientPr->SetUniform("view", view);
            // ambientPr->SetUniform<glm::mat4>("model", model);
            renderer.DrawArray(meshVa, *ambientPr);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        /* Draw lit cube */
        {
            pointLightPr->Bind();

            pointLightPr->SetUniform("s_Texture0", 0);
            pointLightPr->SetUniform("s_Spec0", 1);
            pointLightPr->SetUniform("u_ViewPos", camera.GetPosition());


            pointLightPr->SetUniform("projection", projection);
            pointLightPr->SetUniform("view", view);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0, -4, 0));
            model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
            model = glm::scale(model, glm::vec3(4));
            // model = glm::rotate(model, 0.1f * r, glm::vec3(0, 1, 0));
            pointLightPr->SetUniform<glm::mat4>("model", model);

            pointLightPr->SetUniform("u_Light.brightness", 1.0f);
            pointLightPr->SetUniform("u_Light.type", 0);
            
            pointLightPr->SetUniform("u_Light.color", glm::vec3(0.1f, 1.0f, 0.9f));
            pointLightPr->SetUniform("u_Light.position", lightPos);
            renderer.DrawArray(meshVa, *pointLightPr);
            // renderer.DrawIndexed(cubeVa, *pointLightPr);

            pointLightPr->SetUniform("u_Light.color", glm::vec3(1.0f, 0.1f, 0.9f));
            pointLightPr->SetUniform("u_Light.position", glm::vec3(lightPos.z, lightPos.y, lightPos.x));
            renderer.DrawArray(meshVa, *pointLightPr);

            pointLightPr->SetUniform("u_Light.type", 1);
            pointLightPr->SetUniform("u_Light.color", glm::vec3(1.0f, 0.7f, 0.6f));
            pointLightPr->SetUniform("u_Light.position", glm::vec3(1, 1, 1));
            pointLightPr->SetUniform("u_Light.direction", glm::vec3(1.0, -1.0, -1.0));
            renderer.DrawArray(meshVa, *pointLightPr);
            // renderer.DrawIndexed(cubeVa, *pointLightPr);
        }


        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
        // renderer.DrawIndexed(va, *ambientPr);

        window.OnUpdate();
    }
    
    return 0;
}