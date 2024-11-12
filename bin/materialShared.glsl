layout (std140) uniform ub_SceneData
{
    mat4 view;
    mat4 projection;
    uniform mat4 model;
    vec3 ambient;
    float ambientStrength;
};

layout(std140) uniform ub_MaterialData
{
    float boo;
};

uniform sampler2D s_Albedo;
uniform sampler2D s_Spec0;
uniform sampler2D s_Texture0;