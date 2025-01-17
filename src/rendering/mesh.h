#pragma once
#include <array>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
  Mesh(std::vector<glm::vec3> vertices, std::vector<std::array<int, 3>> indices);
  void draw() const;
  static glm::vec3 calculateNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);

private:
  std::vector<glm::vec3> vertices;
  std::vector<std::array<int, 3>> indices;
  uint32_t VAO, VBO, EBO;
};

#define GR 1.61803398875
const std::vector<glm::vec3> ICO_VERT = {
  {1.f, GR, 0.f},   // 0
  {-1.f, GR, 0.f},  // 1
  {1.f, -GR, 0.f},  // 2
  {-1.f, -GR, 0.f}, // 3
  {GR, 0.f, 1.f},   // 4
  {GR, 0.f, -1.f},  // 5
  {-GR, 0.f, 1.f},  // 6
  {-GR, 0.f, -1.f}, // 7
  {0.f, 1.f, GR},   // 8
  {0.f, -1.f, GR},  // 9
  {0.f, 1.f, -GR},  // 10
  {0.f, -1.f, -GR}, // 11
};

const std::vector<std::array<int, 3>> ICO_IDX = {
  {5, 4, 0},  {1, 6, 7},  {2, 4, 5}, {7, 6, 3},  {9, 8, 4}, {5, 10, 11}, {6, 8, 9}, {11, 10, 7}, {1, 0, 8}, {9, 2, 3},
  {10, 0, 1}, {3, 2, 11}, {0, 4, 8}, {10, 5, 0}, {1, 8, 6}, {1, 7, 10},  {2, 9, 4}, {5, 11, 2},  {3, 6, 9}, {3, 11, 7},
};

const std::vector<glm::vec3> CUBE_VERT = {
  {-0.5f, -0.5f, -0.5f},
  {0.5f, -0.5f, -0.5f},
  {0.5f, 0.5f, -0.5f},
  {-0.5f, 0.5f, -0.5f},
  {-0.5f, -0.5f, 0.5f},
  {0.5f, -0.5f, 0.5f},
  {0.5f, 0.5f, 0.5f},
  {-0.5f, 0.5f, 0.5f}};

const std::vector<std::array<int, 3>> CUBE_IDX = {
  {0, 1, 2},
  {2, 3, 0}, // Front face
  {4, 5, 6},
  {6, 7, 4}, // Back face
  {1, 5, 6},
  {6, 2, 1}, // Right face
  {0, 4, 7},
  {7, 3, 0}, // Left face
  {3, 2, 6},
  {6, 7, 3}, // Top face
  {0, 1, 5},
  {5, 4, 0} // Bottom face
};
