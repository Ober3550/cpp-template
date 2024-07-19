#include "mesh.h"
#include <GL/gl3w.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<std::array<int, 3>> indices)
    : vertices(vertices), indices(indices) {
  // Setup vertex array object for loading vertex data to GPU
  glGenBuffers(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VBO);
  glBindVertexArray(VAO);

  std::vector<glm::vec3> vertsAndNorms(2 * vertices.size());
  // std::cout << "Mesh indices: " << fmt::format("{}", indices) << std::endl;

  for (int i = 0; i < indices.size(); i++) {
    glm::vec3 a(vertices[indices[i][0]]);
    glm::vec3 b(vertices[indices[i][1]]);
    glm::vec3 c(vertices[indices[i][2]]);
    // Get the vertices of the triangle
    glm::vec3 normal = calculateNormal(a, b, c);

    vertsAndNorms[indices[i][0] * 2 + 0] = a;
    vertsAndNorms[indices[i][1] * 2 + 0] = b;
    vertsAndNorms[indices[i][2] * 2 + 0] = c;
    // Place the calculated normal adjacent to the vertex
    vertsAndNorms[indices[i][0] * 2 + 1] = normal;
    vertsAndNorms[indices[i][1] * 2 + 1] = normal;
    vertsAndNorms[indices[i][2] * 2 + 1] = normal;
  }

  std::cout << "Mesh Data: " << std::endl;
  for (int i = 0; i < vertsAndNorms.size(); i += 2) {
    std::cout << fmt::format(
                   "{}x {}y {}z {}u {}v {}w",
                   vertsAndNorms[i].x,
                   vertsAndNorms[i].y,
                   vertsAndNorms[i].z,
                   vertsAndNorms[i + 1].x,
                   vertsAndNorms[i + 1].y,
                   vertsAndNorms[i + 1].z)
              << std::endl;
  }

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertsAndNorms.size() * 6 * sizeof(float), vertsAndNorms.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 3 * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

glm::vec3 Mesh::calculateNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
  std::cout << "Calculating normal from triangle" << std::endl;
  std::cout << "A: " << a.x << "x " << a.y << "y " << a.z << "z" << std::endl;
  std::cout << "B: " << b.x << "x " << b.y << "y " << b.z << "z" << std::endl;
  std::cout << "C: " << c.x << "x " << c.y << "y " << c.z << "z" << std::endl;

  glm::vec3 u = b - a;
  glm::vec3 v = c - a;

  float x = u.y * v.z - u.z * v.y;
  float y = u.z * v.x - u.x * v.z;
  float z = u.x * v.y - u.y * v.x;

  std::cout << "Normal: " << x << "x " << y << "y " << z << "z" << std::endl;
  glm::vec3 normal(x, y, z);
  return normal / glm::length(normal);
}

void Mesh::draw() const {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
}