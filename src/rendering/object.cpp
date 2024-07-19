#include "object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Object::Object(
  const Mesh *mesh,
  const Shader *shader,
  glm::vec3 position,
  glm::vec3 rotation,
  glm::vec3 scale,
  glm::vec3 color)
    : shader(shader), mesh(mesh), position(position), rotation(rotation), scale(scale), color(color) {};

void Object::draw(glm::vec3 cameraPos) {
  glm::mat4 transform = glm::mat4(1.0f);
  transform = glm::translate(transform, position);
  transform = transform * glm::mat4_cast(glm::quat(glm::radians(rotation)));
  transform = glm::scale(transform, scale);
  shader->use();
  shader->setMat4("model", transform);
  shader->setVec3("objectColor", glm::vec3(0.8f, 0.f, 0.f));
  shader->setVec3("lightPos", glm::vec3(0.f, 0.f, 4.f));
  shader->setVec3("lightColor", color);
  shader->setVec3("viewPos", cameraPos);
  mesh->draw();
}

void Object::rotate(glm::vec3 newRotation) { rotation = newRotation; }
void Object::addRotation(glm::vec3 addRotation) { rotation += addRotation; }