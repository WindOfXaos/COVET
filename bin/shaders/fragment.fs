#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float reflectivity;
    float shininess;
};

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

struct SpotLight {
    vec3  position;
    vec3  direction;

    float cutOffInner;
    float cutOffOuter;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant; 
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 32

in vec2 TextCoord;
in vec3 Normal;
in vec3 FragPos;

uniform bool lamp = false;
uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int nmPointLights;
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    // temporary fix
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    // phase 2: Point lights
    for(int i = 0; i < nmPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    
    // phase 3: Spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir); 

    // applying emission map
    vec3 emission = vec3(texture(material.emission, TextCoord));
    if (lamp) emission *= pointLights[0].diffuse;
    result += emission;
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // apply textures
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TextCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TextCoord));
    vec3 specular = light.specular * spec * material.reflectivity * vec3(texture(material.specular, TextCoord));

    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   
    // apply textures
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TextCoord));
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TextCoord));
    vec3 specular = light.specular * spec * material.reflectivity * vec3(texture(material.specular, TextCoord));
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));  
    // apply factors
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   
    // apply textures
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TextCoord));
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TextCoord));
    vec3 specular = light.specular * spec * material.reflectivity * vec3(texture(material.specular, TextCoord));
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));  
    // spotlight
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOffInner - light.cutOffOuter;
    float intensity = clamp((theta - light.cutOffOuter) / epsilon, 0.0, 1.0);    
    // apply factors
    ambient  *= intensity * attenuation;
    diffuse  *= intensity * attenuation;
    specular *= intensity * attenuation;

    return (ambient + diffuse + specular);
} 
