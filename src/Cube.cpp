#include "Cube.hpp"
#include "Exceptions.hpp"

Cube::Cube(unsigned int x, unsigned int y) {
  _x = x;
  _y = y;

  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushVertex(glm::vec3(_x +  0.5f, 0.5f,  _y +-0.5f));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, 0.5f,  _y +-0.5f));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, 0.5f,  _y + 0.5f));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(_x +  0.5f, 0.5f,  _y + 0.5f));

  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushVertex(glm::vec3(_x +  0.5f, -0.5f, _y +  0.5f));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, -0.5f, _y +  0.5f));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, -0.5f, _y + -0.5f));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(_x +  0.5f, -0.5f, _y + -0.5f));

  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushVertex(glm::vec3(_x +  0.5f,  0.5f, _y + 0.5f));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(_x + -0.5f,  0.5f, _y + 0.5f));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, -0.5f, _y + 0.5f));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(_x +  0.5f, -0.5f, _y + 0.5f));

  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushVertex(glm::vec3(_x +  0.5f, -0.5f, _y + -0.5f));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, -0.5f, _y + -0.5f));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(_x + -0.5f,  0.5f, _y + -0.5f));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(_x +  0.5f,  0.5f, _y + -0.5f));

  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushVertex(glm::vec3(_x + -0.5f,  0.5f, _y +  0.5f));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(_x + -0.5f,  0.5f, _y + -0.5f));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, -0.5f, _y + -0.5f));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(_x + -0.5f, -0.5f, _y +  0.5f));

  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushVertex(glm::vec3(x + 0.5f,  0.5f,  _y + -0.5f));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(x + 0.5f,  0.5f,  _y +  0.5f));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(x + 0.5f, -0.5f,  _y +  0.5f));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(x + 0.5f, -0.5f,  _y + -0.5f));

  _geometry.build();
}

Cube::~Cube() {}
