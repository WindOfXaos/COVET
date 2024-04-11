#include "scenes/creeper.h"

#include "scenes/objects.h"

void CreeperScene::setup()
{
  // build and compile shaders
  // -------------------------
  redstone_shader = new Shader("shaders/vertex.vs", "shaders/fragment.fs");
  creeper_shader = new Shader("shaders/vertex.vs", "shaders/fragment.fs");
  ground_shader = new Shader("shaders/vertex.vs", "shaders/fragment.fs");

  // initialize loader and camera
  // ----------------------------
  fps_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
  Loader loader;

  // load vertices and textures
  // --------------------------
  // redstone
  redstone = new Model(loader.loadToVAO(cubeVert, cubeNorm, cubeTexCoord));
  const char *diffuseMap = "assets/textures/redstone_lamp.jpg";
  redstone->addTexture(loader.loadTexture(GL_TEXTURE_2D, diffuseMap, GL_RGB));
  const char *specularMap = "assets/textures/redstone_lamp_specular.png";
  redstone->addTexture(loader.loadTexture(GL_TEXTURE_2D, specularMap, GL_RGBA, true));
  const char *emissionMap = "assets/textures/redstone_lamp_emission.png";
  redstone->addTexture(loader.loadTexture(GL_TEXTURE_2D, emissionMap, GL_RGBA, true));
  // creeper
  creeper = new Model(loader.loadToVAO(cubeVert, cubeNorm, cubeTexCoord));
  diffuseMap = "assets/textures/creeper_face_small_rgb.png";
  creeper->addTexture(loader.loadTexture(GL_TEXTURE_2D, diffuseMap, GL_RGBA, true));
  specularMap = "assets/textures/blank.jpg";
  creeper->addTexture(loader.loadTexture(GL_TEXTURE_2D, specularMap, GL_RGB));
  emissionMap = "assets/textures/creeper_face_emission.png";
  creeper->addTexture(loader.loadTexture(GL_TEXTURE_2D, emissionMap, GL_RGBA, true));
  // ground
  ground = new Model(loader.loadToVAO(planeVert, planeNorm, planeTexCoord));
  diffuseMap = "assets/textures/grass.png";
  ground->addTexture(loader.loadTexture(GL_TEXTURE_2D, diffuseMap, GL_RGBA, true));
  specularMap = "assets/textures/blank.jpg";
  ground->addTexture(loader.loadTexture(GL_TEXTURE_2D, specularMap, GL_RGB));
  emissionMap = "assets/textures/blank.jpg";
  ground->addTexture(loader.loadTexture(GL_TEXTURE_2D, emissionMap, GL_RGB));

  // shader configuration
  // --------------------
  // redstone
  redstone_shader->use();
  redstone_shader->setBool("lamp", true);
  redstone_shader->setInt("material.diffuse", 0);
  redstone_shader->setInt("material.specular", 1);
  redstone_shader->setInt("material.emission", 2);
  // creeper
  creeper_shader->use();
  creeper_shader->setInt("material.diffuse", 0);
  creeper_shader->setInt("material.specular", 1);
  creeper_shader->setInt("material.emission", 2);
  // ground
  ground_shader->use();
  ground_shader->setInt("material.diffuse", 0);
  ground_shader->setInt("material.specular", 1);
  ground_shader->setInt("material.emission", 2);
}

void CreeperScene::update(float aspect_ratio)
{
  glClearColor(skyColor.r, skyColor.g, skyColor.b, skyColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // light shaders
  // -------------
  flashLight.position = fps_camera->position;
  flashLight.direction = fps_camera->front;
  // redstone
  redstone_shader->use();
  redstone_shader->setVec3("viewPos", fps_camera->position);
  redstone_shader->setMaterial(mat.shininess, mat.reflectivity);
  redstone_shader->setDirLight(sun);
  redstone_shader->setPointLight(redstoneLights);
  redstone_shader->setSpotLight(flashLight);
  // creeper
  creeper_shader->use();
  creeper_shader->setVec3("viewPos", fps_camera->position);
  creeper_shader->setMaterial(mat.shininess, mat.reflectivity);
  creeper_shader->setDirLight(sun);
  creeper_shader->setPointLight(redstoneLights);
  creeper_shader->setSpotLight(flashLight);
  // ground
  ground_shader->use();
  ground_shader->setVec3("viewPos", fps_camera->position);
  ground_shader->setMaterial(mat.shininess, mat.reflectivity);
  ground_shader->setDirLight(sun);
  ground_shader->setPointLight(redstoneLights);
  ground_shader->setSpotLight(flashLight);

  // view/projection transformations
  // -------------------------------
  glm::mat4 projection = glm::perspective(glm::radians(fps_camera->zoom),
          aspect_ratio, 0.1f, 100.0f);
  glm::mat4 view = fps_camera->GetViewMatrix();
  // redstone
  redstone_shader->use();
  redstone_shader->setMat4("projection", projection);
  redstone_shader->setMat4("view", view);
  // world transformation
  // --------------------
  glm::mat4 model = glm::mat4(1.0f);
  redstone_shader->setMat4("model", model);
  // redstone
  for (unsigned int i = 0; i < 10; i++)
  {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
      redstone_shader->setMat4("model", model);
      redstone->draw();
  }

  // creeper
  creeper_shader->use();
  creeper_shader->setMat4("projection", projection);
  creeper_shader->setMat4("view", view);
  model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.3f));
  model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
  creeper_shader->setMat4("model", model);
  creeper->draw();
  // ground
  ground_shader->use();
  ground_shader->setMat4("projection", projection);
  ground_shader->setMat4("view", view);
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
  ground_shader->setMat4("model", model);
  ground->draw();
}
