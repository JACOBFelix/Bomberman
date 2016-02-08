#include "Components/Position.hpp"

Component::Position::Position() : BaseComponent(Component::POSITION),
				  _x(0),
				  _y(0) {
}

Component::Position::~Position() {}

Component::Position::Position(Position const& rhs): BaseComponent(Component::POSITION) {
  _x = rhs._x;
  _y = rhs._y;
}

Component::Position& Component::Position::operator=(Position const& rhs) {
  if (this != &rhs) {
    _x = rhs._x;
    _y = rhs._y;
  }
  return *this;
}

unsigned int Component::Position::getX(void) const {
  return _x;
}

void Component::Position::setX(unsigned int const& x) {
  _x = x;
}

unsigned int Component::Position::getY(void) const {
  return _y;
}

void Component::Position::setY(unsigned int const& y) {
  _y = y;
}

Export * Component::Position::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(2);
  save->addData(_x);
  save->addData(_y);
  return save;
}
