#include "Components/InputContext.hpp"

Component::InputContext::InputContext() : BaseComponent(Component::INPUTCONTEXT) {}

Component::InputContext::~InputContext() {}

Component::InputContext::InputContext(InputContext const& rhs)  : BaseComponent(Component::INPUTCONTEXT) {
  _up = rhs._up;
  _down = rhs._down;
  _left = rhs._left;
  _right = rhs._right;
  _drop = rhs._drop;
}

Component::InputContext& Component::InputContext::operator=(InputContext const& rhs) {
  if (this != &rhs) {
    _up = rhs._up;
    _down = rhs._down;
    _left = rhs._left;
    _right = rhs._right;
    _drop = rhs._drop;
  }
  return *this;
}
int Component::InputContext::getUp(void) const {
  return _up;
}

void Component::InputContext::setUp(int const& up) {
  _up = up;
}
int Component::InputContext::getDown(void) const {
  return _down;
}

void Component::InputContext::setDown(int const& down) {
  _down = down;
}
int Component::InputContext::getLeft(void) const {
  return _left;
}

void Component::InputContext::setLeft(int const& left) {
  _left = left;
}
int Component::InputContext::getRight(void) const {
  return _right;
}

void Component::InputContext::setRight(int const& right) {
  _right = right;
}
int Component::InputContext::getDrop(void) const {
  return _drop;
}

void Component::InputContext::setDrop(int const& drop) {
  _drop = drop;
}

Export * Component::InputContext::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(6);
  save->addData(_left);
  save->addData(_right);
  save->addData(_up);
  save->addData(_down);
  save->addData(_drop);
  return save;
}

