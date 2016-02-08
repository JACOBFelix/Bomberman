#include "BaseComponent.hpp"

BaseComponent::BaseComponent(Component::type type) : _type(type) {}

BaseComponent::~BaseComponent() {}

BaseComponent::BaseComponent(BaseComponent const& o) {
  _type = o._type;
}

BaseComponent& BaseComponent::operator=(BaseComponent const& o) {
  if (this != &o) {
    _type = o._type;
  }
  return *this;
}


Component::type BaseComponent::getType() const {
  return _type;
}
