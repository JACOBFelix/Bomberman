#include "Components/Move.hpp"

Component::Move::Move() : BaseComponent(Component::MOVE) {}

Component::Move::~Move() {}

Component::Move::Move(Move const& rhs) : BaseComponent(Component::MOVE) {
  _dir = rhs._dir;
}

Component::Move& Component::Move::operator=(Move const& rhs) {
  if (this != &rhs) {
    _dir = rhs._dir;
  }
  return *this;
}

Component::Move::dir const& Component::Move::getDir(void) const {
  return _dir;
}

void Component::Move::setDir(dir const& dir) {
  _dir = dir;
}

unsigned int Component::Move::getSpeed(void) const {
  return _speed;
}

void Component::Move::setSpeed(unsigned int speed) {
  _speed = speed;
}

Export * Component::Move::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(2);
  save->addData(_dir);
  save->addData(_speed);
  return save;
}
