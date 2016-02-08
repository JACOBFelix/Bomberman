#pragma once

#include "ASystem.hpp"
#include "FactoryEntity.hpp"

#define MAX(x, y)	(x < y ? y : x)

namespace System {
  class Bomb : public ASystem {
  private:
    void createExplosion(unsigned int i, Component::Move::dir const &, unsigned int speed);
    void bombExplos(unsigned int i);
    void createExplosions(std::vector<Entity>::iterator &it);

  public:
    Bomb(std::vector<Entity> &);
    ~Bomb();
    int update(float const timer);
  };
}
