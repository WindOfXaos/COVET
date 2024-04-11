#pragma once

#include <glm/glm.hpp>

struct Material
{
    float shininess;
    float reflectivity; 
};

struct DirLight 
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular; 
};  

struct PointLight 
{   
    // positions of the point lightPos
    unsigned int N;
    glm::vec3 *positions;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant; 
    float linear;
    float quadratic;
};

struct SpotLight {
    glm::vec3  position;
    glm::vec3  direction;

    float cutOffInner;
    float cutOffOuter;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant; 
    float linear;
    float quadratic;
};
