#pragma once

#include "mesh.h"
#include "shader.h"

class Object {
public:
  Object(
    const Mesh *mesh,
    const Shader *shader,
    glm::vec3 position = {},
    glm::vec3 rotation = {},
    glm::vec3 scale = glm::vec3(1.0f),
    glm::vec3 color = {1.0f, 1.0f, 1.0f});
  void draw(glm::vec3 cameraPos);
  void rotate(glm::vec3 rotation);
  void addRotation(glm::vec3 rotation);

  const Mesh *mesh;
  const Shader *shader;
  glm::vec3 position, rotation, scale, color;

private:
};