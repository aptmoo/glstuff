struct EnvLight
{
    vec3 ambient;
    float ambientStrength;
};

#define LIGHT_POINT 0
#define LIGHT_DIRECTIONAL 1

struct Light
{
    vec3 position;
    vec3 color;
    vec3 direction;
    float brightness;
    int type;
};

vec3 CalculateLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, float specularStrength)
{
    vec3 lightDir = vec3(0.0);
    float atten = 1.0;
    if(light.type == LIGHT_POINT)
    {
        lightDir = normalize(light.position - fragPos);
        float dist = length(light.position - fragPos);
        atten = (1.0 / (dist * dist)) * light.brightness;
    }
    else if(light.type == LIGHT_DIRECTIONAL)
    {
        lightDir = normalize(-light.direction);
        atten = light.brightness;
    }

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(specularStrength * spec);

    diffuse *= atten;
    specular *= atten;

    return diffuse + specular;
}