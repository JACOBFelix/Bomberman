#include "FactoryComponent.hpp"

FactoryComponent::FactoryComponent() {
  _createPtrs.reserve(16);
  _createPtrs[Component::BONUS] = &FactoryComponent::createBonus;
  _createPtrs[Component::BREAKABLE] = &FactoryComponent::createBreakable;
  _createPtrs[Component::FD] = &FactoryComponent::createFd;
  _createPtrs[Component::ID] = &FactoryComponent::createId;
  _createPtrs[Component::INPUTCONTEXT] = &FactoryComponent::createInputContext;
  _createPtrs[Component::ISAI] = &FactoryComponent::createIsAI;
  _createPtrs[Component::MOVE] = &FactoryComponent::createMove;
  _createPtrs[Component::NBBOMB] = &FactoryComponent::createNbBomb;
  _createPtrs[Component::PLAYERINFO] = &FactoryComponent::createPlayerInfo;
  _createPtrs[Component::POSITION] = &FactoryComponent::createPosition;
  _createPtrs[Component::RANGE] = &FactoryComponent::createRange;
  _createPtrs[Component::SOLID] = &FactoryComponent::createSolid;
  _createPtrs[Component::TIMER] = &FactoryComponent::createTimer;
}

FactoryComponent::~FactoryComponent() {}

BaseComponent *	FactoryComponent::create(Component::type const t) {
  return (this->*_createPtrs[t])();
}

FactoryComponent *	FactoryComponent::getInstance(void) {
  static FactoryComponent instance;
  return &instance;
}

BaseComponent * FactoryComponent::createPosition() {
  return new Component::Position;
}

BaseComponent * FactoryComponent::createBonus() {
  return new Component::Bonus;
}

BaseComponent * FactoryComponent::createFd() {
  return new Component::Fd;
}

BaseComponent * FactoryComponent::createPlayerInfo() {
  return new Component::PlayerInfo;
}

BaseComponent * FactoryComponent::createRange() {
  return new Component::Range;
}

BaseComponent * FactoryComponent::createTimer() {
  return new Component::Timer;
}

BaseComponent * FactoryComponent::createMove() {
  return new Component::Move;
}

BaseComponent * FactoryComponent::createInputContext() {
  return new Component::InputContext;
}

BaseComponent * FactoryComponent::createNbBomb() {
  return new Component::NbBomb;
}

BaseComponent * FactoryComponent::createId() {
  return new Component::Id;
}

BaseComponent * FactoryComponent::createBreakable() {
  return new Component::Breakable;
}

BaseComponent * FactoryComponent::createSolid() {
  return new Component::Solid;
}

BaseComponent * FactoryComponent::createIsAI() {
  return new Component::IsAI;
}
