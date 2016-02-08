#include "Components/Solid.hpp"

Component::Solid::Solid() : BaseComponent(Component::SOLID) {}

Component::Solid::~Solid() {}

Component::Solid::Solid(Solid const& rhs __attribute__((unused))) : BaseComponent(Component::SOLID) {
}

Component::Solid& Component::Solid::operator=(Solid const& rhs) {
  if (this != &rhs) {
  }
  return *this;
}

Export * Component::Solid::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(0);
  return save;
}
