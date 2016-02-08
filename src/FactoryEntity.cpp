#include "FactoryEntity.hpp"
#include "Exceptions.hpp"

FactoryEntity::FactoryEntity() : _ptr({&FactoryEntity::newPlayer,
      &FactoryEntity::newTile,
      &FactoryEntity::newBomb,
      &FactoryEntity::newPowerUp,
      &FactoryEntity::newExplosion,
      &FactoryEntity::newWall,
      &FactoryEntity::newDestructibleWall}) {
  if (!_flames.load("./assets/flame.fbx"))
    throw DisplayException("Could not load flame model");
  if (!_bonusIce.load("./assets/crystal.fbx"))
    throw DisplayException("Could not load icy bonus model");
  if (!_bonusFlame.load("./assets/crystalf.fbx"))
    throw DisplayException("Could not load fiery bonus model");
  if (!_bonusPink.load("./assets/crystalp.fbx"))
    throw DisplayException("Could not load pink bonus model");
  if (!_bombModel.load("./assets/bomb.fbx"))
    throw DisplayException("Could not load bomb model");
  if (!_wallModel.load("./assets/wall.fbx"))
    throw DisplayException("Could not load wall model");
  if (!_groundModel.load("./assets/ground.fbx"))
    throw DisplayException("Could not load ground model");
  if (!_koalaModel.load("./assets/koala.fbx"))
    throw DisplayException("Could not load Koala model");
  if (!_brokenWallModel.load("./assets/brokenWall.fbx"))
    throw DisplayException("Could not load Koala model");
}

FactoryEntity::~FactoryEntity() {}

gdl::Model& FactoryEntity::getBonusIce(void) {
  return _bonusIce;
}

gdl::Model& FactoryEntity::getBonusFlame(void) {
  return _bonusFlame;
}

gdl::Model& FactoryEntity::getBonusPink(void) {
  return _bonusPink;
}

Entity	FactoryEntity::create(Entity::type const t) {
  return (this->*_ptr[t])();
}

FactoryEntity *	FactoryEntity::getInstance(void) {
  static FactoryEntity instance;
  return &instance;
}

Entity	FactoryEntity::newTile(void) {
  Entity tmp(Entity::TILE);
  tmp << Component::POSITION << new Component::Model(_groundModel, 0.02) << Component::MOVE;
  static_cast<Component::Move *>(tmp[Component::MOVE])->setDir(Component::Move::NONE);
  return tmp;
}

Entity	FactoryEntity::newBomb(void) {
  Entity tmp(Entity::BOMB);
  tmp << Component::POSITION << Component::RANGE << Component::TIMER << new Component::Model(_bombModel, 0.003) << Component::ID << Component::MOVE << Component::SOLID;
  static_cast<Component::Move *>(tmp[Component::MOVE])->setDir(Component::Move::NONE);
  static_cast<Component::Timer *>(tmp[Component::TIMER])->setMs(1000);
  return tmp;
}

Entity	FactoryEntity::newPowerUp(void) {
  Entity tmp(Entity::POWERUP);
  tmp << Component::POSITION << Component::BONUS << new Component::Model(_bonusIce, 0.0002) << Component::MOVE;
  static_cast<Component::Move *>(tmp[Component::MOVE])->setDir(Component::Move::NONE);
  static_cast<Component::Bonus *>(tmp[Component::BONUS])->setType(static_cast<Component::Bonus::type>(std::rand() % 3));
  return tmp;
}

Entity	FactoryEntity::newExplosion(void) {
  return Entity(Entity::EXPLOSION) << Component::POSITION << Component::TIMER << new Component::Model(_flames, 0.003) << Component::MOVE << Component::RANGE;
}

Entity 	FactoryEntity::newPlayer(void) {
  Entity tmp(Entity::PLAYER);
  tmp << Component::POSITION << Component::PLAYERINFO << Component::INPUTCONTEXT << new Component::Model(_koalaModel, 0.002) << Component::MOVE << Component::NBBOMB << Component::RANGE << Component::BREAKABLE << Component::SOLID;
  static_cast<Component::Move *>(tmp[Component::MOVE])->setDir(Component::Move::NONE);
  static_cast<Component::Move *>(tmp[Component::MOVE])->setSpeed(42);
  static_cast<Component::NbBomb *>(tmp[Component::NBBOMB])->setNb(1);
  static_cast<Component::Range *>(tmp[Component::RANGE])->setRange(3);
  return tmp;
}

Entity	FactoryEntity::newWall(void) {
  Entity tmp(Entity::WALL);
  
  tmp << Component::POSITION << new Component::Model(_wallModel, 0.005) << Component::MOVE << Component::SOLID;
  static_cast<Component::Move *>(tmp[Component::MOVE])->setDir(Component::Move::NONE);
  return tmp;
}

Entity	FactoryEntity::newDestructibleWall(void) {
  Entity tmp(Entity::DESTRUCTIBLEWALL);
  tmp << Component::POSITION << new Component::Model(_brokenWallModel, 0.005) << Component::MOVE << Component::SOLID << Component::BREAKABLE;
  static_cast<Component::Move *>(tmp[Component::MOVE])->setDir(Component::Move::NONE);
  return tmp;
}
