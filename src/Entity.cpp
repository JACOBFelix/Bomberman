#include "Entity.hpp"
#include <iostream>

Entity::Entity(type const type) : _type(type) {
  _components.resize(64);
}

Entity::~Entity() {
  while (!_components.empty()) {
    _components.pop_back();
  }
}

Entity::Entity(Entity const& o) {
  _type = o._type;
  _components = o._components;
}

Entity& Entity::operator=(Entity const& o) {
  if (this != &o) {
    _type = o._type;
    _components = o._components;
  }
  return *this;
}

void	Entity::addComponent(Component::type const type) {
  _components[type] = FactoryComponent::getInstance()->create(type);
}

Entity&	Entity::operator<<(Component::type const type) {
  _components[type] = FactoryComponent::getInstance()->create(type);
  return *this;
}

void	Entity::addComponent(BaseComponent* component) {
  _components[component->getType()] = component;
}

Entity&	Entity::operator<<(BaseComponent* component) {
  _components[component->getType()] = component;
  return *this;
}

BaseComponent*	Entity::getComponent(Component::type const type) const {
  return _components[type];
}

BaseComponent*	Entity::operator[](Component::type const type) const {
  return _components[type];
}

Entity::type Entity::getType(void) const {
  return _type;
}

template<typename T>
int addComponentToExport(Export * tmpComponents, T comp) {
  if (comp == NULL)
    return 0;
  Export * tmp = comp->serialize();
  std::cout << "Add component " << comp->getType() << "\t: " << tmp->getData().size() << " bytes" << std::endl;

  tmpComponents->merge(tmp);
  delete tmp;
  return 1;
}

Export * Entity::serialize() const {
  Export * save = new Export;
  Export * tmpComponents = new Export;

  unsigned int o = 0;

//  std::cout << "Entity type was not defined " << std::endl;
  save->addData(getType());
  std::cout << std::endl;
  int x = save->getDataInt(o);
  std::cout << "Entity type defined to     \t: " << x << ", type size in mem is " << save->getData().size() << std::endl;

  int nb = 0;
  Component::Position * position = static_cast<Component::Position *>(_components[Component::POSITION]);
  Component::Bonus * bonus = static_cast<Component::Bonus *>(_components[Component::BONUS]);
  Component::Fd * fd = static_cast<Component::Fd *>(_components[Component::FD]);
  Component::PlayerInfo * playerinfo = static_cast<Component::PlayerInfo *>(_components[Component::PLAYERINFO]);
  Component::Range * range = static_cast<Component::Range *>(_components[Component::RANGE]);
  Component::Timer* timer = static_cast<Component::Timer *>(_components[Component::TIMER]);
  Component::Move * move = static_cast<Component::Move *>(_components[Component::MOVE]);
  Component::InputContext * input = static_cast<Component::InputContext *>(_components[Component::INPUTCONTEXT]);
  Component::NbBomb * nbbomb = static_cast<Component::NbBomb *>(_components[Component::NBBOMB]);
  Component::Id * id = static_cast<Component::Id *>(_components[Component::ID]);
  Component::Breakable * breakable = static_cast<Component::Breakable *>(_components[Component::BREAKABLE]);
  Component::Solid * solid = static_cast<Component::Solid *>(_components[Component::SOLID]);
  nb += addComponentToExport(tmpComponents, position);
  nb += addComponentToExport(tmpComponents, bonus);
  nb += addComponentToExport(tmpComponents, fd);
  nb += addComponentToExport(tmpComponents, playerinfo);
  nb += addComponentToExport(tmpComponents, range);
  nb += addComponentToExport(tmpComponents, timer);
  nb += addComponentToExport(tmpComponents, move);
  nb += addComponentToExport(tmpComponents, input);
  nb += addComponentToExport(tmpComponents, nbbomb);
  nb += addComponentToExport(tmpComponents, id);
  nb += addComponentToExport(tmpComponents, breakable);
  nb += addComponentToExport(tmpComponents, solid);
  std::cout << "Entity will get " << nb << " components, so " << tmpComponents->getData().size() << " bytes." << std::endl;
  save->addData(nb);
  save->merge(tmpComponents);
  delete tmpComponents;
  return save;
}
