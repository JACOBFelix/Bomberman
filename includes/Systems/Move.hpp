#pragma once

#include "MapConfiguration.hpp"
#include "ASystem.hpp"

namespace System {
  class Move : public ASystem {
  private:
    std::vector<void (System::Move::*)(unsigned int&)> const _ptr;
    std::vector<void (System::Move::*)(Entity *)> const _bonusPtr;
    void bonusSpeed(Entity *);
    void bonusBomb(Entity *);
    void bonusRange(Entity *);
    void pickUpBonus(int i, Entity *);
    int canMove(unsigned int, unsigned int, unsigned int& i, Component::type, int margin = 500);
    void moveNorth(unsigned int& i);
    void moveSouth(unsigned int& i);
    void moveEast(unsigned int& i);
    void moveWest(unsigned int& i);
    bool sameTile(int xa, int ya, int xb, int yb, int margin = 0);

  public:
    Move(std::vector<Entity>&);
    ~Move();

    int update(float const timer);
  };
}
