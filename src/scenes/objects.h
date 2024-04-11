// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!BAD PRACTICE!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TODO: Implement scene graph system

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "renderer/light.h"

// positions all containers
extern glm::vec3 cubePositions[];

extern glm::vec4 skyColor;

extern Material mat;

extern DirLight sun;

extern PointLight redstoneLights;

extern SpotLight flashLight;

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
extern std::vector <float> cubeVert;

extern std::vector <float> cubeNorm;

extern std::vector <float> cubeTexCoord;

extern std::vector <float> planeVert;

extern std::vector <float> planeNorm;

extern std::vector <float> planeTexCoord;
