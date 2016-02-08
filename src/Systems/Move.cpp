#include "Systems/Move.hpp"
#include "FactoryEntity.hpp"

#define MAX(x, y)	((signed)(x) < (signed)(y) ? (y) : (x))

System::Move::Move(std::vector<Entity> & entities) : ASystem(entities), _ptr({NULL,
      &System::Move::moveNorth,
      &System::Move::moveEast,
      &System::Move::moveSouth,
      &System::Move::moveWest}),
						     _bonusPtr({&System::Move::bonusSpeed,
							   &System::Move::bonusBomb,
							   &System::Move::bonusRange}) {
  }

System::Move::~Move() {}

int System::Move::update(float const timer __attribute__((unused))) {
  Component::Move *move;
  int j;

  for (unsigned int i = 0; i < _entities.size(); ++i) {
    if ((move = static_cast<Component::Move *>(_entities[i][Component::MOVE]))
	&& move->getDir() != Component::Move::NONE) {
      Component::Position *pos = static_cast<Component::Position *>(_entities[i][Component::POSITION]);
      (this->*_ptr[move->getDir()])(i);
      if (_entities[i].getType() == Entity::PLAYER) {
	for (unsigned int k = 0; k < _entities.size(); ++k) {
	  if (_entities[k].getType() == Entity::POWERUP) {
	    Component::Position *posPower = static_cast<Component::Position *>(_entities[k][Component::POSITION]);
	    if (sameTile(posPower->getX(), posPower->getY(), pos->getX(), pos->getY(), 650)) {
	      (this->*_bonusPtr[static_cast<Component::Bonus *>(_entities[k][Component::BONUS])->getType()])(&_entities[i]);
	      _entities.erase(_entities.begin() + k);
	      i -= (k < i);
	      break;
	    }
	  }
	}
      }

      else if (_entities[i].getType() == Entity::EXPLOSION) {
	Component::Range *range = static_cast<Component::Range *>(_entities[i][Component::RANGE]);
	range->setRange(MAX(range->getRange() - move->getSpeed(), 0));
	if (_entities[i].getType() == Entity::EXPLOSION
	    && (j = canMove(pos->getX(), pos->getY(), i, Component::BREAKABLE, 450)) != -1) {
	  if (std::rand() % 10 > 8) {
	    FactoryEntity *fac = FactoryEntity::getInstance();
	    Entity tmp = fac->create(Entity::POWERUP);
	    Component::Position *oldPos = static_cast<Component::Position *>(_entities[j][Component::POSITION]);
	    Component::Position *newPos = static_cast<Component::Position *>(tmp[Component::POSITION]);
	    std::vector<gdl::Model& (FactoryEntity::*)(void)> const fptr({&FactoryEntity::getBonusFlame,
		  &FactoryEntity::getBonusIce,
		  &FactoryEntity::getBonusPink});
	    tmp << new Component::Model((FactoryEntity::getInstance()->*fptr[static_cast<Component::Bonus *>(tmp[Component::BONUS])->getType()])(), 0.0002);
	    newPos->setX(oldPos->getX());
	    newPos->setY(oldPos->getY());
	    _entities.push_back(tmp);
	    _entities.erase(_entities.begin() + j);
	  }
	  else {
	    _entities.erase(_entities.begin() + j);
	  }
	  _entities.erase(_entities.begin() + i - (j < static_cast<int>(i)));
	  i -= (j < static_cast<int>(i));
	  --i;
	}
	else if (_entities[i].getType() == Entity::EXPLOSION
		 && ((j = canMove(pos->getX(), pos->getY(), i, Component::SOLID, 450)) != -1
		     || static_cast<Component::Range *>(_entities[i][Component::RANGE])->getRange() == 0)) {
	  _entities.erase(_entities.begin() + i);
	  --i;
	}
      }
    }
  }
  return 0;
}

void System::Move::bonusSpeed(Entity *player) {
  Component::Move *playerMove = static_cast<Component::Move *>((*player)[Component::MOVE]);

  playerMove->setSpeed(playerMove->getSpeed() + 5);
}

void System::Move::bonusRange(Entity *player) {
  Component::Range *playerRange = static_cast<Component::Range *>((*player)[Component::RANGE]);

  playerRange->setRange(playerRange->getRange() + 500);
}

void System::Move::bonusBomb(Entity *player) {
  Component::NbBomb *playerNbBomb = static_cast<Component::NbBomb *>((*player)[Component::NBBOMB]);

  playerNbBomb->setNb(playerNbBomb->getNb() + 8);
}

void System::Move::pickUpBonus(int i, Entity *player) {
  Component::Bonus *bonus = static_cast<Component::Bonus *>(_entities[i][Component::BONUS]);

  (this->*_bonusPtr[bonus->getType()])(player);
}

bool System::Move::sameTile(int xa, int ya, int xb, int yb, int margin) {
  return (std::abs(xa - xb) < 1000 - margin && std::abs(ya - yb) < 1000 - margin);
}

int System::Move::canMove(unsigned int x, unsigned int y, unsigned int& i, Component::type type, int margin) {
  std::vector<Entity>::iterator it = _entities.begin();

  for (unsigned int j = 0; it != _entities.end(); ++it, ++j) {
    if (i != j && (*it)[type]) {
      Component::Position *posi = static_cast<Component::Position *>((*it)[Component::POSITION]);
      if (this->sameTile(posi->getX(), posi->getY(), x, y, margin))
	return j;
    }
  }
  return -1;
}

void System::Move::moveSouth(unsigned int& i) {
  Component::Position *pos = static_cast<Component::Position *>(_entities[i][Component::POSITION]);
  Component::Move *move = static_cast<Component::Move *>(_entities[i][Component::MOVE]);

  if ((pos->getX() - PIXELS_OFFSET + move->getSpeed()) / PIXELS_BY_CASE == (pos->getX() - PIXELS_OFFSET)/ PIXELS_BY_CASE) {
    pos->setX(pos->getX() + move->getSpeed());
  }
  else if (canMove(pos->getX() + move->getSpeed(), pos->getY(), i, Component::SOLID) == -1) {
    pos->setX(pos->getX() + move->getSpeed());
  }
}

void System::Move::moveNorth(unsigned int& i) {
  Component::Position *pos = static_cast<Component::Position *>(_entities[i][Component::POSITION]);
  Component::Move *move = static_cast<Component::Move *>(_entities[i][Component::MOVE]);

  if ((pos->getX() - PIXELS_OFFSET - move->getSpeed()) / PIXELS_BY_CASE == (pos->getX() - PIXELS_OFFSET) / PIXELS_BY_CASE) {
    pos->setX(pos->getX() - move->getSpeed());
  }
  else if (canMove(pos->getX() - move->getSpeed(), pos->getY(), i, Component::SOLID) == -1) {
    pos->setX(pos->getX() - move->getSpeed());
  }
}

void System::Move::moveEast(unsigned int& i) {
  Component::Position *pos = static_cast<Component::Position *>(_entities[i][Component::POSITION]);
  Component::Move *move = static_cast<Component::Move *>(_entities[i][Component::MOVE]);

  if ((pos->getY() - PIXELS_OFFSET + move->getSpeed()) / PIXELS_BY_CASE == (pos->getY() - PIXELS_OFFSET) / PIXELS_BY_CASE) {
    pos->setY(pos->getY() + move->getSpeed());
  }
  else if (canMove(pos->getX(), pos->getY() + move->getSpeed(), i, Component::SOLID) == -1)
    pos->setY(pos->getY() + move->getSpeed());
}

void System::Move::moveWest(unsigned int& i) {
  Component::Position *pos = static_cast<Component::Position *>(_entities[i][Component::POSITION]);
  Component::Move *move = static_cast<Component::Move *>(_entities[i][Component::MOVE]);

  if ((pos->getY() - PIXELS_OFFSET - move->getSpeed()) / PIXELS_BY_CASE == (pos->getY() - PIXELS_OFFSET) / PIXELS_BY_CASE) {
    pos->setY(pos->getY() -move->getSpeed());
  }
  else if (canMove(pos->getX(), pos->getY() - move->getSpeed(), i, Component::SOLID) == -1) {
    pos->setY(pos->getY() - move->getSpeed());
  }
}
