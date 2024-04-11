// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!BAD PRACTICE!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TODO: Implement scene graph system

#include "scenes/objects.h"

// positions all containers
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  3.0f,  0.0f),
    glm::vec3( 2.0f,  8.0f, -15.0f),
    glm::vec3(-1.5f,  1.2f, -2.5f),
    glm::vec3(-3.8f,  1.0f, -12.3f),
    glm::vec3( 2.4f,  2.6f, -3.5f),
    glm::vec3(-1.7f,  6.0f, -7.5f),
    glm::vec3( 1.3f,  1.0f, -2.5f),
    glm::vec3( 1.5f,  5.0f, -2.5f),
    glm::vec3( 1.5f,  3.2f, -1.5f),
    glm::vec3(-1.3f,  4.0f, -1.5f)
};

glm::vec4 skyColor(0.1f, 0.1f, 0.1f, 1.0f);

Material mat{
    32.0f,  // shininess
    1.0f    // reflectivity
};

DirLight sun{
    glm::vec3(-0.2f, -1.0f, -0.3f), // direction
    glm::vec3(0.05f, 0.05f, 0.05f), // ambient
    glm::vec3(0.4f, 0.4f, 0.4f),    // diffuse
    glm::vec3(0.5f, 0.5f, 0.5f)     // specular 
};

PointLight redstoneLights{
    10,              // length
    cubePositions,  // positions

    glm::vec3(0.05f, 0.05f, 0.05f),  // ambient
    glm::vec3(0.8f, 0.8f, 0.8f),     // diffuse
    glm::vec3(1.0f, 1.0f, 1.0f),     // specular

    1.0f,  // constant
    0.09, // linear
    0.032 // quadratic
};

SpotLight flashLight = {
    glm::vec3(),        // position
    glm::vec3(),        // direction

    12.5f, 17.5f,       // inner and outer cutoff angle

    glm::vec3(0.05f, 0.05f, 0.05f),  // ambient
    glm::vec3(0.8f, 0.8f, 0.8f),     // diffuse
    glm::vec3(1.0f, 1.0f, 1.0f),     // specular

    1.0f,  // constant
    0.09, // linear
    0.032 // quadratic
};

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
std::vector <float> cubeVert = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
                       
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
                       
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
                       
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
                       
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
                       
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

std::vector <float> cubeNorm = {
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f, 
     0.0f,  0.0f, -1.0f, 
     0.0f,  0.0f, -1.0f, 
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
                        
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f, 
     0.0f,  0.0f,  1.0f, 
     0.0f,  0.0f,  1.0f, 
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f,
                        
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
                        
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
                        
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f, 
     0.0f, -1.0f,  0.0f, 
     0.0f, -1.0f,  0.0f, 
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f,
                        
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f, 
     0.0f,  1.0f,  0.0f, 
     0.0f,  1.0f,  0.0f, 
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f
};

std::vector <float> cubeTexCoord = {
     0.0f,  0.0f,
     1.0f,  0.0f,
     1.0f,  1.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
                 
     0.0f,  0.0f,
     1.0f,  0.0f,
     1.0f,  1.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
                 
     1.0f,  0.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
     1.0f,  0.0f,
                 
     1.0f,  0.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
     1.0f,  0.0f,
                 
     0.0f,  1.0f,
     1.0f,  1.0f,
     1.0f,  0.0f,
     1.0f,  0.0f,
     0.0f,  0.0f,
     0.0f,  1.0f,
                 
     0.0f,  1.0f,
     1.0f,  1.0f,
     1.0f,  0.0f,
     1.0f,  0.0f,
     0.0f,  0.0f,
     0.0f,  1.0f
};

std::vector <float> planeVert = {
    200.0f, 0.0f,-200.0f,
    200.0f, 0.0f, 200.0f,
   -200.0f, 0.0f, 200.0f,
   -200.0f, 0.0f, 200.0f,
   -200.0f, 0.0f,-200.0f,
    200.0f, 0.0f,-200.0f
};

std::vector <float> planeNorm = {
   0.0f, 1.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 1.0f, 0.0f
};

std::vector <float> planeTexCoord = {
     1.0f * 200.0f,  1.0f * 200.0f,
     1.0f * 200.0f,  0.0f * 200.0f,
     0.0f * 200.0f,  0.0f * 200.0f,
     0.0f * 200.0f,  0.0f * 200.0f,
     0.0f * 200.0f,  1.0f * 200.0f,
     1.0f * 200.0f,  1.0f * 200.0f
};
