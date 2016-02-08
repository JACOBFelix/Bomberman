#include "Systems/Input.hpp"

System::Input::Input(std::vector<Entity>& entities) : ASystem(entities) {}

System::Input::~Input() {}

int System::Input::update(float const timer __attribute__((unused))) {
  std::vector<bool (System::Input::*)(Entity&)> keys ({
      &System::Input::keyRight,
	&System::Input::keyLeft,
	&System::Input::keyUp,
	&System::Input::keyDown,
	&System::Input::keyDrop,
	&System::Input::keyPut,
	});
  _context.updateInputs(_input);
  BaseComponent *tmp;
  if (_input.getKey(SDLK_ESCAPE, true) || _input.getInput(SDL_QUIT))
    return 1;
  std::vector<Entity>::iterator it = _entities.begin();
  for (; it != _entities.end(); ++it) {
    if ((_inputPlayer = static_cast<Component::InputContext *>((*it)[Component::INPUTCONTEXT])) &&
	!(tmp = (*it)[Component::ISAI])) {
      _move = static_cast<Component::Move *>((*it)[Component::MOVE]);
      _move->setDir(Component::Move::NONE);

      if (_input.getKey(_inputPlayer->getRight()))
	(this->*keys[0])(*it);
      else if (_input.getKey(_inputPlayer->getLeft()))
	(this->*keys[1])(*it);
      else if (_input.getKey(_inputPlayer->getUp()))
	(this->*keys[2])(*it);
      else if (_input.getKey(_inputPlayer->getDown()))
	(this->*keys[3])(*it);
      else if (_input.getKey(_inputPlayer->getDrop()))
      	(this->*keys[4])(*it);
      else
      	_move->setDir(Component::Move::NONE);
    }
  }
  return 0;
}

bool System::Input::keyRight(Entity& entity __attribute__((unused))) {
  _move->setDir(Component::Move::EAST);
  return true;
}

bool System::Input::keyLeft(Entity& entity __attribute__((unused))) {
  _move->setDir(Component::Move::WEST);
  return true;
}

bool System::Input::keyUp(Entity& entity __attribute__((unused))) {
  _move->setDir(Component::Move::NORTH);
  return true;
}

bool System::Input::keyDown(Entity& entity __attribute__((unused))) {
  _move->setDir(Component::Move::SOUTH);
  return true;
}

bool System::Input::keyDrop(Entity& entity) {
  unsigned int const nbBombs = static_cast<Component::NbBomb *>(entity[Component::NBBOMB])->getNb();
  unsigned int const range = static_cast<Component::Range *>(entity[Component::RANGE])->getRange();
  Component::Position const *position = static_cast<Component::Position const *>(entity[Component::POSITION]);
  Component::PlayerInfo *playerInfo = static_cast<Component::PlayerInfo *>(entity[Component::PLAYERINFO]);

  if (nbBombs) {
    Entity bomb = FactoryEntity::getInstance()->create(Entity::BOMB);
    Component::Position *pos = static_cast<Component::Position *>(bomb[Component::POSITION]);
    static_cast<Component::Range *>(bomb[Component::RANGE])->setRange(range);
    static_cast<Component::NbBomb *>(entity[Component::NBBOMB])->setNb(nbBombs - 1);
    static_cast<Component::Id *>(bomb[Component::ID])->setId(playerInfo->getId());
    pos->setY(((position->getY() + 500) / 1000) * 1000);
    pos->setX(((position->getX() + 500) / 1000) * 1000);
    _entities.push_back(bomb);
    return true;
  }
  return false;
}

bool System::Input::keyPut(Entity& entity __attribute__((unused))) {
  return true;
}

void	System::Input::setInput(gdl::Input const & input) {
  _input = input;
}

void	System::Input::setContext(gdl::SdlContext const & context) {
  _context = context;
}
