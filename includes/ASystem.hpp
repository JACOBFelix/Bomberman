#pragma once

#include <vector>
#include "Entity.hpp"

class ASystem {
protected:
  std::vector<Entity>& _entities;

public:
  ASystem(std::vector<Entity>& entities);
  ~ASystem() {}

  virtual int update(float const dt) = 0;
};
