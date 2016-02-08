#include <algorithm>
#include "Systems/AI.hpp"
#include "BaseComponent.hpp"
#include "Components/Move.hpp"
#include "Position.hpp"
#include "Range.hpp"
#include "FactoryEntity.hpp"
#include <utility>

System::AI::AI(std::vector<Entity>& entities) : ASystem(entities) {
  //{PLAYER, TILE, BOMB, POWERUP, EXPLOSION, WALL, DESTRUCTIBLEWALL};
  _propagationPtrs.push_back(&System::AI::propagationPlayer);
  _propagationPtrs.push_back(&System::AI::propagationTile);
  _propagationPtrs.push_back(&System::AI::propagationBomb);
  _propagationPtrs.push_back(&System::AI::propagationBonus);
  _propagationPtrs.push_back(&System::AI::propagationExplosion);
  _propagationPtrs.push_back(&System::AI::propagationWall);
  _propagationPtrs.push_back(&System::AI::propagationDestructibleWall);
  _addSmellPtrs.reserve(8);
  _addSmellPtrs[Component::Move::NORTH] = &System::AI::addNorth;
  _addSmellPtrs[Component::Move::EAST] = &System::AI::addEast;
  _addSmellPtrs[Component::Move::SOUTH] = &System::AI::addSouth;
  _addSmellPtrs[Component::Move::WEST] =&System::AI::addWest;
}

System::AI::~AI() {}

int System::AI::update(float) {
  std::vector<Entity>::iterator it = _entities.begin();
  while (it != _entities.end()) {
    if (System::AI::predictIsABot(*it)) {
      updateBot(*it);
    }
    it++;
  }
  return 0;
}

void System::AI::updateBot(Entity & ent) {
  initMapSmells(ent);
  Component::Position *position_player = static_cast<Component::Position *>(ent[Component::POSITION]);
  int idx = (position_player->getY() + 500) / MAPPS + (position_player->getX() + 500) / MAPPS * MAPS;
  Action move = choseAction(ent, idx);
  act(ent, move);
}

void System::AI::initMapSmells(Entity const & ent) {
  _mapEntities.clear();
  _mapEntities.reserve(MAPS * MAPS);
  _mapSmells.clear();
  _mapSmells.reserve(MAPS * MAPS);
  Component::Position * position;
  BaseComponent * component;
  Entity const * entity;
  unsigned int i;
  // generate blank
  for (i = 0; i < MAPS * MAPS; i++) {
    _mapSmells[i] = 0;
    _mapEntities[i] = NULL;
  }
  // generate smells
  for (i = 0; i < _entities.size(); i++) {
    entity = &_entities[i];
    component = entity->getComponent(Component::POSITION);
    position = static_cast<Component::Position *>(component);
    int idx = (position->getY() + 500) / MAPPS + (position->getX() + 500) / MAPPS * MAPS;
    if (idx >= 0 && idx <= MAPS * MAPS)
      _mapEntities[idx] = entity;
    if (&_entities[i] != &ent)
      propagation(_entities[i], idx);
  }
}

void System::AI::propagation(Entity & ent, int idx) {
  if (_propagationPtrs[ent.getType()] != NULL) {
    (this->*_propagationPtrs[ent.getType()])(ent, idx);
  }
}
void System::AI::propagationWall(Entity &, int idx) {
  _mapSmells[idx] = -100;
}
void System::AI::propagationDestructibleWall(Entity &, int idx) {
  _mapSmells[idx] = -100;
}
void System::AI::propagationBomb(Entity & ent, int idx) {
  _mapSmells[idx] = -100;
  Component::Range * rangePtr = static_cast<Component::Range *>(ent.getComponent(Component::RANGE));
  unsigned int range = rangePtr->getRange()  / PIXELS_BY_CASE;
  for (unsigned int i = 1; i <= range; i++)
    addAround(-50+i*2, idx, i);
}
void System::AI::propagationBonus(Entity &, int idx) {
  _mapSmells[idx] += 5;
  addAround(3, idx, 1);
  addAround(2, idx, 2);
  addAround(1, idx, 3);
}
void System::AI::propagationPlayer(Entity &, int idx) {
  _mapSmells[idx] = -100;
  addAround(2, idx, 1);
  addAround(1, idx, 2);
}
void System::AI::propagationExplosion(Entity & ent, int idx) {
  _mapSmells[idx] -= 100;
  Component::Range * rangePtr = static_cast<Component::Range *>(ent.getComponent(Component::RANGE));
  Component::Move * movePtr = static_cast<Component::Move *>(ent.getComponent(Component::MOVE));
  unsigned int range = rangePtr->getRange() / PIXELS_BY_CASE;
  for (unsigned int i = 1; i <= range; i++) {
    addToComponentDir(movePtr->getDir(), -50+i*2, idx, i);
  }
}
void System::AI::propagationTile(Entity &, int) {
}

#include <iostream>
System::AI::Action System::AI::choseAction(Entity & ent, int idx) {
  // Priority to survive
  if (isInDanger(idx))
    return moveToBetter(ent, idx);
  else {
    // If near a target
    //if (nearTo(idx, Entity::POWERUP))
    //  return moveToBetter(ent, idx);
    //else if (nearTo(idx, Entity::PLAYER))
    //  return placeBomb(ent, idx);
    // If no target
    if (nearToNothing(ent, idx))
      return moveToBetter(ent, idx);
    //else if (nearTo(idx, Entity::WALL))
    //  return placeBomb(ent, idx);
    else
      return moveToRandom(ent, idx);
  }
}

void System::AI::act(Entity & ent, System::AI::Action move) {
  int dir = (int)move;
  if (rand() % ENTROPY == 0)
    dir = (dir + rand() % 4 + 1) % 4 + 1;
  if (dir >= (int)NORTH && move <= (int)WEST) {
    static_cast<Component::Move *>(ent.getComponent(Component::MOVE))->setDir((Component::Move::dir)(dir));
  }
  else if (dir == BOMB) {
  }
}

System::AI::Action System::AI::moveToBetter(Entity &, int idx) {
  std::vector<int> smells(4);
  smells[0] = getSmellAtNorth(idx);
  smells[1] = getSmellAtEast(idx);
  smells[2] = getSmellAtSouth(idx);
  smells[3] = getSmellAtWest(idx);
  Action move(ERROR);
  int max = *std::max_element(smells.begin(), smells.end());
  if (max < 0 || max < _mapSmells[idx])
    return move;
  move = (Action)(int)(std::find(smells.begin(), smells.end(), max) - smells.begin() + 1);
  return (move);
}
System::AI::Action System::AI::moveToRandom(Entity & ent, int idx) {
//  return WEST;
  return moveToBetter(ent, idx);
}
System::AI::Action System::AI::placeBomb(Entity &entity, int) {
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
  }
  return BOMB;
}

bool System::AI::isInDanger(int idx) {
  try {
    int v = _mapSmells.at(idx);
    return v < 0;
  } catch (...) {
    return false;
  }
}

int System::AI::getSmellAt(int from, int x, int y, int range) {
  int xf = from % MAPS;
  int yf = from / MAPS;
  x = xf + x * range;
  y = yf + y * range;
  if (x < 0 || x >= MAPS || y < 0 || y >= MAPS)
    return -100;
  return _mapSmells[x + y * MAPS];
}
int System::AI::getSmellAtNorth(int idx) {
  return getSmellAt(idx, 0, -1);
}
int System::AI::getSmellAtEast(int idx) {
  return getSmellAt(idx, 1, 0);
}
int System::AI::getSmellAtSouth(int idx) {
  return getSmellAt(idx, 0, +1);
}
int System::AI::getSmellAtWest(int idx) {
  return getSmellAt(idx, -1, 0);
}

Entity const * System::AI::getEntityAt(int idx) {
  if (idx < 0 || idx > MAPS * MAPS)
    return NULL;
  try {
    return _mapEntities.at(idx);
  } catch (...) {
    return NULL;
  }
}
Entity::type System::AI::getEntityTypeAt(int idx) {
  Entity const * ent(getEntityAt(idx));
  if (ent != NULL)
    return ent->getType();
  return Entity::TILE;
}

System::AI::Action System::AI::nearTo(int idx, Entity::type type) {
  _nearTo.push_back(std::pair<Action, int>(NORTH, idx - MAPS));
  _nearTo.push_back(std::pair<Action, int>(EAST, idx + 1));
  _nearTo.push_back(std::pair<Action, int>(SOUTH, idx + MAPS));
  _nearTo.push_back(std::pair<Action, int>(WEST, idx - 1));
  _nearTo.push_back(std::pair<Action, int>(NONE, idx));
  Action move(System::AI::ERROR);
  for (unsigned int i = 0; i < _nearTo.size(); ++i) {
    if (getEntityTypeAt(_nearTo[i].second) == type) {
      move = _nearTo[i].first;
    }
  }
  return move;
}

int System::AI::nearToNothing(Entity &, int idx) {
  Entity::type WEST, up, EAST, SOUTH;
  up = getEntityTypeAt(idx - MAPS);
  EAST = getEntityTypeAt(idx + 1);
  SOUTH = getEntityTypeAt(idx + MAPS);
  WEST = getEntityTypeAt(idx - 1);
  if ((up == Entity::WALL || up == Entity::TILE) &&
      (EAST == Entity::WALL || EAST == Entity::TILE) &&
      (SOUTH == Entity::WALL || SOUTH == Entity::TILE) &&
      (WEST == Entity::WALL || WEST == Entity::TILE))
    return 1;
  return 0;
}

void System::AI::addAt(int v, int from, int x, int y, int range) {
  int xf = from % MAPS;
  int yf = from / MAPS;
  x = xf + x * range;
  y = yf + y * range;
  if (x < 0 || x >= MAPS || y < 0 || y >= MAPS)
    return;
  _mapSmells[x + y * MAPS] += v;
}
void System::AI::addNorth(int v, int from, int range) {
  addAt(v, from, 0, -1, range);
}
void System::AI::addEast(int v, int from, int range) {
  addAt(v, from, 1, 0, range);
}
void System::AI::addSouth(int v, int from, int range) {
  addAt(v, from, 0, 1, range);
}
void System::AI::addWest(int v, int from, int range) {
  addAt(v, from, -1, 0, range);
}
void System::AI::addAround(int v, int from, int range) {
  addNorth(v, from, range);
  addEast(v, from, range);
  addSouth(v, from, range);
  addWest(v, from, range);
}

void System::AI::addToComponentDir(Component::Move::dir dir, int v, int from, int range) {
  (this->*_addSmellPtrs[dir])(v, from, range);
}

void System::AI::addToActionDir(System::AI::Action dir, int v, int from, int range) {
  if (dir == NORTH || dir == EAST || dir == SOUTH || dir == WEST)
    addToComponentDir((Component::Move::dir)((int)dir - 1), v, from, range);
}

bool System::AI::predictIsABot(Entity & ent) {
  return ent.getComponent(Component::ISAI) != NULL;
}
