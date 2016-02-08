#include "Components/Breakable.hpp"

Component::Breakable::Breakable() : BaseComponent(Component::BREAKABLE) {}

Component::Breakable::~Breakable() {}

Component::Breakable::Breakable(Breakable const& rhs __attribute__((unused))) : BaseComponent(Component::BREAKABLE){
}

Component::Breakable& Component::Breakable::operator=(Breakable const& rhs) {
  if (this != &rhs) {
  }
  return *this;
}

Export * Component::Breakable::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(0);
  return save;
}
