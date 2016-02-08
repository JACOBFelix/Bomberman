#include "Components/Bonus.hpp"
#include <cstdlib>
Component::Bonus::Bonus() : BaseComponent(Component::BONUS) {
  _value = std::rand() % 100;
  _type = static_cast<Component::Bonus::type>(std::rand()% 3);
}

Component::Bonus::~Bonus() {}

Component::Bonus::Bonus(Bonus const& rhs) : BaseComponent(Component::BONUS) {
  _value = rhs._value;
  _type = rhs._type;
}

Component::Bonus& Component::Bonus::operator=(Bonus const& rhs) {
  if (this != &rhs) {
    _value = rhs._value;
    _type = rhs._type;
  }
  return *this;
}

Component::Bonus::type Component::Bonus::getType(void) const {
  return _type;
}

void Component::Bonus::setType(Component::Bonus::type newType) {
  _type = newType;
}

int Component::Bonus::getValue(void) const {
  return _value;
}

void Component::Bonus::setValue(int const& value) {
  _value = value;
}

Export * Component::Bonus::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(2);
  save->addData(_value);
  save->addData(_type);
  return save;
}
