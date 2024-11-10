layout (std140) uniform ub_SceneData
{
    mat4 view;
    mat4 projection;
    vec3 ambient;
    float ambientStrength;
};

layout(std140) uniform ub_MaterialData
{
    // sampler2D s_Albedo;
    // sampler2D s_Spec0;
    // sampler2D s_Texture0;
    float boo;
};

uniform mat4 model;