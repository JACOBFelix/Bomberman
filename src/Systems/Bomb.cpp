#include "Components/Position.hpp"
#include "Systems/Bomb.hpp"

void System::Bomb::createExplosion(unsigned int i,
				   Component::Move::dir const & dir,
				   unsigned int speed __attribute__((unused))) {
  FactoryEntity	*factory = FactoryEntity::getInstance();
  Entity explosion = factory->create(Entity::EXPLOSION);
  unsigned int range = static_cast<Component::Range *>(_entities[i][Component::RANGE])->getRange();
  unsigned int const x = static_cast<Component::Position *>(_entities[i][Component::POSITION])->getX();
  unsigned int const y = static_cast<Component::Position *>(_entities[i][Component::POSITION])->getY();

  static_cast<Component::Position *>(explosion[Component::POSITION])->setX(x);
  static_cast<Component::Position *>(explosion[Component::POSITION])->setY(y);
  static_cast<Component::Move *>(explosion[Component::MOVE])->setDir(dir);
  static_cast<Component::Move *>(explosion[Component::MOVE])->setSpeed(52);
  static_cast<Component::Range *>(explosion[Component::RANGE])->setRange(range);
  _entities.push_back(explosion);
}

void System::Bomb::bombExplos(unsigned int i) {
  Component::PlayerInfo *playerInfo;
  std::vector<Entity>::iterator play = _entities.begin();
  unsigned int const id = static_cast<Component::Id *>(_entities[i][Component::ID])->getId();
  int nb;
  unsigned int speed = 52;

  for (; play < _entities.end(); ++play) {
    if (play->getType() == Entity::PLAYER
	&& (playerInfo = static_cast<Component::PlayerInfo *>((*play)[Component::PLAYERINFO]))
	&& (playerInfo->getId() == id)) {
      nb = static_cast<Component::NbBomb *>((*play)[Component::NBBOMB])->getNb();
      static_cast<Component::NbBomb *>((*play)[Component::NBBOMB])->setNb(nb + 1);
      speed = static_cast<Component::Move *>((*play)[Component::MOVE])->getSpeed() + 8;
      break;
    }
  }
  createExplosion(i, Component::Move::EAST, speed);
  createExplosion(i, Component::Move::WEST, speed);
  createExplosion(i, Component::Move::NORTH, speed);
  createExplosion(i, Component::Move::SOUTH, speed);
  _entities.erase(_entities.begin() + i);
}

int System::Bomb::update(float const time) {
  std::vector<Entity>::iterator it = _entities.begin();
  Component::Timer *timer;

  for (unsigned int i = 0; i < _entities.size(); ++i) {
    if (_entities[i].getType() == Entity::BOMB) {
      timer = static_cast<Component::Timer *>(_entities[i][Component::TIMER]);
      if (timer->getMs() - time <= 0)
	bombExplos(i);
      else
	timer->setMs(timer->getMs() - time);
    }
  }
  return 0;
}

System::Bomb::Bomb(std::vector<Entity >& entities) : ASystem(entities) {}

System::Bomb::~Bomb() {}
